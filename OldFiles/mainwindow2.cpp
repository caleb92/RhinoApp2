#include "mainwindow2.h"

#include <QFile>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent)
{
    setupToolBar();
    setupCentral();

    setupPageStart();
    setupPageFiles();
    setupPageSetup();
    setupPageVerif();

    applyCSS();
    this->setWindowTitle("Nose Rhino");
    this->showMaximized();
}

MainWindow2::~MainWindow2()
{
}

void MainWindow2::on_actStart_triggered()
{
    stackedMain->setCurrentWidget(pageStart);
    actFiles->setChecked(false);
    actSetup->setChecked(false);
    actVerif->setChecked(false);
    this->statusBar()->showMessage("Home Page");
}

void MainWindow2::on_actFiles_triggered()
{
    stackedMain->setCurrentWidget(pageFiles);
    this->statusBar()->showMessage("File Viewer");
}

void MainWindow2::on_actSetup_triggered()
{
    stackedMain->setCurrentWidget(pageSetup);
    this->statusBar()->showMessage("Settings");
}

void MainWindow2::on_actVerif_triggered()
{
    stackedMain->setCurrentWidget(pageVerif);
    this->statusBar()->showMessage("Verification Tools");
}

void MainWindow2::on_actExit_triggered()
{
    this->close();
}

void MainWindow2::on_actCSS_triggered()
{
    applyCSS();
    this->statusBar()->showMessage("Updated CSS");
}

void MainWindow2::applyCSS()
{
    QFile styleFile("../RhinoApp2/styles/style1.css");
    if(styleFile.exists()) {
        styleFile.open(QIODevice::ReadOnly);
        if(styleFile.isOpen()) {
            QString currentStyle(styleFile.readAll());
            this->setStyleSheet(currentStyle);
            styleFile.close();
            this->statusBar()->showMessage("Style Applied",1000);
        } else
            this->statusBar()->showMessage("Could not open status file!",2000);
    } else
        this->statusBar()->showMessage("Style file does not exist!",2000);
}

void MainWindow2::setupToolBar()
{
    //create a tool bar
    toolBar = new QToolBar(this);
    toolBar->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    toolBar->setIconSize(QSize(10,10));
    //create a central widget for toolBar
    toolWidget = new QWidget;
    //create a layout to manage the QToolButtons
    layToolBar = new QVBoxLayout;
    //create an action group to manage the actions
    actGroupToolBar = new QActionGroup(this);
    actGroupToolBar->setExclusive(true);
    //creat QToolButtons for the menu and assign them a QAction
    //Start
    actStart = actGroupToolBar->addAction("Nose Rhino");
    btnStart = new QToolButton(this);
    btnStart->addAction(actStart);
    layToolBar->addWidget(btnStart);
    //Files
    actFiles = new QAction("Files", this);
    actGroupToolBar->addAction(actFiles);
    btnFiles = new QToolButton(this);
    btnFiles->addAction(actFiles);
    actFiles->setCheckable(true);
    layToolBar->addWidget(btnFiles);
    //Setup
    actSetup = actGroupToolBar->addAction("Setup Camera");
    btnSetup = new QToolButton(this);
    btnSetup->addAction(actSetup);
    actSetup->setCheckable(true);
    layToolBar->addWidget(btnSetup);
    //Verif
    actVerif = actGroupToolBar->addAction("Verification");
    btnVerif = new QToolButton(this);
    btnVerif->addAction(actVerif);
    actVerif->setCheckable(true);
    layToolBar->addWidget(btnVerif);
    //Exit
    actExit = actGroupToolBar->addAction("Exit");
    btnExit = new QToolButton(this);
    btnExit->addAction(actExit);
    layToolBar->addWidget(btnExit);
    //CSS
    actCSS = actGroupToolBar->addAction("CSS");
    btnCSS = new QToolButton(this);
    btnCSS->addAction(actCSS);
    layToolBar->addWidget(btnCSS);

    //btnFiles->setText("Files");
    //actFiles->setText("Filez");


    //add layout to toolWidget and add toolWidget to toolBar
    toolWidget->setLayout(layToolBar);
    toolWidget->setAutoFillBackground(true);
    toolBar->addWidget(toolWidget);
    //add the toolBar to the left side of the main window
    this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

}

void MainWindow2::setupCentral()
{
    //create a stacked widget (the main widget)
    stackedMain = new QStackedWidget(this);
    //create widgets for the pages of stackedMain
    pageStart = new QWidget;
    pageFiles = new QWidget;
    pageSetup = new QWidget;
    pageVerif = new QWidget;
    stackedMain->addWidget(pageStart);
    stackedMain->addWidget(pageFiles);
    stackedMain->addWidget(pageSetup);
    stackedMain->addWidget(pageVerif);

    //add stackedMain central part of mainWindow
    this->setCentralWidget(stackedMain);

    //connect toolBar to stackedMain
    connect(actStart, SIGNAL(triggered()), this, SLOT(on_actStart_triggered()));
    connect(actFiles, SIGNAL(triggered()), this, SLOT(on_actFiles_triggered()));
    connect(actSetup, SIGNAL(triggered()), this, SLOT(on_actSetup_triggered()));
    connect(actVerif, SIGNAL(triggered()), this, SLOT(on_actVerif_triggered()));
    connect(actExit, SIGNAL(triggered()), this, SLOT(on_actExit_triggered()));
    connect(actCSS, SIGNAL(triggered()), this, SLOT(on_actCSS_triggered()));

}

void MainWindow2::setupPageStart()
{
    //populate pageSetup (an empty QWidget)
    layStart = new QGridLayout(pageSetup);
    lblStart = new QLabel(stackedMain);
    layStart->addWidget(lblStart);
    pageStart->setLayout(layStart);

    //layStart->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    lblStart->setAutoFillBackground(true);
    lblStart->setAlignment(Qt::AlignTop);
    lblStart->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QPixmap pixmapHome;
    if(!pixmapHome.load(":/images/images/logo.png")) {
        qWarning("failed to load :/images/images/logo.png");
    }
    //lblStart->setPixmap(pixmapHome.scaled(lblStart->size(),Qt::KeepAspectRatio));
    lblStart->setPixmap(pixmapHome);
}

void MainWindow2::setupPageFiles()
{
    //populate pageFiles (an empty QWidget)
    tabFiles = new QTabWidget(stackedMain); //main pageFile widget
    layFiles = new QGridLayout(pageFiles);  //layout for sizing tab widget
    layFiles->addWidget(tabFiles);          //add tabFiles to the layout
    pageFiles->setLayout(layFiles);         //apply layout to the pageFiles Widget

    txtDefaultTab = new QTextEdit;
    txtDefaultTab->setText("Welcome!");
    tabFiles->addTab(txtDefaultTab,"Tab 1");
}

void MainWindow2::setupPageSetup()
{
    //populate pageSetup (an empty QWidget)
    laySetup = new QGridLayout(pageSetup);
    lblSetup = new QLabel(stackedMain);
    laySetup->addWidget(lblSetup);
    pageSetup->setLayout(laySetup);

    lblSetup->setText("this is lblSetup");
}

void MainWindow2::setupPageVerif()
{
    //populate pageVerif (an empty QWidget)
    layVerif = new QGridLayout(pageVerif);
    lblVerif = new QLabel(stackedMain);
    layVerif->addWidget(lblVerif);
    pageVerif->setLayout(layVerif);

    lblVerif->setText("this is lblVerif");
}
