#include "MainWindow3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow3 mainWindow;
    mainWindow.show();

    return a.exec();
}
