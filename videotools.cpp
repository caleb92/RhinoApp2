#include "videotools.h"

#include "stasm_lib.h"

VideoTools::VideoTools()
{
    m_nCameraIndex = 54; //index of the capture devcie;
}

VideoTools::~VideoTools()
{
    m_capWebcam.release();
}

void VideoTools::getFrame(cv::Mat_<unsigned char>& frame)
{
    if(!(m_capWebcam.isOpened()))
        openCamera(m_nCameraIndex);

    m_capWebcam.read(frame);
    if(frame.empty() == true)
    {
        printf("Failed to read from capture device!");

    }

    cv::cvtColor(frame, frame, CV_BGR2GRAY);//CV_BGR2RGB

}

void VideoTools::openCamera(int nCameraIndex)
{
    if(m_capWebcam.open(nCameraIndex))
    {
        printf("Cannot open capture device!");
    }
}

void VideoTools::landmarkAll(cv::Mat_<unsigned char>& frame)
{

    //cv::cvtColor(frame, frame, CV_BGR2GRAY);//CV_BGR2RGB

    if (!stasm_search_single(   &foundface,
                                landmarks,
                                (const char*)frame.data,
                                frame.cols,
                                frame.rows,
                                "/stasm_search_single_ERRORS",
                                "../data"))
    {
        printf("Error in stasm_search_single: %s\n", stasm_lasterr());
        exit(1);
    }

    if (foundface)
    {
        // draw the landmarks on the image as white dots (image is monochrome)
        stasm_force_points_into_image(landmarks, frame.cols, frame.rows);
        for (int i = 0; i < stasm_NLANDMARKS; i++)
        {
            //frame(cv::Range(cvRound(landmarks[i*2+1])-1,cvRound(landmarks[i*2+1])+1),cv::Range(10,20));
            frame(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
        }
    }

}
