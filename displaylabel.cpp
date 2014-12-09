#include "displaylabel.h"

#include <QDebug>
#include <QPainter>

DisplayLabel::DisplayLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setMinimumSize(128,128);
    //this->setScaledContents(true);
}

/*
void DisplayLabel::resizeEvent(QResizeEvent *)
{
    //something here to resieze the label when the window is resized
    //QLabel::setPixmap(this->pixmap()->scaled(this->size(),
    //                                       Qt::KeepAspectRatio,
    //                                       Qt::SmoothTransformation));
    //qDebug() << "DisplayLabel resizeEvent end";
}*/

/*
void DisplayLabel::paintEvent(QPaintEvent *)
{

    QPainter painter;
    painter.begin(this);
    painter.drawRect(5,5,100,100);
    painter.drawImage();

}*/
