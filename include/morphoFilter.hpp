#include <opencv2/opencv.hpp>
#include "ImageProcessor.hpp"

class morphoFilter : public ImageProcessor{
    private:
        int thresh_;
        int kernel_;
    public:
        morphoFilter(int thresh, int kernel);
        cv::Mat process(const cv::Mat& inputImage);

};