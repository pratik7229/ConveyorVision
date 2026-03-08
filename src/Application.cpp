#include "Application.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>

void Application::addProcessor(std::unique_ptr<ImageProcessor> processor)
{
    processor_.push_back(std::move(processor));
}
void Application::run(const std::string& imagePath)
{
    if (!loader_.load(imagePath))
    {
        std::cout << "Failed to load image\n";
        return;
    }

    cv::Mat image = loader_.getImage();

    for (auto& processor : processor_)
    {
        image = processor->process(image);
    }
    cv::imshow("Result", image);

    cv::waitKey(0);
}