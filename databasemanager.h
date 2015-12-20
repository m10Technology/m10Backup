#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QString>

class DatabaseManager
{
public:
    void disconnect();
    QList<QList<QString> > updateAgain();
    QList<QList<QString> > update();
    void connect();
    void addNewBackup(int id, QString backupName, QString backupFrom, QString backupTo, QString Schedule);
    DatabaseManager();
    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
