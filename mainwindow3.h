#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolButton>
#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QDockWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "videotools.h"
#include "videowindow2.h"
#include "fileviewer.h"

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = 0);
    ~MainWindow3();

    enum stackedMainTabIndex {
        IndexStartPage, //0
        IndexFilesPage, //1
        IndexSetupPage, //2
        IndexVerifPage, //3
    };

private:
    int stackedMainLastIndex;
    VideoTools *video;

    void setupToolBar();
    void setupCentral();
    void setupPageStart();
    void setupPageFiles();
    void setupPageSetup();
    void applyCSS();

    QSize menuIcons;
    QSize toggleIcons;
    Qt::ToolBarArea currentToolBarArea;
    Qt::ToolButtonStyle currentToolButtonStyle;
    const QSizePolicy menuButtonSizePolicy;
    const QSizePolicy toggleButtonSizePolicy;

    QToolBar *toolBar;
    QWidget *toolWidget;
    QBoxLayout *layToolBar;
    QButtonGroup *btnGroupMenu;
    QToolButton *btnStart;
    QToolButton *btnFiles;
    QToolButton *btnSetup;
    QToolButton *btnVerif;
    QToolButton *btnExit;
    QToolButton *btnCSS;

    QWidget *toggleWidget;
    QToolButton *btnTogglePosistion;
    QBoxLayout *layToggle;
    QToolButton *btnToggleIcons;

    QStackedWidget *stackedMain;

    QWidget *pageStart;
    QGridLayout *layStart;
    QLabel *lblStart;

    QWidget *pageFiles;
    QGridLayout *layFiles;
    FileViewer *Files;
    //QTabWidget *tabFiles;
    //QTextEdit *txtDefaultTab;

    QWidget *pageSetup;
    QGridLayout *laySetup;
    QLabel *lblSetup;

    VideoWindow *pageVerif;
    QGridLayout *layVerif;

    QVBoxLayout *layOptionsVerif;
    QWidget *optionsVerif;
    QGroupBox *groupDisplay;
    QToolButton *btnDisplayPause;
    QToolButton *btnDisplaySize;
    QGroupBox *groupLandmarks;
    QToolButton *btnLandmarksNone;
    QToolButton *btnLandmarks72;
    QToolButton *btnLandmarks13;

private slots:
    void on_btnStart_clicked();
    void on_btnFiles_clicked();
    void on_btnSetup_clicked();
    void on_btnVerif_clicked();
    void on_btnExit_clicked();
    void on_btnCSS_clicked();
    void on_btnTogglePosition_clicked();
    void on_btnToggleIcons_clicked();

    void on_stackedMain_currentChanged(int index);
};

#endif // MAINWINDOW3_H
