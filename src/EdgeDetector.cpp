#include "EdgeDetector.hpp"
#include <opencv2/imgproc.hpp>

EdgeDetector::EdgeDetector(int lowThreshold, int highThreshold) : lowThreshold_(lowThreshold),
      highThreshold_(highThreshold){
    
}

cv::Mat EdgeDetector::process(const cv::Mat& inputImage){
    cv::Mat edges;
    cv::Canny(inputImage, edges, lowThreshold_, highThreshold_);
    return edges;
}

