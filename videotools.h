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
    explicit VideoTools(DisplayLabel *display, QObject *parent = 0);
    ~VideoTools();

    enum StreamingStatus {
        NotStreaming,
        StreamingOn
    };

    enum Mode {
        VIDEOMODE,
        IMAGEMODE
    };

    enum LandmarkState {
        LandmarkNone,
        Landmark72,
        Landmark13
    };

    enum BoundsPos {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT,
        XCENTER,
        YCENTER,
        WIDTH,
        HEIGHT
    };

    int getCameraIndex();
    void setCameraIndex(int cameraIndex);

    VideoTools::StreamingStatus getStreamingStatus();
    void setStreamingStatus(VideoTools::StreamingStatus streamingStatus);

    int getMode();
    void setMode(VideoTools::Mode mode);

    VideoTools::LandmarkState getLandmarkState();
    void setLandmarkState(VideoTools::LandmarkState landmarkState);

    int getFoundFace();

public slots:

private slots:
    void processFrame();

private:
    void getFrame();
    void updateBounds();
    void openCaptureDevice();
    void updateLandmarks();

    void drawLandmarks72(QPainter* painter);
    void drawBounds72(QPainter* painter);
    void drawLandmarks13(QPainter* painter);
    void drawBounds13(QPainter* painter);

    void landmark72();
    void landmark13();

    int m_cameraIndex;

    VideoTools::StreamingStatus m_streamingStatus;
    void streamingStatusChanged();

    int m_mode;
    void modeChanged();

    VideoTools::LandmarkState m_landmarkState;
    void landmarkStateChanged();

    DisplayLabel *m_display;

    QTimer *timer;
    cv::Mat_<unsigned char> matOriginal;
    cv::Mat_<unsigned char> matVideo;
    cv::Mat_<unsigned char> matGray;
    QImage *imgOriginal;
    QImage *imgVideo;
    QImage *imgVerifyOriginal;
    QImage *imgVerifyProcessed;

    cv::VideoCapture m_capVideoStream;
    int foundface;
    float landmarks[2*stasm_NLANDMARKS];

    const int NNASALLANDMARKS;
    QVector<int> XLocs13; //holds the 13 X locations of the nasal landmarks within the landmarks vector
    QVector<int> YLocs13; //holds the 13 Y locations of the nasal landmarks within the landmarks vector
    QVector<int> bounds72; //holds the 6 boundary positions of the face landmarks (top, right, bottom, left, Xcenter, Ycenter, width, height)
    QVector<int> bounds13; //holds the 6 boundary positions of the nose landmarks (top, right, bottom, left, Xcenter, Ycenter, width, height)

    QPainter* painterVideo;
    QPainter* painterImage;
    QPen penLandmarks;
    QPen penBounds;
    QBrush brushClear;
    QBrush brushBlack;

};

#endif // VIDEOTOOLS_H
