#include<InferenceEngine.hpp>
#include<iostream>
#include<vector>
const std::vector<std::string> coco_classes = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat",
    "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
    "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack",
    "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball",
    "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket",
    "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
    "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake",
    "chair", "couch", "potted plant", "bed", "dining table", "toilet", "tv", "laptop",
    "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink",
    "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"
};

InferenceEngine::InferenceEngine(): env(ORT_LOGGING_LEVEL_WARNING, "ConveyorVision")
{
    session = nullptr;
}

bool InferenceEngine::loadModel(const std::string& model_path)
{
    try
    {
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
        session = new Ort::Session(env, model_path.c_str(), session_options);

        Ort::AllocatorWithDefaultOptions allocator;

        // Input name
        auto input_name = session->GetInputNameAllocated(0, allocator);
        input_names_str.push_back(input_name.get());

        // Output name
        auto output_name = session->GetOutputNameAllocated(0, allocator);
        output_names_str.push_back(output_name.get());

        // Convert to const char*
        for(auto& name : input_names_str)
            input_names.push_back(name.c_str());

        for(auto& name : output_names_str)
            output_names.push_back(name.c_str());
    }
    catch(const std::exception& e)
    {
        std::cout << "Model load failed: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Model Loaded\n";
    return true;
}

inline float sigmoid(float x)
{
    return 1.f / (1.f + std::exp(-x));
}

void InferenceEngine::run(cv::Mat& frame)
{
    cv::Mat resized, rgb;

    cv::resize(frame, resized, cv::Size(640,640));
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);
    rgb.convertTo(rgb, CV_32F, 1.0/255.0);

    std::vector<cv::Mat> channels(3);
    cv::split(rgb, channels);

    std::vector<float> input_tensor_values(3 * 640 * 640);

    int channel_size = 640 * 640;

    for(int i=0;i<3;i++)
    {
        memcpy(
            input_tensor_values.data() + i * channel_size,
            channels[i].data,
            channel_size * sizeof(float)
        );
    }

    std::array<int64_t,4> input_shape = {1,3,640,640};

    Ort::MemoryInfo memory_info =
        Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    Ort::Value input_tensor =
        Ort::Value::CreateTensor<float>(
            memory_info,
            input_tensor_values.data(),
            input_tensor_values.size(),
            input_shape.data(),
            4
        );


    auto output_tensors = session->Run(
        Ort::RunOptions{nullptr},
        input_names.data(),
        &input_tensor,
        1,
        output_names.data(),
        1
    );

    float* output_data = output_tensors[0].GetTensorMutableData<float>();
    auto shape = output_tensors[0].GetTensorTypeAndShapeInfo().GetShape();

    // YOLOv11 output is [1, 84, 8400]
    int rows = shape[1]; // 4 (coords) + 80 (classes for COCO)
    int cols = shape[2]; // 8400 (anchors/predictions)

    // Transpose to [8400, 84]
    cv::Mat output_mat(rows, cols, CV_32F, output_data);
    cv::Mat detections = output_mat.t();

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    float conf_threshold = 0.25f;
    float nms_threshold = 0.45f; // Standard overlap threshold
    
    float x_scale = frame.cols / 640.0f;
    float y_scale = frame.rows / 640.0f;

    for (int i = 0; i < detections.rows; i++)
    {
        float* row_ptr = detections.ptr<float>(i);
        
        // Scores start at index 4
        cv::Mat scores(1, rows - 4, CV_32F, row_ptr + 4);
        double max_conf;
        cv::Point class_id;
        cv::minMaxLoc(scores, nullptr, &max_conf, nullptr, &class_id);

        if (max_conf > conf_threshold)
        {
            float cx = row_ptr[0];
            float cy = row_ptr[1];
            float w  = row_ptr[2];
            float h  = row_ptr[3];

            int left   = static_cast<int>((cx - w/2) * x_scale);
            int top    = static_cast<int>((cy - h/2) * y_scale);
            int width  = static_cast<int>(w * x_scale);
            int height = static_cast<int>(h * y_scale);

            boxes.push_back(cv::Rect(left, top, width, height));
            confidences.push_back(static_cast<float>(max_conf));
            class_ids.push_back(class_id.x);
        }
    }

    // Apply NMS
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, conf_threshold, nms_threshold, indices);

    // Draw only the best boxes
    for (int idx : indices)
{
    cv::Rect box = boxes[idx];
    int class_id = class_ids[idx];
    float confidence = confidences[idx];

    // Get name from list, safety check for index
    std::string class_name = (class_id < coco_classes.size()) ? coco_classes[class_id] : "Unknown";
    
    // Create label string: "person: 0.85"
    std::string label = class_name + ": " + cv::format("%.2f", confidence);

    // Draw Box
    cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);

    // Draw Label Background
    int baseline;
    cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 1.7, 1, &baseline);
    cv::rectangle(frame, 
                  cv::Rect(box.x, box.y - label_size.height - 10, label_size.width, label_size.height + 10), 
                  cv::Scalar(0, 255, 0), cv::FILLED);

    // Write Text
    cv::putText(frame, label, cv::Point(box.x, box.y - 10), 
                cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 0), 1);
}
}
