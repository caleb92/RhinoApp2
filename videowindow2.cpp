#include "videowindow2.h"

#include <QDebug>

VideoWindow::VideoWindow(QWidget *parent) :
    QWidget(parent),
    iconPlay("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.control.play.png"),
    iconPause("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.control.pause.png"),
    lblVerifIsStarted(false)
{
    createVideoWindow();

    video = new VideoTools(lblDisplay,this);

    connect(btnPlayOrPause, SIGNAL(clicked()), this, SLOT(on_btnPlayOrPause_clicked()));
    connect(btnVerify, SIGNAL(clicked()), this, SLOT(on_btnVerify_clicked()));

    connect(btnLandmarksNone, SIGNAL(clicked()), this, SLOT(on_btnLandmarksNone_clicked()));
    connect(btnLandmarks13, SIGNAL(clicked()), this, SLOT(on_btnLandmarks13_clicked()));
    connect(btnLandmarks72, SIGNAL(clicked()), this, SLOT(on_btnLandmarks72_clicked()));

    groupLandmarks->hide();
}

void VideoWindow::on_btnPlayOrPause_clicked()
{
    qDebug() << "on_btnDisplayPlay_clicked start";

    if( !lblVerifIsStarted ) {
        lblVerifIsStarted = true;
        layVideoWindow->removeWidget(lblDisplayStart);
        layVideoWindow->addWidget(lblDisplay,0,1);
        lblDisplay->setStyleSheet("background-color: #EEEEEE");
    }

    VideoTools::StreamingStatus streamingStatus = video->getStreamingStatus();

    if(streamingStatus == VideoTools::StreamingOn) {
        video->setStreamingStatus(VideoTools::StreamingOff);
        btnPlayOrPause->setIcon(iconPlay);
        btnPlayOrPause->setText("Play");
        qDebug() << "Stopped Video Streaming";
    } else {
        video->setStreamingStatus(VideoTools::StreamingOn);
        btnPlayOrPause->setIcon(iconPause);
        btnPlayOrPause->setText("Pause");
        btnVerify->setEnabled(true);
        qDebug() << "Initiated Video Streaming";
    }

    qDebug() << "on_btnDisplayPlay_clicked end";
}

void VideoWindow::on_btnVerify_clicked()
{
    btnPlayOrPause->hide();
    btnVerify->hide();

    groupLandmarks->show();
    optionsBar->updateGeometry();

    video->setDisplayMode(VideoTools::ImageMode);

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

void VideoWindow::createVideoWindow()
{
    //size policies
    const QSizePolicy sizepolOptionButtons( QSizePolicy::Preferred, QSizePolicy::Preferred );
    const QSizePolicy sizepolOptionGroups( QSizePolicy::Preferred, QSizePolicy::Fixed );
    const QSizePolicy sizepolOptionBar( QSizePolicy::Preferred, QSizePolicy::Preferred );
    const QSizePolicy sizepolDisplay( QSizePolicy::Expanding, QSizePolicy::Expanding);
    //sizes
    const QSize sizeStartIcons(96,96);
    const QSize sizeIcons(18,18);

    //layout for video window widget
    layVideoWindow = new QGridLayout(this);
    //the label displayed on start up
    lblDisplayStart = new QLabel;
    lblDisplayStart->setPixmap(QPixmap("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/VideoWindowWaiting.png"));
    lblDisplayStart->setSizePolicy(sizepolDisplay);
    lblDisplayStart->setAlignment(Qt::AlignCenter);
    layVideoWindow->addWidget(lblDisplayStart,0,1);
    //the label display during verification
    lblDisplay = new DisplayLabel;
    lblDisplay->setSizePolicy(sizepolDisplay);
    lblDisplay->setAlignment(Qt::AlignCenter);
    lblDisplay->setSizePolicy( sizepolDisplay );
    //widget to hold options menu
    optionsBar = new QWidget;
    optionsBar->setSizePolicy(sizepolOptionBar);

    layVideoWindow->addWidget(optionsBar,0,0);

    //layout for options menu widget (at start display)
    QVBoxLayout* layOptions = new QVBoxLayout;
    optionsBar->setLayout(layOptions);

    //startup widgets
    //button to play or pause video
    btnPlayOrPause = new QToolButton;
    btnPlayOrPause->setText("Play");
    btnPlayOrPause->setCheckable(true);
    btnPlayOrPause->setSizePolicy(sizepolOptionButtons);
    btnPlayOrPause->setIcon(iconPlay);
    btnPlayOrPause->setIconSize(sizeStartIcons);
    layOptions->addWidget(btnPlayOrPause);
    //button to begin verification on still frame
    btnVerify = new QToolButton;
    btnVerify->setText("Begin Verification");
    btnVerify->setCheckable(true);
    btnVerify->setSizePolicy(sizepolOptionButtons);
    btnVerify->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.check.png"));
    btnVerify->setIconSize(sizeStartIcons);
    btnVerify->setEnabled(false);
    layOptions->addWidget(btnVerify);

    //verification widgets
    //group for landmark options
    groupLandmarks = new QGroupBox;
    groupLandmarks->setTitle("Landmarks");
    groupLandmarks->setSizePolicy(sizepolOptionGroups);
    layOptions->addWidget(groupLandmarks);
    //layout for landmark group
    QHBoxLayout *layLandmarkGroup = new QHBoxLayout;
    groupLandmarks->setLayout(layLandmarkGroup);
    QButtonGroup *btnGroupLandmarks = new QButtonGroup;
    btnGroupLandmarks->setExclusive(true);
    //button to display no landmarks
    btnLandmarksNone = new QToolButton;
    btnLandmarksNone->setText("0");
    btnLandmarksNone->setCheckable(true);
    btnLandmarksNone->setChecked(true);
    btnLandmarksNone->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarksNone);
    layLandmarkGroup->addWidget(btnLandmarksNone);
    //button to display the 13 nose landmarks
    btnLandmarks13 = new QToolButton;
    btnLandmarks13->setText("13");
    btnLandmarks13->setCheckable(true);
    btnLandmarks13->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarks13);
    layLandmarkGroup->addWidget(btnLandmarks13);
    //button to display all 72 face landmarks
    btnLandmarks72 = new QToolButton;
    btnLandmarks72->setText("72");
    btnLandmarks72->setCheckable(true);
    btnLandmarks72->setSizePolicy(sizepolOptionButtons);
    btnGroupLandmarks->addButton(btnLandmarks72);
    layLandmarkGroup->addWidget(btnLandmarks72);

    layOptions->addStretch();
}
