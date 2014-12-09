#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolButton>
#include <QWidget>

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

private:
    void setupToolBar();
    void setupCentral();
    void setupPageStart();
    void setupPageFiles();
    void setupPageSetup();
    void setupPageVerif();
    void applyCSS();

    QToolBar *toolBar;
    QWidget *toolWidget;
    QVBoxLayout *layToolBar;
    QActionGroup *actGroupToolBar;
    QAction *actStart; QToolButton *btnStart;
    QAction *actFiles; QToolButton *btnFiles;
    QAction *actSetup; QToolButton *btnSetup;
    QAction *actVerif; QToolButton *btnVerif;
    QAction *actExit; QToolButton *btnExit;
    QAction *actCSS; QToolButton *btnCSS;

    QStackedWidget *stackedMain;

    QWidget *pageStart;
    QGridLayout *layStart;
    QLabel *lblStart;

    QWidget *pageFiles;
    QGridLayout *layFiles;
    QTabWidget *tabFiles;
    QTextEdit *txtDefaultTab;

    QWidget *pageSetup;
    QGridLayout *laySetup;
    QLabel *lblSetup;

    QWidget *pageVerif;
    QGridLayout *layVerif;
    QLabel *lblVerif;

private slots:
    void on_actStart_triggered();
    void on_actFiles_triggered();
    void on_actSetup_triggered();
    void on_actVerif_triggered();
    void on_actExit_triggered();
    void on_actCSS_triggered();

};

#endif // MAINWINDOW2_H
