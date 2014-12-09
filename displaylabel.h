#ifndef DISPLAYLABEL_H
#define DISPLAYLABEL_H

#include <QLabel>

class DisplayLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DisplayLabel(QWidget *parent = 0);

signals:

public slots:
    //void resizeEvent(QResizeEvent *);

protected:
    //void paintEvent(QPaintEvent *);

};

#endif // DISPLAYLABEL_H
