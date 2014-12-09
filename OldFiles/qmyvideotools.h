#ifndef QMYVIDEOTOOLS_H
#define QMYVIDEOTOOLS_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stasm_lib.h"

#include <QTimer>
#include <QList>

class QmyVideoTools : public QObject
{
    Q_OBJECT

public:
    explicit QmyVideoTools(QObject *parent = 0);
    ~QmyVideoTools();

signals:

public slots:
    void getFrame(cv::Mat_<unsigned char>& frame);
    void openCaptureDevice(const int nCameraIndex = m_nDefaultCameraIndex);

    void landmarkAll(cv::Mat_<unsigned char>& frame);
    void landmarkNose(cv::Mat_<unsigned char>& frame);

    void markCenterPoint(cv::Mat_<unsigned char>& frame);

private:
    bool bStreamPaused;
    static const int m_nDefaultCameraIndex = 0;

    cv::VideoCapture m_capVideoStream;
    int foundface;
    float landmarks[2*stasm_NLANDMARKS];
    //QList m_listLandmarksAll<float>;

    static const int NNASALLANDMARKS = 13;
    //float nasalLandmarks[2*NNASALLANDMARKS];
    //static const int nasalLandmarksIndices[2*NNASALLANDMARKS] = {42,43,44,45,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117};

};

#endif // QMYVIDEOTOOLS_H
