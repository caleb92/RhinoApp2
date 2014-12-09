#include "mainwindow3.h"

#include <QFile>
#include <QDebug>

MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    menuIcons(48,48),
    toggleIcons(24,24),
    currentToolBarArea(Qt::LeftToolBarArea),
    currentToolButtonStyle(Qt::ToolButtonTextBesideIcon),
    menuButtonSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum ),
    toggleButtonSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ),
    stackedMainLastIndex(0)
{
    setupCentral();
    setupToolBar();

    setupPageStart();
    setupPageFiles();
    setupPageSetup();

    applyCSS();
    //this->setWindowFlags(Qt::FramelessWindowHint); //remove frame and title bar
    //this->setWindowFlags(Qt::CustomizeWindowHint); //remove title bar
    this->setWindowTitle("Nose Pro");
    this->showMaximized();

    connect(stackedMain, SIGNAL(currentChanged(int)), this, SLOT(on_stackedMain_currentChanged(int)));
}

MainWindow3::~MainWindow3() {
}

void MainWindow3::on_btnStart_clicked() {
    stackedMain->setCurrentWidget(pageStart);
    this->statusBar()->showMessage("Home Page");
}

void MainWindow3::on_btnFiles_clicked() {
    stackedMain->setCurrentWidget(pageFiles);
    this->statusBar()->showMessage("File Viewer");
}

void MainWindow3::on_btnSetup_clicked() {
    stackedMain->setCurrentWidget(pageSetup);
    this->statusBar()->showMessage("Settings");
}

void MainWindow3::on_btnVerif_clicked() {
    stackedMain->setCurrentWidget(pageVerif);
}

void MainWindow3::on_btnExit_clicked() {
    this->close();
}

void MainWindow3::on_btnCSS_clicked() {
    applyCSS();
    this->statusBar()->showMessage("Updated CSS");
}

void MainWindow3::on_btnToggleIcons_clicked() {
    Qt::ToolButtonStyle iconStyle = toolBar->toolButtonStyle();
    switch(iconStyle) {
    case Qt::ToolButtonIconOnly:
        toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnStart->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnFiles->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnSetup->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnVerif->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnExit->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btnCSS->setToolButtonStyle(Qt::ToolButtonTextOnly);
        statusBar()->showMessage("Viewing text only", 1000);
        break;
    case Qt::ToolButtonTextOnly:
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnStart->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnFiles->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnSetup->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnVerif->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnExit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnCSS->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        statusBar()->showMessage("Viewing text beside icons", 1000);
        break;
    case Qt::ToolButtonTextUnderIcon:
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnStart->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnFiles->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnSetup->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnVerif->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnExit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnCSS->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        statusBar()->showMessage("Viewing text beside icons", 1000);
        break;
    case Qt::ToolButtonTextBesideIcon:
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnStart->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnFiles->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnSetup->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnVerif->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnExit->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnCSS->setToolButtonStyle(Qt::ToolButtonIconOnly);
        statusBar()->showMessage("Viewing icons only", 1000);
        break;
    default:
        statusBar()->showMessage("No cases met!");
    }
}

void MainWindow3::on_stackedMain_currentChanged(int index)
{
    switch(stackedMainLastIndex) {
    case IndexStartPage:
        qDebug() << "Last Page: Start Page";
        break;
    case IndexFilesPage:
        qDebug() << "Last Page: Files Page";
        break;
    case IndexSetupPage:
        qDebug() << "Last Page: Setup Page";
        break;
    case IndexVerifPage:
        qDebug() << "Last Page: Verif Page";
        break;
    default:
        qDebug() << "Last Page: WTF page?";
    }

    stackedMainLastIndex = index;
}

void MainWindow3::on_btnTogglePosition_clicked() {
    Qt::ToolBarArea position = this->toolBarArea(toolBar);
    switch(position) {
    case Qt::LeftToolBarArea:
        this->addToolBar(Qt::TopToolBarArea, toolBar);
        layToolBar->setDirection(QBoxLayout::LeftToRight);
        layToggle->setDirection(QBoxLayout::TopToBottom);
        btnTogglePosistion->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.arrow.left.png"));
        btnTogglePosistion->setToolTip("Move menu to the left");
        break;
    case Qt::TopToolBarArea:
        this->addToolBar(Qt::LeftToolBarArea, toolBar);
        layToolBar->setDirection(QBoxLayout::TopToBottom);
        layToggle->setDirection(QBoxLayout::LeftToRight);
        btnTogglePosistion->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.arrow.up.png"));
        btnTogglePosistion->setToolTip("Move menu to the top");
        break;
    }
}

void MainWindow3::applyCSS() {
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

void MainWindow3::setupCentral() {
    //create a stacked widget (the main widget)
    stackedMain = new QStackedWidget(this);
    //create widgets for the pages of stackedMain
    pageStart = new QWidget;
    pageFiles = new QWidget;
    pageSetup = new QWidget;
    pageVerif = new VideoWindow;
    stackedMain->addWidget(pageStart); stackedMain->setCurrentIndex(IndexStartPage);
    stackedMain->addWidget(pageFiles); stackedMain->setCurrentIndex(IndexFilesPage);
    stackedMain->addWidget(pageSetup); stackedMain->setCurrentIndex(IndexSetupPage);
    stackedMain->addWidget(pageVerif); stackedMain->setCurrentIndex(IndexVerifPage);
    stackedMain->setCurrentWidget(pageStart); //dispaly start page on opening

    //add stackedMain central part of mainWindow
    this->setCentralWidget(stackedMain);

}

void MainWindow3::setupPageStart() {
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

void MainWindow3::setupPageFiles() {
    //populate pageFiles (an empty QWidget)
    //tabFiles = new QTabWidget(stackedMain); //main pageFile widget
    Files = new FileViewer(stackedMain);
    layFiles = new QGridLayout(pageFiles);  //layout for sizing tab widget
    layFiles->addWidget(Files);          //add tabFiles to the layout
    pageFiles->setLayout(layFiles);         //apply layout to the pageFiles Widget
}

void MainWindow3::setupPageSetup() {
    //populate pageSetup (an empty QWidget)
    laySetup = new QGridLayout(pageSetup);
    lblSetup = new QLabel(stackedMain);
    laySetup->addWidget(lblSetup);
    pageSetup->setLayout(laySetup);

    lblSetup->setText("this is lblSetup");
}

void MainWindow3::setupToolBar() {
    //create a tool bar
    toolBar = new QToolBar(this);
    toolBar->setSizePolicy(menuButtonSizePolicy);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    toolBar->setToolButtonStyle(currentToolButtonStyle);
    //create a central widget for toolBar
    toolWidget = new QWidget(toolBar);
    toolWidget->setSizePolicy(menuButtonSizePolicy);
    //create a layout to manage the position of QToolButtons
    layToolBar = new QBoxLayout(QBoxLayout::TopToBottom, toolWidget);
    //creat a button group to manage the state of QToolButtons
    btnGroupMenu = new QButtonGroup(this);
    btnGroupMenu->setExclusive(true);

    //creat QToolButtons for the menu
    //Start
    btnStart = new QToolButton;
    btnStart->setText("Nose Pro");
    btnStart->setCheckable(true);
    btnStart->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.home.png"));
    btnStart->setIconSize(menuIcons);
    btnStart->setToolButtonStyle(currentToolButtonStyle);
    btnStart->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnStart);
    btnGroupMenu->addButton(btnStart);
    //Files
    btnFiles = new QToolButton;
    btnFiles->setText("Files");
    btnFiles->setCheckable(true);
    btnFiles->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.cabinet.files.png"));
    btnFiles->setIconSize(menuIcons);
    btnFiles->setToolButtonStyle(currentToolButtonStyle);
    btnFiles->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnFiles);
    btnGroupMenu->addButton(btnFiles);
    //Setup
    btnSetup = new QToolButton;
    btnSetup->setText("Setup");
    btnSetup->setCheckable(true);
    btnSetup->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.cogs.png"));
    btnSetup->setIconSize(menuIcons);
    btnSetup->setToolButtonStyle(currentToolButtonStyle);
    btnSetup->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnSetup);
    btnGroupMenu->addButton(btnSetup);
    //Verif
    btnVerif = new QToolButton;
    btnVerif->setText("Verify");
    btnVerif->setCheckable(true);
    btnVerif->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.check.png"));
    btnVerif->setIconSize(menuIcons);
    btnVerif->setToolButtonStyle(currentToolButtonStyle);
    btnVerif->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnVerif);
    btnGroupMenu->addButton(btnVerif);
    //Exit
    btnExit = new QToolButton;
    btnExit->setText("Exit");
    btnExit->setCheckable(true);
    btnExit->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.close.png"));
    btnExit->setIconSize(menuIcons);
    btnExit->setToolButtonStyle(currentToolButtonStyle);
    btnExit->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnExit);
    btnGroupMenu->addButton(btnExit);
    //CSS
    btnCSS = new QToolButton;
    btnCSS->setText("CSS");
    btnCSS->setCheckable(true);
    btnCSS->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.beer.png"));
    btnCSS->setIconSize(menuIcons);
    btnCSS->setToolButtonStyle(currentToolButtonStyle);
    btnCSS->setSizePolicy(menuButtonSizePolicy);
    layToolBar->addWidget(btnCSS);
    btnGroupMenu->addButton(btnCSS);

    //add toggle buttons
    toggleWidget = new QWidget(toolBar);
    layToggle = new QBoxLayout(QBoxLayout::LeftToRight, toggleWidget);
    btnTogglePosistion = new QToolButton;
    btnTogglePosistion->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.arrow.up.png"));
    btnTogglePosistion->setIconSize(toggleIcons);
    btnTogglePosistion->setSizePolicy(toggleButtonSizePolicy);
    btnTogglePosistion->setToolTip("Move menu to the top");
    layToggle->addWidget(btnTogglePosistion, Qt::AlignCenter);
    btnToggleIcons = new QToolButton;
    btnToggleIcons->setIcon(QIcon("C:/QtPrograms/NasalApplication/RhinoApp2.0/RhinoApp2/icons/appbar.list.gear.png"));
    btnToggleIcons->setIconSize(toggleIcons);
    btnToggleIcons->setSizePolicy(toggleButtonSizePolicy);
    btnToggleIcons->setToolTip("Toggle the menu display style");
    layToggle->addWidget(btnToggleIcons, Qt::AlignCenter);

    QSpacerItem *spacerToolBar = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);
    layToolBar->addSpacerItem(spacerToolBar);

    //layToolBar->addStretch(1);
    layToolBar->addWidget(toggleWidget);

    //add layout to toolWidget and add toolWidget to toolBar
    toolBar->addWidget(toolWidget);
    //add the toolBar to the left side of the main window
    this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

    //connect toolBar to stackedMain
    connect(btnStart, SIGNAL(clicked()), this, SLOT(on_btnStart_clicked()));
    connect(btnFiles, SIGNAL(clicked()), this, SLOT(on_btnFiles_clicked()));
    connect(btnSetup, SIGNAL(clicked()), this, SLOT(on_btnSetup_clicked()));
    connect(btnVerif, SIGNAL(clicked()), this, SLOT(on_btnVerif_clicked()));
    connect(btnExit, SIGNAL(clicked()), this, SLOT(on_btnExit_clicked()));
    connect(btnCSS, SIGNAL(clicked()), this, SLOT(on_btnCSS_clicked()));

    connect(btnTogglePosistion, SIGNAL(clicked()), this, SLOT(on_btnTogglePosition_clicked()));
    connect(btnToggleIcons, SIGNAL(clicked()), this, SLOT(on_btnToggleIcons_clicked()));

    btnCSS->hide();
}
