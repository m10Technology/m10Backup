#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <QtSql/QSql>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon i("/Volumes/Dev/Projects/C++/m10Backup/icon.png");
    a.setWindowIcon(i);
    MainWindow w;
    w.setWindowIcon(i);
    w.show();


    return a.exec();
}
