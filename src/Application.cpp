#include "Application.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>

void Application::addProcessor(std::unique_ptr<ImageProcessor> processor)
{
    processor_.push_back(std::move(processor));
}
void Application::run()
{
    inference_.loadModel("/Users/pratik/Documents/Finalized Projects/ConveyorVision/runs/yolov8m.onnx");
    if(!camera_.open(0))
    {
        std::cout<<"Failed to open Camera" << std::endl;
        return;
    }

    while(true){
        if(!camera_.grabFrame()){
            break;
        }
        cv::Mat frame = camera_.getFrame();
        inference_.run(frame);
        for(auto& processor : processor_){
            processor->process(frame);
        }
        cv::imshow("ConveyorVision", frame);

        if(cv::waitKey(1) == 27){
            break;
        }
    }
    camera_.release();


    
}