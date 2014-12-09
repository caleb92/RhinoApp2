#ifndef VIDEOTOOLS_H
#define VIDEOTOOLS_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stasm_lib.h"

#include <QTimer>
#include <QList>
#include <QLabel>
#include <QPainter>
#include <QVector>

#include "displaylabel.h"

class VideoTools : public QObject
{
    Q_OBJECT

public:

    enum StreamingStatus {
        StreamingOff,
        StreamingOn
    };
    enum DisplayMode {
        VideoMode,
        ImageMode
    };
    enum LandmarkMode {
        LandmarkNone,
        Landmark72,
        Landmark13
    };

    explicit VideoTools(DisplayLabel *display, QObject *parent = 0);
    ~VideoTools();

    int getCameraIndex();
    void setCameraIndex(int cameraIndex);

    StreamingStatus getStreamingStatus();
    void setStreamingStatus(VideoTools::StreamingStatus streamingStatus);

    DisplayMode getDisplayMode();
    void setDisplayMode(VideoTools::DisplayMode displayMode);

    LandmarkMode getLandmarkState();
    void setLandmarkState(VideoTools::LandmarkMode landmarkState);

    bool isBounds13();
    void setBounds13(bool bounds13On);

    bool isBounds72();
    void setBOunds72(bool bounds72On);

    bool isScaleCirc();
    void setScaleCirc(bool scaleCircOn);

    bool isScaleLine();
    void setScaleLine(bool scaleLineOn);

    int getFoundFace();

public slots:

private slots:
    void processFrame();

private:
    void getFrame();
    void updateRect72();
    void updateRect13();
    void openCaptureDevice();
    void updateLandmarks();

    void drawLandmarks72();
    void drawRect72();
    void drawLandmarks13();
    void drawRect13();
    void drawScaleCirc();
    void drawScaleLine();

    int m_cameraIndex;

    StreamingStatus m_streamingStatus;

    DisplayMode m_displayMode;

    float landmarks[2*stasm_NLANDMARKS];
    VideoTools::LandmarkMode m_landmarkMode;

    bool m_bounds13;
    QRect rect13;
    bool m_bounds72;
    QRect rect72;

    bool m_scaleCirc;
    bool m_scaleLine;

    DisplayLabel *m_display;

    QTimer *timer;
    cv::Mat_<unsigned char> matGray;
    cv::Mat_<unsigned char> matOriginal;
    cv::Mat_<unsigned char> matProcessed;
    const QImage* imgOriginal;
    QImage imgDisplay;

    cv::VideoCapture m_capVideoStream;
    int foundface;


    const int NNASALLANDMARKS;
    QVector<int> XLocs13; //holds the 13 X locations of the nasal landmarks within the landmarks vector
    QVector<int> YLocs13; //holds the 13 Y locations of the nasal landmarks within the landmarks vector

    QPainter painter;
    QPen penLandmarks;
    QPen penBounds;
    QBrush brushBounds;
    QBrush brushLandmarks;

    QPainter painterDisplay;
};

#endif // VIDEOTOOLS_H
