#include "mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent)
{
    setupGUI();
}

MainWindow2::~MainWindow2()
{
}

void MainWindow2::setupGUI()
{
    //create a tool bar
    toolBar = new QToolBar(this);
    //add actions with their buttons to the tool bar
    actFiles = toolBar->addAction("File Viewer");
    actSetup = toolBar->addAction("Setup Camera");
    actVerif = toolBar->addAction("Verification");
    actExit = toolBar->addAction("Exit");
    actCSS = toolBar->addAction("CSS");
    //add the toolBar to the left side of the main window
    this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

    //create a stacked widget (the main widget)
    stackedMain = new QStackedWidget(this);
    //create widgets for the pages of stackedMain
    pageFiles = new QWidget;
    pageSetup = new QWidget;
    pageVerif = new QWidget;
    stackedMain->addWidget(pageFiles);
    stackedMain->addWidget(pageSetup);
    stackedMain->addWidget(pageVerif);

    //populate pageFiles (an empty QWidget)
    layFiles = new QGridLayout(pageFiles);
    tabFiles = new QTabWidget(stackedMain);
    layFiles->addWidget(tabFiles);
    pageFiles->setLayout(layFiles);
    //populate pageSetup (an empty QWidget)
    laySetup = new QGridLayout(pageSetup);
    lblSetup = new QLabel(stackedMain);
    laySetup->addWidget(lblSetup);
    pageSetup->setLayout(laySetup);
    //populate pageVerif (an empty QWidget)
    layVerif = new QGridLayout(pageVerif);
    lblVerif = new QLabel(stackedMain);
    layVerif->addWidget(lblVerif);
    pageVerif->setLayout(layVerif);

    //add stackedMain central part of mainWindow
    this->setCentralWidget(stackedMain);

    //connect toolBar to stackedMain
    connect(actFiles, SIGNAL(triggered()), this, SLOT(on_actFiles_triggered()));
    connect(actSetup, SIGNAL(triggered()), this, SLOT(on_actSetup_triggered()));
    connect(actVerif, SIGNAL(triggered()), this, SLOT(on_actVerif_triggered()));
    connect(actExit, SIGNAL(triggered()), this, SLOT(on_actExit_triggered()));
    connect(actCSS, SIGNAL(triggered()), this, SLOT(on_actCSS_triggered()));

    //detail stackedMain
    tabFiles->setTabText(1,"Tab 1");
    lblSetup->setText("this is lblSetup");
    lblVerif->setText("this is lblVerif");

}

void MainWindow2::on_actFiles_triggered()
{
    stackedMain->setCurrentWidget(pageFiles);
}

void MainWindow2::on_actSetup_triggered()
{
    stackedMain->setCurrentWidget(pageSetup);
}

void MainWindow2::on_actVerif_triggered()
{
    stackedMain->setCurrentWidget(pageVerif);
}

void MainWindow2::on_actExit_triggered()
{
    this->close();
}

void MainWindow2::on_actCSS_triggered()
{

}
