#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>


class CameraProcessor{
    private:
        cv::VideoCapture cap;
        cv::Mat frame; 

    public:
        bool open(int camera_id=0);
        bool grabFrame();
        const cv::Mat& getFrame() const;
        void release();

};