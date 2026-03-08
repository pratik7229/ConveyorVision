#include<opencv2/opencv.hpp>
#include "ImageProcessor.hpp"

class ThresholdProcessor : public ImageProcessor{
    private:
        int ThresholdValue_;
        int MaxThreshold_;
    public:
        ThresholdProcessor(int ThresholdValue, int MaxThreshold);
        cv::Mat process(const cv::Mat& inputImage) override;
};