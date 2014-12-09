#include "draw.h"

#include <QDebug>

Draw::Draw(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Draw constructor!";
    test();
}

void Draw::test()
{
    qDebug() << m_cameraIndex;
}
