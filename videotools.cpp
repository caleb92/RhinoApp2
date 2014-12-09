#include "videotools.h"
#include <QDebug>

VideoTools::VideoTools(DisplayLabel *display, QObject *parent) :
    QObject(parent),
    m_cameraIndex(0),
    m_streamingStatus(NotStreaming),
    m_mode(VIDEOMODE),
    m_landmarkState(Landmark72),
    NNASALLANDMARKS(13)
{
    XLocs13 << 42 << 44 << 96 << 98 << 100 << 102 << 104 << 106 << 108 << 110 << 112 << 114 << 116;
    YLocs13 << 43 << 45 << 97 << 99 << 101 << 103 << 105 << 107 << 109 << 111 << 113 << 115 << 117;

    bounds72.resize(8);//set max size to 6 (top,right,bottom,left,xcenter,ycenter, width, height)
    bounds13.resize(8);//set max size to 6 (top,right,bottom,left,xcenter,ycenter, width, height)

    m_display = display;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFrame()));

    painterVideo = new QPainter;
    painterImage = new QPainter;

    penLandmarks.setWidth(1);
    penLandmarks.setColor(Qt::black);

    penBounds.setWidth(1);
    penBounds.setColor(Qt::white);
    penBounds.setCapStyle(Qt::RoundCap);
    penBounds.setStyle(Qt::DashLine);

    brushBlack.setColor(Qt::white);
    brushBlack.setStyle(Qt::SolidPattern);
}

VideoTools::~VideoTools()
{
    m_capVideoStream.release();
}

int VideoTools::getCameraIndex()
{
    return m_cameraIndex;
}

void VideoTools::setCameraIndex(int cameraIndex)
{
    m_cameraIndex = cameraIndex;
}

VideoTools::StreamingStatus VideoTools::getStreamingStatus() {
    return m_streamingStatus;
}

void VideoTools::setStreamingStatus(VideoTools::StreamingStatus streamingStatus)
{
    qDebug() << "setStreamingStatus";
    m_streamingStatus = streamingStatus;
    streamingStatusChanged();
}

int VideoTools::getMode()
{
    return m_mode;
}

void VideoTools::setMode(VideoTools::Mode mode)
{
    if ( m_mode != mode ) {
        m_mode = mode;
        modeChanged();
    }
}

VideoTools::LandmarkState VideoTools::getLandmarkState()
{
    return m_landmarkState;
}

void VideoTools::setLandmarkState(VideoTools::LandmarkState landmarkState)
{
    qDebug() << "VideoTools setLandmarkState";
    m_landmarkState = landmarkState;
    landmarkStateChanged();
}

int VideoTools::getFoundFace()
{
    return foundface;
}

void VideoTools::processFrame()
{
    getFrame();
    updateLandmarks();
    updateBounds();

    if (!painterVideo->isActive()) {
        painterVideo->begin(imgVideo);
    }

    drawBounds72(painterVideo);
    drawLandmarks72(painterVideo);

    m_display->setPixmap(QPixmap::fromImage(imgVideo->scaled(m_display->size(), Qt::KeepAspectRatio)));
}

void VideoTools::getFrame()
{
    if(!(m_capVideoStream.isOpened()))
        openCaptureDevice();


    m_capVideoStream.read(matOriginal);
    if(matOriginal.empty() == true)
    {
        qDebug() << "Failed to read from capture device!";
    }

    cv::cvtColor(matOriginal,   //in default BGR format
                 matOriginal,      //in RGB color format
                 CV_BGR2RGB);

    matOriginal.copyTo(matVideo);

    imgOriginal = new QImage((uchar*)matOriginal.data,
                             matOriginal.cols,
                             matOriginal.rows,
                             matOriginal.step,
                             QImage::Format_RGB888);

    imgVideo = new QImage((uchar*)matVideo.data,
                             matVideo.cols,
                             matVideo.rows,
                             matVideo.step,
                             QImage::Format_RGB888);

    cv::cvtColor(matOriginal,   //in default BGR format
                 matGray,       //in RGB mono format
                 CV_BGR2GRAY);
}

void VideoTools::updateBounds()
{
    /**************************************/
    //udpate bounds for 72 Facial landmarks;
    float xSum = 0.0;
    float ySum = 0.0;

    //reset bounds to the entire display
    bounds72[LEFT] = m_display->width();
    bounds72[RIGHT] = 0;
    bounds72[TOP] = m_display->height();
    bounds72[BOTTOM] = 0;

    int xLoc;
    int yLoc;
    for (int i = 0; i < stasm_NLANDMARKS; i++)
    {
        xLoc = i*2;
        yLoc = i*2+1;

        xSum += landmarks[xLoc];
        ySum += landmarks[yLoc];

        if(landmarks[xLoc]<bounds72[LEFT])   {bounds72[LEFT]  =qRound(landmarks[xLoc]);}
        if(landmarks[xLoc]>bounds72[RIGHT])  {bounds72[RIGHT] =qRound(landmarks[xLoc]);}
        if(landmarks[yLoc]<bounds72[TOP])    {bounds72[TOP]   =qRound(landmarks[yLoc]);}
        if(landmarks[yLoc]>bounds72[BOTTOM]) {bounds72[BOTTOM]=qRound(landmarks[yLoc]);}
    }

    bounds72[XCENTER] = qRound ( xSum/13.0 );
    bounds72[YCENTER] = qRound ( ySum/13.0 );
    bounds72[WIDTH] = bounds72[RIGHT] - bounds72[LEFT];
    bounds72[HEIGHT] = bounds72[BOTTOM] - bounds72[TOP];

    /**************************************/
    //udpate bounds for 13 Nasal landmarks;
    xSum = 0.0;
    ySum = 0.0;

    //reset bounds to the entire display
    bounds13[LEFT] = m_display->width();
    bounds13[RIGHT] = 0;
    bounds13[TOP] = m_display->height();
    bounds13[BOTTOM] = 0;

    for( int i = 0 ; i<NNASALLANDMARKS ; i++ )
    {
        xLoc = XLocs13[i];
        yLoc = YLocs13[i];

        xSum += landmarks[xLoc];
        ySum += landmarks[yLoc];

        if(landmarks[xLoc]<bounds13[LEFT])   {bounds13[LEFT]  =qRound(landmarks[xLoc]);}
        if(landmarks[xLoc]>bounds13[RIGHT])  {bounds13[RIGHT] =qRound(landmarks[xLoc]);}
        if(landmarks[yLoc]<bounds13[TOP])    {bounds13[TOP]   =qRound(landmarks[yLoc]);}
        if(landmarks[yLoc]>bounds13[BOTTOM]) {bounds13[BOTTOM]=qRound(landmarks[yLoc]);}
    }

    bounds13[XCENTER] = qRound ( xSum/13.0 );
    bounds13[YCENTER] = qRound ( ySum/13.0 );
    bounds13[WIDTH] = bounds13[RIGHT] - bounds13[LEFT];
    bounds13[HEIGHT] = bounds13[BOTTOM] - bounds13[TOP];
}

void VideoTools::openCaptureDevice()
{
    if(!m_capVideoStream.open(m_cameraIndex))
    {
        qDebug() << "Cannot open capture device!";
    }
}

void VideoTools::updateLandmarks()
{
    if (!stasm_search_single(   &foundface,
                                landmarks,
                                (const char*)matGray.data,
                                matGray.cols,
                                matGray.rows,
                                "/stasm_search_single_ERRORS",
                                "../data"))
    {
        qFatal("Error in stasm_search_single");
    }

    if (foundface)
    {
        stasm_force_points_into_image(landmarks, matGray.cols, matGray.rows);
    }
}

void VideoTools::drawLandmarks72(QPainter *painter)
{
    qDebug() << "VideoTools drawLandmarks72";
    painter->setPen(penLandmarks);
    painter->setBrush(brushBlack);

    for (int i = 0; i < stasm_NLANDMARKS; i++)
    {
        //painter->drawPoint(qRound(landmarks[i*2]), qRound(landmarks[i*2+1]));
        painter->drawEllipse(qRound(landmarks[i*2]), qRound(landmarks[i*2+1]),2,2);
    }
}

void VideoTools::drawBounds72(QPainter *painter)
{
    qDebug() << "VideoTools drawBounds72";
    painter->setPen(penBounds);
    painter->setBrush(brushClear);
    painter->drawLine(bounds72[XCENTER], bounds72[TOP], bounds72[XCENTER], bounds72[BOTTOM]);
    painter->drawRect(bounds72[LEFT], bounds72[TOP], bounds72[WIDTH], bounds72[HEIGHT]);
}

void VideoTools::drawLandmarks13(QPainter* painter)
{
    qDebug() << "VideoTools drawLandmarks13";
    painter->setPen(penLandmarks);
    painter->setBrush(brushClear);
    for (int i = 0; i<NNASALLANDMARKS ; i++) {
        painter->drawPoint( qRound(landmarks[XLocs13[i]]),qRound(landmarks[YLocs13[i]]));
    }
}

void VideoTools::drawBounds13(QPainter *painter)
{
    qDebug() << "VideoTools drawBounds13";
    painter->setPen(penBounds);
    painter->setBrush(brushClear);
    painter->drawLine(bounds13[XCENTER], bounds13[TOP], bounds13[XCENTER], bounds13[BOTTOM]);
    painter->drawRect(bounds13[LEFT], bounds13[TOP], bounds13[WIDTH], bounds13[HEIGHT]);
}

void VideoTools::streamingStatusChanged()
{
    if( m_streamingStatus == NotStreaming ) {
        qDebug() << "streaming status: NotStreaming";
        timer->stop();
    } else if( m_streamingStatus == StreamingOn ) {
        qDebug() << "streaming status: StreamingOn";
        timer->start(20);
    }
}

void VideoTools::modeChanged()
{
    qDebug() << "videoTools modeChanged";
    if (m_mode == IMAGEMODE) {
        setStreamingStatus(NotStreaming);
        imgVerifyOriginal = new QImage(imgOriginal->copy(bounds72[LEFT], bounds72[TOP], bounds72[WIDTH], bounds72[HEIGHT]));
        //imgVerifyProcessed = new QImage(imgVerifyOriginal->copy(imgVerifyOriginal->rect()));
        imgVerifyProcessed = new QImage(*imgVerifyOriginal);
        qDebug() << "Original:  " << imgVerifyOriginal;
        qDebug() << "Processed: " << imgVerifyProcessed;

        int xLoc,yLoc;
        for (int i=0 ; i<stasm_NLANDMARKS ; i++) {
            xLoc = i*2;
            yLoc = i*2+1;
            landmarks[xLoc] -= bounds72[LEFT];
            landmarks[yLoc] -= bounds72[TOP];
            //qDebug() << landmarks[xLoc] << " , " << landmarks[yLoc];
        }
        updateBounds();

        if (!painterImage->isActive()) {
            painterImage->begin(imgVerifyProcessed);
        }

        drawLandmarks72(painterImage);
        drawBounds13(painterImage);

        m_display->setPixmap(QPixmap::fromImage(imgVerifyProcessed->scaled(m_display->size(), Qt::KeepAspectRatio)));
    }
}

void VideoTools::landmarkStateChanged()
{
    qDebug() << "VideoTools landmarkStateChanged";
    //imgVerifyProcessed = new QImage(imgVerifyOriginal->copy(imgVerifyOriginal->rect()));
    //delete imgVerifyProcessed;//causes crash
    imgVerifyProcessed = new QImage(*imgVerifyOriginal);
    //imgVerifyProcessed = new QImage(imgVerifyOriginal->copy(imgVerifyOriginal->rect()));



    if (!painterImage->isActive()) {
        painterImage->begin(imgVerifyProcessed);
    }

    switch (m_landmarkState) {
    case LandmarkNone:
        break;
    case Landmark13:
        drawLandmarks13(painterImage);
        break;
    case Landmark72:
        drawLandmarks72(painterImage);
        break;
    }
    QPainter test(imgVerifyOriginal);
    test.drawRect(3,3,10,10);

    qDebug() << painterImage->device();
    drawLandmarks72(painterImage);

    qDebug() << "Original:  " << imgVerifyOriginal;
    qDebug() << "Processed: " << imgVerifyProcessed;

    m_display->setPixmap(QPixmap::fromImage(imgVerifyProcessed->scaled(m_display->size(), Qt::KeepAspectRatio)));
}
