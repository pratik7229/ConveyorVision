#include <opencv2/opencv.hpp>
#include "ImageProcessor.hpp"


class Blurring : public ImageProcessor{
    private:
        int kernalSize_;
    public:
       Blurring(int kernalSize); 
       cv::Mat process(const cv::Mat& inputImage);
};