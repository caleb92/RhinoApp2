#ifndef VIDEOTOOLS_H
#define VIDEOTOOLS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "stasm_lib.h"

class VideoTools
{
public:
    VideoTools();
    ~VideoTools();

    void getFrame(cv::Mat_<unsigned char>& frame);
    void openCamera(int nCameraIndex);

    void landmarkAll(cv::Mat_<unsigned char>& frame);

private:

    int m_nCameraIndex;

    cv::VideoCapture m_capWebcam;

    //cv::Mat_<unsigned char> m_matOriginal;//(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE));


    int foundface;
    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)

};

#endif // VIDEOTOOLS_H
