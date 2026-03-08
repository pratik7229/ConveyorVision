#pragma once
#include "ImageLoader.hpp"
#include "ImageProcessor.hpp"
#include <memory>
#include <string>

using namespace std;

class Application{
    private:
        ImageLoader loader_;
        vector<unique_ptr<ImageProcessor>> processor_;
    public:
        void addProcessor(unique_ptr<ImageProcessor> processor);
        void run(const string& imagePath);
};