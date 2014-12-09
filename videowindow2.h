#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QButtonGroup>
#include <QToolButton>
#include <QIcon>
#include <QPixmap>

#include "videotools2.h"
#include "displaylabel.h"

class VideoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = 0);

    //QLabel *lblVerif;
    DisplayLabel *lblDisplay;

signals:

public slots:


private slots:
    void on_btnPlayOrPause_clicked();
    void on_btnVerify_clicked();

    void on_btnLandmarksNone_clicked();
    void on_btnLandmarks13_clicked();
    void on_btnLandmarks72_clicked();

    void on_btnVCenterLine_clicked();
    void on_btnHCenterLine_clicked();

private:
    VideoTools *video;

    QGridLayout *layVideoWindow;
    QLabel *lblDisplayStart;
    //DisplayLabel lblVerif (in public)
    bool lblVerifIsStarted;

    QWidget *optionsBar;
    //QVBoxLayout *layOptionsStart;
    //QVBoxLayout *layOptionsVerify;

    QToolButton *btnPlayOrPause;
    const QIcon iconPlay;
    const QIcon iconPause;
    QToolButton *btnVerify;

    QGroupBox *groupLandmarks;
    QToolButton *btnLandmarksNone;
    QToolButton *btnLandmarks13;
    QToolButton *btnLandmarks72;

    QGroupBox *groupSymmetry;
    QToolButton *btnHCenterLine;
    QToolButton *btnVCenterLine;

    void createVideoWindow();
};

#endif // VIDEOWINDOW_H
