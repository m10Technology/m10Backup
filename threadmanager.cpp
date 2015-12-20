#include <threadmanager.h>
#include <QDebug>
#include <QString>
#include <quaziputil.h>
#include <stdlib.h>
#include <progressthread.h>


ProgressThread* instanceP;
QString backupFrom;
QString backupTo;
void ThreadManager::run(){
    qDebug() << "Running!" <<endl;
    QuazipUtil q;
    q.setProgressManager(instanceP);
    q.compressDir(backupTo,backupFrom);
    qDebug() << "Done" << endl;
    instanceP->myParent->toggleIsBackingUp();
    instanceP->setDone();
}

void ThreadManager::endPrematurely()
{
   //Code to Kill The Current Backup
}

void ThreadManager::setBackupFrom(QString input){
    backupFrom = input;
}
void ThreadManager::setBackupTo(QString input2){
    backupTo = input2;
}

void ThreadManager::setProgressManagerToPass(ProgressThread *p)
{
    instanceP = p;
}

