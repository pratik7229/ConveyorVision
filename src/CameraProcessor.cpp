#include "CameraProcessor.hpp"
#include <string>

        bool open(int camera_id=0);
        bool grabFrame();
        const cv::Mat& getFrame();
        bool release();

bool CameraProcessor::open(int camera_id){
    cap.open(camera_id);
    return cap.isOpened();
}

bool CameraProcessor::grabFrame(){
    cap>>frame;
    return !frame.empty();
}

const cv::Mat& CameraProcessor::getFrame() const{
    return frame;
}

void CameraProcessor::release(){
    if(cap.isOpened())
        cap.release();
    

}
