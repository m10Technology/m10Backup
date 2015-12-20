#ifndef QUAZIPUTIL_H
#define QUAZIPUTIL_H
#include <QString>
#include <QStringList>
#include <QThread>
#include <QDir>
#include <progressthread.h>
class QuazipUtil
{
public:
        void compressDir(QString ZipFile, QString Directory);

        double getFolderSize(QDir directory);

        QStringList listFiles(QString ZipFile);

        void decompressArchive(QString ZipFile, QString Directory);

        void setProgressManager(ProgressThread* p);

};

#endif // QUAZIPUTIL_H
