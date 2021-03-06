#include "qmyvideotools.h"
#include <stdlib.h>

QmyVideoTools::QmyVideoTools(QObject *parent)
    : QObject(parent)
    , bStreamPaused(false)
{
}

QmyVideoTools::~QmyVideoTools()
{
    m_capVideoStream.release();
}

void QmyVideoTools::getFrame(cv::Mat_<unsigned char> &frame)
{
    if(!(m_capVideoStream.isOpened()))
        openCaptureDevice(m_nDefaultCameraIndex);

    m_capVideoStream.read(frame);
    if(frame.empty() == true)
    {
        printf("Failed to read from capture device!");
    }

    cv::cvtColor(frame, frame, CV_BGR2GRAY);//CV_BGR2RGB
}

void QmyVideoTools::openCaptureDevice(int nCameraIndex)
{
    if(!m_capVideoStream.open(nCameraIndex))
    {
        printf("Cannot open capture device!");
    }
}

void QmyVideoTools::landmarkAll(cv::Mat_<unsigned char> &frame)
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


void QmyVideoTools::landmarkNose(cv::Mat_<unsigned char> &frame)
{

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

         frame(cvRound(landmarks[43]), cvRound(landmarks[42])) = 255;
         frame(cvRound(landmarks[45]), cvRound(landmarks[44])) = 255;
         frame(cvRound(landmarks[97]), cvRound(landmarks[96])) = 255;
         frame(cvRound(landmarks[99]), cvRound(landmarks[98])) = 255;
         frame(cvRound(landmarks[101]), cvRound(landmarks[100])) = 255;
         frame(cvRound(landmarks[103]), cvRound(landmarks[102])) = 255;
         frame(cvRound(landmarks[105]), cvRound(landmarks[104])) = 255;
         frame(cvRound(landmarks[107]), cvRound(landmarks[106])) = 255;
         frame(cvRound(landmarks[109]), cvRound(landmarks[108])) = 255;
         frame(cvRound(landmarks[111]), cvRound(landmarks[110])) = 255;
         frame(cvRound(landmarks[113]), cvRound(landmarks[112])) = 255;
         frame(cvRound(landmarks[115]), cvRound(landmarks[114])) = 255;
         frame(cvRound(landmarks[117]), cvRound(landmarks[116])) = 255;

    }

}

void QmyVideoTools::markCenterPoint(cv::Mat_<unsigned char> &frame)
{
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

    //calculate lenght of landmarks (note: must be even because contains x,y pairs)
    //int nLengthOfLandmarks = (sizeof(landmarks)) / (sizeof((landmarks[0])));
    int nLengthOfLandmarks = 26;
    float xSum = 0.0;
    float ySum = 0.0;
    //float xLandmarks[13];
    //float yLandmarks[13];
    int xMax = 0;
    int yMax = 0;

    for( int i = 0 ; i<nLengthOfLandmarks/2 ; i++ )
    {
        xSum += landmarks[2*i];
        //xLandmarks[i]=landmarks[i];
        ySum += landmarks[2*i+1];
        //yLandmarks[i+1]=landmarks[i+1];

        if(landmarks[2*i]>xMax) {xMax=landmarks[2*i];}
        if(landmarks[2*i+1]>yMax) {yMax=landmarks[2*i+1];}
    }

    float xCenter = xSum / 13.0;
    float yCenter = ySum / 13.0;

    printf("\nxSum: %f\tySum: %f\n",xSum,ySum);
    printf("xCenter: %f",xCenter);
    printf("\tyCenter: %f\n",yCenter);
    printf("landmark[0] = %f",landmarks[0]);
    printf("\tlandmark[1] = %f\n",landmarks[1]);


    cv::line(frame,cvPoint(xCenter,yMax),cvPoint(xCenter,yMax+50),1);
    //frame(cvRound(yCenter), cv::Range(yMax,yMax-30)) = 0;
}
