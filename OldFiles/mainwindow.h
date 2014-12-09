#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "qmyvideotools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionUpdate_CSS_triggered();
    void on_actionSetup_Camera_triggered();
    void on_actionFile_Viewer_triggered();
    void on_actionVerification_triggered();
    void on_actionSettings_triggered();
    void on_actionExit_triggered();

    void processFrame();

private:
    Ui::MainWindow *ui;

    int nCurrentVideoOption;
    enum VideoOptions
    {
        RAW_GRAY,
        LANDMARK_ALL,
        LANDMARK_NOSE
    };

    QmyVideoTools videoTools;

    QTimer *tmrTimer;
    cv::Mat_<unsigned char> matProcessed;
    QImage qimgProcessed;

};

#endif // MAINWINDOW_H
