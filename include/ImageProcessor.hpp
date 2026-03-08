#pragma once
#include <opencv2/opencv.hpp>

class ImageProcessor {
   public:
        virtual cv::Mat process(const cv::Mat& inputImage) = 0;
        virtual ~ImageProcessor() = default;
};