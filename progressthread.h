#ifndef PROGRESSTHREAD_H
#define PROGRESSTHREAD_H
#include <progressthread.h>
#include <QThread>
#include <mainwindow.h>
#include <QFile>
class ProgressThread : public QThread
{
        Q_OBJECT


public:
    MainWindow* myParent;
    void setDone();
    void setFinalFile(QString file);
    void setEstSize(double size);
    void printSomething();
    int getPercent();
    void setPercent();
    void setParent(MainWindow* parent);
    double checkCurrentSize(QString file);
    int running = 1;
private:
    void run();

signals:
    void valueChanged(int percent);

};

#endif // PROGRESSTHREAD_H
