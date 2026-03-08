#include "ImageLoader.hpp"


bool ImageLoader::load(const std::string& path){
    image = cv::imread(path);
    return !image.empty();
}

const cv::Mat& ImageLoader::getImage() const{
    return image;
}