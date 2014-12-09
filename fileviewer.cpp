#include "fileviewer.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QString>



FileViewer::FileViewer(QWidget *parent) :
    QWidget(parent)
{
 filelayout = new QVBoxLayout(this);
 firstlabel = new QLabel("First name");
 lastlabel = new QLabel("Last name");
 first = new QLineEdit(this);
 last = new QLineEdit(this);
 grabfile = new QPushButton("Get Files");
 tabWidget = new QTabWidget(this);

 filelayout->addWidget(firstlabel);
 filelayout->addWidget(first);
 filelayout->addWidget(lastlabel);
 filelayout->addWidget(last);
 filelayout->addWidget(grabfile);
 filelayout->addWidget(tabWidget);

 first->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
 first->setMinimumWidth(100);


 connect(grabfile, SIGNAL(clicked()), this, SLOT(on_grabfile_clicked()));
}

void FileViewer::on_grabfile_clicked()
{

     //uses name input as arguments for path
    QString location = QString("C:/Users/Mike/Documents/Patients/%1_%2")
                   .arg(first->text())
                   .arg(last->text());

    //FILES//

    //filtering for txt files//
    QStringList textFilter;
    textFilter << "*.txt";

    //opens directory at location, with filter//
    QDir dir(location);

    QFileInfoList textlist = dir.entryInfoList(textFilter, QDir::Files);

    //--actions for each txt file--//
    foreach(QFileInfo f, textlist){

        QString g = f.filePath();    //gets filename
        QFile thisfile(g);           //sets file for filename
        if(!thisfile.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",thisfile.errorString()); //creates error message if can't open file
        QTextStream in(&thisfile);                                     //grabs text from file

        QTextBrowser *browser = new QTextBrowser;  //creates textbrowser for file text to display
        browser->setText(in.readAll());            //sets text of textbrowser to file text

        tabWidget->addTab(browser,tr("Doc"));      //adds tab with browser inside, displaying text
    }

    //PICTURES///

    //--filter out picture files--//

    QStringList picFilter;
    picFilter <<"*.png" << "*.jpg" <<"*.gif" <<"*.jpeg"; //lists file types to filter

    QFileInfoList piclist = dir.entryInfoList(picFilter, QDir::Files);


    //--actions for each picture file--//
    foreach(QFileInfo p, piclist){

        QString k = p.filePath(); //gets filename of image
        QImage newpic(k);  //gets image from filename
        QLabel *imagelabel = new QLabel(this); //creates label for image
        QImage newpic2 = newpic.scaled(tabWidget->width(), tabWidget->height(),Qt::KeepAspectRatio); //scales image to size of tabs
        imagelabel->setPixmap(QPixmap::fromImage(newpic2)); //sets label to image

        tabWidget->addTab(imagelabel,tr("Picture")); //creates tab with scaled image inside
}
}


