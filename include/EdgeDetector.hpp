#include<opencv2/opencv.hpp>
#include "ImageProcessor.hpp"

class EdgeDetector : public ImageProcessor{
    private:
        int lowThreshold_;
        int highThreshold_;
    public:
        EdgeDetector(int lowThreshold, int highThreshold);
        cv::Mat process(const cv::Mat& inputImage) override;
};