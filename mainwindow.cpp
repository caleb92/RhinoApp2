#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

#include "videotools.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->addToolBar(Qt::LeftToolBarArea,ui->mainToolBar); //move tool bar from defult top area to left area



}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionUpdate_CSS_triggered()
{
    QFile styleFile("../RhinoApp2/styles/style1.css");
    if(styleFile.exists()) {
        styleFile.open(QIODevice::ReadOnly);
        if(styleFile.isOpen()) {
            QString currentStyle(styleFile.readAll());
            this->setStyleSheet(currentStyle);
            styleFile.close();
        } else
            printf("Could not open Style File!\n");
    } else
        printf("Style File does not exist!\n");
}

void MainWindow::on_actionFile_Viewer_triggered()
{
    ui->stackedCentral->setCurrentWidget(ui->pageFileViewer);
}

void MainWindow::on_actionSetup_Camera_triggered()
{
    ui->stackedCentral->setCurrentWidget(ui->pageSetupCamera);

    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrame()));
    tmrTimer->start(20);
}



void MainWindow::on_actionVerification_triggered()
{
    ui->stackedCentral->setCurrentWidget(ui->pageVerification);
}

void MainWindow::on_actionSettings_triggered()
{
    ui->stackedCentral->setCurrentWidget(ui->pageSettings);
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::processFrame()
{
    oVideoTools.getFrame(matProcessed);
    oVideoTools.landmarkAll(matProcessed);

    QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);
    ui->lblSetupCamera->setPixmap(QPixmap::fromImage(qimgProcessed));
}
