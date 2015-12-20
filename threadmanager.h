
#ifndef THREADMANAGER_H
#define THREADMANAGER_H
#include <threadmanager.h>
#include <QThread>
#include <QObject>
#include <QString>
#include <progressthread.h>

class ThreadManager :  public QThread
{
 public:
      void endPrematurely();
      void setBackupFrom(QString);
      void setBackupTo(QString);
      void setProgressManagerToPass(ProgressThread *p);
      //QString backupFrom;
      //QString backupTo;
 private:
        void run();

};

#endif // THREAD_H

