#pragma once
#include<opencv2/opencv.hpp>
#include <onnxruntime/onnxruntime_cxx_api.h>
#include<vector>


class InferenceEngine{
    private:
        Ort::Env env;
        Ort::Session* session;
        Ort::SessionOptions session_options;

        std::vector<std::string> input_names_str;
        std::vector<std::string> output_names_str;

        std::vector<const char*> input_names;
        std::vector<const char*> output_names;
    public:
        InferenceEngine();
        bool loadModel(const std::string& model_path);
        void run(cv::Mat& frame);
};