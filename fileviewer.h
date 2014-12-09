#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QLabel>


class FileViewer : public QWidget
{
    Q_OBJECT
public:
    explicit FileViewer(QWidget *parent = 0);

signals:

public slots:

private slots:
     void on_grabfile_clicked();

private:
    QLineEdit *first;
    QLineEdit *last;
    QPushButton *grabfile;
    QTabWidget  *tabWidget;
    QTextBrowser *browser;
    QVBoxLayout *filelayout;
    QLabel *firstlabel;
    QLabel *lastlabel;





};

#endif // FILEVIEWER_H
