#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

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
