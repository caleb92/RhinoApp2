#include "videowindow.h"

#include <QDebug>

VideoWindow::VideoWindow(QWidget *parent) :
    QWidget(parent),
    iconPlay("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.control.play.png"),
    iconPause("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.control.pause.png"),
    lblVerifIsStarted(false)
{
    qDebug() << "Constructor Start";

    //size policy for all option buttons
    const QSizePolicy sizepolOptionButtons( QSizePolicy::Preferred, QSizePolicy::Preferred );
    const QSizePolicy sizepolOptionGroups( QSizePolicy::Preferred, QSizePolicy::Fixed );
    const QSizePolicy sizepolOptionBar( QSizePolicy::Fixed, QSizePolicy::Preferred );

    const QSize sizePlayIcon(96,96);
    const QSize sizeIcons(18,18);

    //populate pageVerif (an empty QWidget)
    layVerif = new QGridLayout(this);

    lblVerifStart = new QLabel;
    lblVerifStart->setPixmap(QPixmap("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/VideoWindowWaiting.png"));
    lblVerifStart->setAlignment(Qt::AlignCenter);
    layVerif->addWidget(lblVerifStart,0,1);
    //lblVerif = new QLabel;
    lblVerif = new DisplayLabel;
    lblVerif->setAlignment(Qt::AlignCenter);
    lblVerif->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    optionsVerif = new QWidget;
    optionsVerif->setSizePolicy(sizepolOptionBar);
    layVerif->addWidget(optionsVerif,0,0);

    layOptionsVerif = new QVBoxLayout;
    optionsVerif->setLayout(layOptionsVerif);
    groupDisplay = new QGroupBox;
    groupDisplay->setTitle("Display 1");
    groupDisplay->setSizePolicy(sizepolOptionGroups);
    layOptionsVerif->addWidget(groupDisplay);
    groupLandmarks = new QGroupBox;
    groupLandmarks->setTitle("Landmarks");
    groupLandmarks->setSizePolicy(sizepolOptionGroups);
    layOptionsVerif->addWidget(groupLandmarks);
    groupSymmetry = new QGroupBox;
    groupSymmetry->setTitle("Symmetry");
    groupSymmetry->setSizePolicy(sizepolOptionGroups);
    layOptionsVerif->addWidget(groupSymmetry);

    QVBoxLayout *layDisplayGroup = new QVBoxLayout;
    groupDisplay->setLayout(layDisplayGroup);
    btnDisplayPlay = new QToolButton;
    btnDisplayPlay->setText("Play");
    btnDisplayPlay->setCheckable(true);
    btnDisplayPlay->setSizePolicy(sizepolOptionButtons);
    btnDisplayPlay->setIcon(iconPlay);
    btnDisplayPlay->setIconSize(sizePlayIcon);
    layDisplayGroup->addWidget(btnDisplayPlay);

    QHBoxLayout *layLandmarkGroup = new QHBoxLayout;
    groupLandmarks->setLayout(layLandmarkGroup);
    QButtonGroup *btnGroupLandmarks = new QButtonGroup;
    btnGroupLandmarks->setExclusive(true);
    btnLandmarksNone = new QToolButton;
    btnLandmarksNone->setText("0");
    btnLandmarksNone->setCheckable(true);
    btnLandmarksNone->setChecked(true);
    btnLandmarksNone->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarksNone);
    layLandmarkGroup->addWidget(btnLandmarksNone);
    btnLandmarks13 = new QToolButton;
    btnLandmarks13->setText("13");
    btnLandmarks13->setCheckable(true);
    btnLandmarks13->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarks13);
    layLandmarkGroup->addWidget(btnLandmarks13);
    btnLandmarks72 = new QToolButton;
    btnLandmarks72->setText("72");
    btnLandmarks72->setCheckable(true);
    btnLandmarks72->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarks72);
    layLandmarkGroup->addWidget(btnLandmarks72);

    QHBoxLayout *laySymmetryGroup = new QHBoxLayout;
    groupSymmetry->setLayout(laySymmetryGroup);
    btnVCenterLine = new QToolButton;
    btnVCenterLine->setText("|");
    btnVCenterLine->setCheckable(true);
    btnVCenterLine->setSizePolicy(sizepolOptionButtons);
    laySymmetryGroup->addWidget(btnVCenterLine);
    btnHCenterLine = new QToolButton;
    btnHCenterLine->setText("---");
    btnHCenterLine->setCheckable(true);
    btnHCenterLine->setSizePolicy(sizepolOptionButtons);
    laySymmetryGroup->addWidget(btnHCenterLine);

    layOptionsVerif->addStretch();

    video = new VideoTools(lblVerif,this);

    connect(btnDisplayPlay, SIGNAL(clicked()), this, SLOT(on_btnDisplayPlay_clicked()));

    connect(btnLandmarksNone, SIGNAL(clicked()), this, SLOT(on_btnLandmarksNone_clicked()));
    connect(btnLandmarks13, SIGNAL(clicked()), this, SLOT(on_btnLandmarks13_clicked()));
    connect(btnLandmarks72, SIGNAL(clicked()), this, SLOT(on_btnLandmarks72_clicked()));

    qDebug() << "Constructor end";
}

void VideoWindow::on_btnDisplayPlay_clicked()
{
    qDebug() << "on_btnDisplayPlay_clicked start";
    if( !lblVerifIsStarted ) {
        lblVerifIsStarted = true;
        layVerif->removeWidget(lblVerifStart);
        layVerif->addWidget(lblVerif,0,1);
    }

    VideoTools::StreamingStatus streamingStatus = video->getStreamingStatus();

    if(streamingStatus == VideoTools::StreamingOn) {
        video->setStreamingStatus(VideoTools::NotStreaming);
        btnDisplayPlay->setIcon(iconPlay);
        qDebug() << "Stopped Video Streaming";
    } else {
        video->setStreamingStatus(VideoTools::StreamingOn);
        btnDisplayPlay->setIcon(iconPause);
        qDebug() << "Initiated Video Streaming";
    }

    qDebug() << "on_btnDisplayPlay_clicked end";
}

void VideoWindow::on_btnLandmarksNone_clicked()
{
    video->setLandmarkState(VideoTools::LandmarkNone);
}

void VideoWindow::on_btnLandmarks13_clicked()
{
    video->setLandmarkState(VideoTools::Landmark13);
}

void VideoWindow::on_btnLandmarks72_clicked()
{
    video->setLandmarkState(VideoTools::Landmark72);
}

void VideoWindow::on_btnVCenterLine_clicked()
{
    //draw vertical centerline
}

void VideoWindow::on_btnHCenterLine_clicked()
{
    //draw horizontal center line
}
