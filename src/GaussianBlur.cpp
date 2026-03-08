#include "Blurring.hpp"
#include<opencv2/opencv.hpp>


Blurring::Blurring(int kernalSize) : kernalSize_(kernalSize){

}

cv::Mat Blurring::process(const cv::Mat& inputImage){
    cv::Mat blur;
    cv::GaussianBlur(inputImage, blur, cv::Size(kernalSize_, kernalSize_), 0);

    return blur;
}
