#pragma once
#include "ImageLoader.hpp"
#include "ImageProcessor.hpp"
#include "CameraProcessor.hpp"
#include <memory>
#include <string>

using namespace std;

class Application{
    private:
        CameraProcessor camera_;
        ImageLoader loader_;
        vector<unique_ptr<ImageProcessor>> processor_;
    public:
        void addProcessor(unique_ptr<ImageProcessor> processor);
        void run();
};