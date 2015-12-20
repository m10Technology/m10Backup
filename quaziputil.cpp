#include "quaziputil.h"
#include <JlCompress.h>
#include <qdebug.h>
#include <iostream>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QDirIterator>
#include <QFileInfoList>
#include <QFileInfo>
#include <progressthread.h>
using namespace std;

double sum;
static ProgressThread* instanceP;

void QuazipUtil::compressDir(QString ZipFile, QString Directory){
    QDir dir(Directory);
    QFile zipFile(ZipFile);

    //This Following Code may have some use one day...
    getFolderSize(dir);
    double dirSize = sum;
    double estSize = dirSize/1.3;
    qDebug() << "Original folder size is " << dirSize << endl << "Estimated output size is" << estSize;
    instanceP->setEstSize(estSize);
    instanceP->start();
   if(JlCompress::compressDir(ZipFile,Directory)){
        qDebug() << "Successfully created " << ZipFile << endl;
    }
    else{
      //  qDebug() << "Failed to create " << ZipFile << endl;
    }


}

QStringList QuazipUtil::listFiles(QString ZipFile){
    QFile file(ZipFile);
    if(!file.exists()){
        qDebug() << "Couldn't find " << ZipFile << endl;

    }
    else{
        QStringList files = JlCompress::getFileList(ZipFile);
        return files;
    }
}

void QuazipUtil::decompressArchive(QString ZipFile, QString Directory){
    QFile file(ZipFile);
    if(!file.exists()){
        qDebug() << "Error: File does not exist!" << endl;
    }
    else{
        JlCompress::extractDir(ZipFile,Directory);
        qDebug() << "Successfully extracted to " << Directory;
    }
}

void QuazipUtil::setProgressManager(ProgressThread *p)
{
    instanceP = p;
}


double QuazipUtil::getFolderSize(QDir directory){
    QFileInfoList myList = directory.entryInfoList();
    for(int i =0; i<myList.count();i++){
        QFileInfo info = myList[i];
        QString filePath = info.filePath();
        if(info.isDir()){
            if(info.fileName()!=".." && info.fileName()!="."){
                getFolderSize(filePath);
            }
        }
        else{
            sum += info.size();
        }
    }
}
