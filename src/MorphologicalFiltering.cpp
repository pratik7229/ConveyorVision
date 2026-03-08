#include "morphoFilter.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>

morphoFilter::morphoFilter(int thresh, int kernel) : thresh_(thresh), kernel_(kernel){

}

cv::Mat morphoFilter::process(const cv::Mat& inputImage){
    cv::Mat output;
    cv::Mat kernelout = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size(kernel_,kernel_)
    );
    cv::morphologyEx(
        inputImage,
        output,
        cv::MORPH_OPEN,
        kernelout
    );

    cv::morphologyEx(
        output,
        output,
        cv::MORPH_CLOSE,
        kernelout
    );

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(output, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    double maxArea = 0;
    int maxIndex = -1;

    for(int i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        if(area > maxArea)
        {
            maxArea = area;
            maxIndex = i;
        }
    }


    cv::Mat clean = cv::Mat::zeros(output.size(), CV_8UC1);

    if(maxIndex >= 0)
    {
        cv::drawContours(clean, contours, maxIndex, 255, -1);
    }

    
    return clean;
}