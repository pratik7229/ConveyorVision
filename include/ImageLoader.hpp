#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class ImageLoader{
    private:
        cv::Mat image;
    public:
        bool load(const std::string& path);
        const cv::Mat& getImage() const;
};