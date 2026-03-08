#include "ThresholdProcessor.hpp"
#include <opencv2/imgproc.hpp>

ThresholdProcessor::ThresholdProcessor(int ThresholdValue, int MaxThreshold) : ThresholdValue_(ThresholdValue),
      MaxThreshold_(MaxThreshold){
    
}

cv::Mat ThresholdProcessor::process(const cv::Mat& inputImage)
{
    cv::Mat hsv;
    cv::Mat mask;

    cv::cvtColor(inputImage, hsv, cv::COLOR_BGR2HSV);

    cv::Scalar lowerGreen(35, 40, 40);
    cv::Scalar upperGreen(85, 255, 255);

    cv::inRange(hsv, lowerGreen, upperGreen, mask);

    cv::bitwise_not(mask, mask);

    return mask;
}

