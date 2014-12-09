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

#include "videotools.h"
#include "displaylabel.h"

class VideoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = 0);

    //QLabel *lblVerif;
    DisplayLabel *lblVerif;

signals:

public slots:


private slots:
    void on_btnDisplayPlay_clicked();

    void on_btnLandmarksNone_clicked();
    void on_btnLandmarks13_clicked();
    void on_btnLandmarks72_clicked();

    void on_btnVCenterLine_clicked();
    void on_btnHCenterLine_clicked();

private:
    VideoTools *video;

    QGridLayout *layVerif;
    QLabel *lblVerifStart;
    //DisplayLabel lblVerif (in public)
    bool lblVerifIsStarted;


    QVBoxLayout *layOptionsVerif;
    QWidget *optionsVerif;

    QGroupBox *groupDisplay;
    QToolButton *btnDisplayPlay;
    const QIcon iconPlay;
    const QIcon iconPause;
    QToolButton *btnDisplaySize;

    QGroupBox *groupLandmarks;
    QToolButton *btnLandmarksNone;
    QToolButton *btnLandmarks13;
    QToolButton *btnLandmarks72;

    QGroupBox *groupSymmetry;
    QToolButton *btnHCenterLine;
    QToolButton *btnVCenterLine;

};

#endif // VIDEOWINDOW_H
