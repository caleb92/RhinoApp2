#ifndef DRAW_H
#define DRAW_H

#include <QObject>

class Draw : public QObject
{
    Q_OBJECT
public:
    explicit Draw(QObject *parent = 0);

    void test();

signals:

public slots:

private:


};

#endif // DRAW_H
