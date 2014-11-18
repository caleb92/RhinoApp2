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

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

private:
    void setupGUI();

    QToolBar *toolBar;
    QAction *actFiles;
    QAction *actSetup;
    QAction *actVerif;
    QAction *actExit;
    QAction *actCSS;

    QStackedWidget *stackedMain;

    QWidget *pageFiles;
    QGridLayout *layFiles;
    QTabWidget *tabFiles;

    QWidget *pageSetup;
    QGridLayout *laySetup;
    QLabel *lblSetup;

    QWidget *pageVerif;
    QGridLayout *layVerif;
    QLabel *lblVerif;

private slots:
    void on_actFiles_triggered();
    void on_actSetup_triggered();
    void on_actVerif_triggered();
    void on_actExit_triggered();
    void on_actCSS_triggered();

};

#endif // MAINWINDOW2_H
