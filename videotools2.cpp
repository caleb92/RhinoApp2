#include "videotools2.h"
#include <QDebug>

VideoTools::VideoTools(DisplayLabel *display, QObject *parent) :
    QObject(parent),
    m_cameraIndex(0),
    m_streamingStatus(StreamingOff),
    m_displayMode(VideoMode),
    m_landmarkMode(Landmark72),
    m_bounds13(false),
    m_bounds72(true),
    m_scaleCirc(false),
    m_scaleLine(true),
    NNASALLANDMARKS(13)
{
    XLocs13 << 42 << 44 << 96 << 98 << 100 << 102 << 104 << 106 << 108 << 110 << 112 << 114 << 116;
    YLocs13 << 43 << 45 << 97 << 99 << 101 << 103 << 105 << 107 << 109 << 111 << 113 << 115 << 117;

    m_display = display;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFrame()));

    penLandmarks.setWidth(1);
    penLandmarks.setColor(Qt::black);

    penBounds.setWidth(1);
    penBounds.setColor(Qt::white);
    penBounds.setCapStyle(Qt::RoundCap);
    penBounds.setStyle(Qt::DashLine);

    brushLandmarks.setColor(Qt::white);
    brushLandmarks.setStyle(Qt::SolidPattern);
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
    qDebug() << "VideoTools setStreamingStatus";

    if (m_streamingStatus != streamingStatus) {
        m_streamingStatus = streamingStatus;

        switch (streamingStatus) {
        case StreamingOff:
            qDebug() << "StreamingOff";
            timer->stop();
            break;
        case StreamingOn:
            qDebug() << "StreamingOn";
            timer->start(20);
            break;
        }

    }
}

VideoTools::DisplayMode VideoTools::getDisplayMode()
{
    return m_displayMode;
}

void VideoTools::setDisplayMode(VideoTools::DisplayMode displayMode)
{
    if ( m_displayMode != displayMode ) {
        m_displayMode = displayMode;

        switch (displayMode) {
        case VideoMode:
            break;
        case ImageMode:
            setStreamingStatus(StreamingOff);
            processFrame();
            break;
        }

    }
}

VideoTools::LandmarkMode VideoTools::getLandmarkState()
{
    return m_landmarkMode;
}

void VideoTools::setLandmarkState(VideoTools::LandmarkMode landmarkState)
{
    qDebug() << "VideoTools setLandmarkState";

    if (m_landmarkMode != landmarkState) {
        m_landmarkMode = landmarkState;

        processFrame();
    }
}

bool VideoTools::isBounds13()
{
    return m_bounds13;
}

void VideoTools::setBounds13(bool bounds13On)
{
    m_bounds13 = bounds13On;
}

bool VideoTools::isBounds72()
{
    return m_bounds72;
}

void VideoTools::setBOunds72(bool bounds72On)
{
    m_bounds72 = bounds72On;
}

bool VideoTools::isScaleCirc()
{
    return m_scaleCirc;
}

void VideoTools::setScaleCirc(bool scaleCircOn)
{
    m_scaleCirc = scaleCircOn;
}

bool VideoTools::isScaleLine()
{
    return m_scaleLine;
}

void VideoTools::setScaleLine(bool scaleLineOn)
{
    m_scaleLine = scaleLineOn;
}

int VideoTools::getFoundFace()
{
    return foundface;
}

void VideoTools::processFrame()
{
    qDebug() << "VideoTools processFrame()";

    QSize sizeSource;
    QPoint topLeftSource;

    if (m_displayMode == VideoMode) {
        qDebug() << "processFrame VIDEOMODE";
        getFrame();
        updateLandmarks();

        sizeSource = imgOriginal->size();
        topLeftSource = QPoint(0,0);

    } else if (m_displayMode == ImageMode) {
        qDebug() << "processFrame IMAGEMODE";

        sizeSource = rect72.size();
        topLeftSource = rect72.topLeft();

        setScaleCirc(true);
    }

    updateRect13();
    updateRect72();

    if (imgDisplay.isNull())
        imgDisplay = QImage(m_display->size(), QImage::Format_RGB888);

    if (!painter.isActive())
        painter.begin(&imgDisplay);

    QSize sizeOriginal = imgOriginal->size();
    QSize sizeDisplay = imgDisplay.size();

    //QSize sizeSource depends on if in Video or Image mode (defined above)
    QRect rectSource(topLeftSource, sizeSource);
    QSize sizeTarget = sizeSource.scaled(sizeDisplay, Qt::KeepAspectRatio);
    QRect rectTarget(QPoint(0,0), sizeTarget);

    float targetScale = (float)sizeTarget.height() / sizeSource.height();
    int   targetXTrans = sizeDisplay.width()/2 - sizeTarget.width()/2 ;//- topLeftSource.x();
    int   targetYTrans = sizeDisplay.height()/2 - sizeTarget.height()/2 ;//- topLeftSource.y();

    rectTarget.moveLeft(targetXTrans);

    painter.fillRect(imgDisplay.rect(), Qt::black);
    painter.drawImage(rectTarget, *imgOriginal, rectSource);

    QTransform transform;
    transform.translate(targetXTrans,0);
    transform.scale(targetScale,targetScale);

    if (m_displayMode == ImageMode) {
        transform.translate(-topLeftSource.x() , -topLeftSource.y());
    }

    painter.setTransform(transform);

    switch (m_landmarkMode) {
    case LandmarkNone:
        break;
    case Landmark13:
        drawLandmarks13();
        break;
    case Landmark72:
        drawLandmarks72();
        break;
    }


    if (m_bounds13) {drawRect13();}
    if (m_bounds72) {drawRect72();}
    if (m_scaleCirc) {drawScaleCirc();}
    if (m_scaleLine) {drawScaleLine();}

    painter.resetTransform();

    m_display->setPixmap(QPixmap::fromImage(imgDisplay));
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

    imgOriginal = new QImage((const uchar*)matOriginal.data,
                matOriginal.cols,
                matOriginal.rows,
                matOriginal.step,
                QImage::Format_RGB888);
}

void VideoTools::updateRect72()
{
    //udpate bounds for 72 Facial landmarks;
    rect72.setLeft(m_display->width());
    rect72.setRight(0);
    rect72.setTop(m_display->height());
    rect72.setBottom(0);

    int xLoc;
    int yLoc;
    for (int i = 0; i < stasm_NLANDMARKS; i++)
    {
        xLoc = i*2;
        yLoc = i*2+1;

        if(landmarks[xLoc]<(rect72.left()))   {rect72.setLeft(qRound(landmarks[xLoc]));}
        if(landmarks[xLoc]>rect72.right())  {rect72.setRight(qRound(landmarks[xLoc]));}
        if(landmarks[yLoc]<rect72.top())    {rect72.setTop(qRound(landmarks[yLoc]));}
        if(landmarks[yLoc]>rect72.bottom()) {rect72.setBottom(qRound(landmarks[yLoc]));}
    }
}

void VideoTools::updateRect13()
{
    //udpate bounds for 13 Nasal landmarks;
    rect13.setLeft(m_display->width());
    rect13.setRight(0);
    rect13.setTop(m_display->height());
    rect13.setBottom(0);

    int xLoc;
    int yLoc;
    for( int i = 0 ; i<NNASALLANDMARKS ; i++ )
    {
        xLoc = XLocs13[i];
        yLoc = YLocs13[i];

        if(landmarks[xLoc]<(rect13.left()))   {rect13.setLeft(qRound(landmarks[xLoc]));}
        if(landmarks[xLoc]>rect13.right())  {rect13.setRight(qRound(landmarks[xLoc]));}
        if(landmarks[yLoc]<rect13.top())    {rect13.setTop(qRound(landmarks[yLoc]));}
        if(landmarks[yLoc]>rect13.bottom()) {rect13.setBottom(qRound(landmarks[yLoc]));}
    }
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
    cv::cvtColor(matOriginal,   //in default BGR format
                     matGray,       //in RGB mono format
                     CV_BGR2GRAY);

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

void VideoTools::drawLandmarks72()
{
    qDebug() << "VideoTools drawLandmarks72";
    painter.setPen(penLandmarks);
    painter.setBrush(brushLandmarks);
    for (int i = 0; i < stasm_NLANDMARKS; i++)
    {
        painter.drawEllipse(qRound(landmarks[i*2]), qRound(landmarks[i*2+1]),2,2);
    }
}

void VideoTools::drawRect72()
{
    qDebug() << "VideoTools drawBounds72";
    painter.setPen(penBounds);
    painter.setBrush(brushBounds);
    painter.drawRect(rect72);
}

void VideoTools::drawLandmarks13()
{
    qDebug() << "VideoTools drawLandmarks13";
    painter.setPen(penLandmarks);
    painter.setBrush(brushLandmarks);
    for (int i = 0; i<NNASALLANDMARKS ; i++) {
        painter.drawEllipse(qRound(landmarks[XLocs13[i]]), qRound(landmarks[YLocs13[i]]),2,2);
    }
}

void VideoTools::drawRect13()
{
    qDebug() << "VideoTools drawBounds13";
    painter.setPen(penBounds);
    painter.setBrush(brushBounds);
    painter.drawRect(rect13);
}

void VideoTools::drawScaleCirc()
{
    painter.save();

    QBrush brushScale;
    brushScale.setStyle(Qt::NoBrush);
    painter.setBrush(brushScale);

    QPen penTickMinor;
    penTickMinor.setColor(Qt::gray);
    penTickMinor.setStyle(Qt::SolidLine);
    penTickMinor.setWidth(2);
    penTickMinor.setCapStyle(Qt::FlatCap);
    penTickMinor.setJoinStyle(Qt::RoundJoin);

    QPen penTickMajor(penTickMinor);
    penTickMajor.setColor(Qt::darkGray);
    penTickMajor.setWidth(3);

    QPen penScale;
    penScale.setColor(Qt::darkGray);
    penScale.setStyle(Qt::SolidLine);
    penScale.setWidth(1);

    const int scaleInset = 7;
    int radius =(rect72.width() < rect72.height()) ?
                (rect72.width()/2-scaleInset) :
                (rect72.height()/2-scaleInset);

    QRect rectScaleCirc;
    rectScaleCirc.setWidth(2*radius);
    rectScaleCirc.setHeight(2*radius);
    rectScaleCirc.moveCenter(rect72.center());

    painter.setPen(penScale);
    painter.drawEllipse(rectScaleCirc);

    painter.translate(rectScaleCirc.center());

    const int tickAngleMinor = 5;
    const int tickAngleMajor = 45;
    for (int angle = 0 ; angle<=360 ; angle+=tickAngleMinor ) {
        if (angle%tickAngleMajor == 0) {
            painter.setPen(penTickMajor);
            painter.drawLine(0, radius-5, 0 ,radius+5);
        } else {
            painter.setPen(penTickMinor);
            painter.drawLine(0,radius-3,0,radius+3);
        }

        painter.rotate(tickAngleMinor);
    }

    painter.restore();
}

void VideoTools::drawScaleLine()
{
    qDebug() << "VideoTools drawScaleLine()";

    /********************
    Program creates a rectangle, draws the bottom and left edges of that rectangle,
    and adds tick marks on those lines at desired spacing
    *********************/

    painter.save();
    //QPainter painter(this);

    //KEPT THE SAME PENS
    QBrush brushScale;
    brushScale.setStyle(Qt::NoBrush);
    painter.setBrush(brushScale);

    QPen penTickMinor;
    penTickMinor.setColor(Qt::gray);
    penTickMinor.setStyle(Qt::SolidLine);
    penTickMinor.setWidth(1);
    penTickMinor.setCapStyle(Qt::FlatCap);
    penTickMinor.setJoinStyle(Qt::RoundJoin);

    QPen penTickMajor(penTickMinor);
    penTickMajor.setColor(Qt::darkGray);
    penTickMajor.setWidth(2);

    QPen penScale;
    penScale.setColor(Qt::darkGray);
    penScale.setStyle(Qt::SolidLine);
    penScale.setWidth(1);

    QRect rectScaleLine = rect72.adjusted(5,5,-5,-5);

    painter.setPen(penScale);
    painter.drawLine(rectScaleLine.bottomLeft(), rectScaleLine.bottomRight()); //DRAWS BOTTOM EDGE OF RECTANGLE
    painter.drawLine(rectScaleLine.bottomLeft(), rectScaleLine.topLeft()); //DRAWS LEFT EDGE OF RECTANGLE

    //CHANGE AS NEEDED
    int tickwidth = 3; //size of tick
    int tickgap = 10; //tick spacing

    int left = rectScaleLine.left(); //X-COORD OF LEFT EDGE
    int bottom = rectScaleLine.bottom(); //Y-COORD OF BOTTOM EDGE
    int count = 0;

    //DRAWS TICKS ON X AXIS
    while (left < rectScaleLine.right())
    {
        if (count%5 == 0)
        {
            painter.setPen(penTickMajor);
            painter.drawLine(left, bottom + tickwidth/2, left, bottom - tickwidth/2);
        }
        else
        {
            painter.setPen(penTickMinor);
            painter.drawLine(left, bottom + tickwidth/2, left, bottom - tickwidth/2); //DRAWS TICKS
        }
        left = left + tickgap; //MOVES X COORD TO RIGHT
        count = count + 1;
    }

    //RESETTING VALUES
    left = rectScaleLine.left();
    bottom = rectScaleLine.bottom();
    count = 0;

    //DRAWS TICK ON Y AXIS
    while (bottom < rectScaleLine.top())
    {
        if (count%5 == 0)
        {
            painter.setPen(penTickMajor);
            painter.drawLine(left - tickwidth/2, bottom, left + tickwidth/2, bottom);
        }
        else
        {
            painter.setPen(penTickMinor);
            painter.drawLine(left - tickwidth/2, bottom, left + tickwidth/2, bottom);
        }
        bottom = bottom - tickgap; //MOVES Y COORD UP
        count = count + 1;
    }


}
