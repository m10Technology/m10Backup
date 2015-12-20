#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <quaziputil.h>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "threadmanager.h"
#include <progressthread.h>
#include <newbackup.h>
#include <QDataStream>
#include <QList>
#include <QDir>
#include <databasemanager.h>
#include <databasesetupdlg.h>

/*
 * Startup Global Variables
 */
 QFile* configFile;
DatabaseManager d;
ThreadManager *t;
ThreadManager mThread;
ProgressThread* p;
QString mtpDefault;
QList<QList<QString> > databaseItems;
QList<QString> IDs;
QList<QString> BackupNames;
QList<QString> BackupFrom;
QList<QString> BackupTo;
bool isBackingUp = false;



/*
* Backup List and Database Functions
*/
int MainWindow::getCurrentID()
{
    int myCount = ui->listWidget_2->count();
}

void MainWindow::refresh()
{
    qDebug() << "Refreshing..." << endl;
    ui->listWidget_2->clear();
    databaseItems = d.update();
    IDs = databaseItems.at(0);
    BackupNames = databaseItems.at(1);
    BackupFrom = databaseItems.at(2);
    BackupTo = databaseItems.at(3);
    for(int i=0;i<IDs.length();i++){
        ui->listWidget_2->addItem(BackupNames.at(i));
        qDebug() << "IDS: " << IDs.at(i);
    }
}

void MainWindow::changeUI(int conformID)
{
    ui->lineEdit_backupFrom->setText(BackupFrom.at(conformID));
    ui->lineEdit_outputFolder->setText(BackupTo.at(conformID));
}



/*
* Primary Backup & Progress Functions
*/
bool MainWindow::performBackup(QString from, QString to)
{
    p = new ProgressThread;
    p->setParent(this);
    isBackingUp = true;
    mThread.setBackupFrom(from);
    mThread.setBackupTo(to);
    p->setFinalFile(to);
    t = new ThreadManager;
    t->setProgressManagerToPass(p);
    t->start();
}

void MainWindow::setMyPercent(int percent)
{
  ui->progressBar->setValue(percent);
}

void MainWindow::toggleIsBackingUp()
{
    if(isBackingUp = true){
        isBackingUp = false;
    }
    else if(isBackingUp = false){
        isBackingUp = true;
    }
    else{
        return;
    }
}



/*
*File Checking Functions
*/

//Checks if m10Backup.conf file Exists
bool MainWindow::isFirstRun(){
    configFile = new QFile("./m10Backup.conf");
    if(!configFile->exists()){
        qDebug() << "Is First Run!" << endl;
        return true;
    }
    else{
        mtpDefault = getDefaultMtp();
        qDebug() << "Default Path for mtp has been set to" << mtpDefault;
        return false;
    }

}

QString MainWindow::getDefaultMtp(){
    configFile->open(QIODevice::ReadOnly);
    QString myPath = configFile->readLine(2);
    return myPath;
}

//Checks for Existing Backup File
bool MainWindow::checkForFileExists(QString fileLocation)
{
    //If I return False I do not exist
    //If I return True I do exist

    QFile testFile(fileLocation);
    if(testFile.exists()){
        return true;
    }
    else if(!testFile.exists()){
        return false;
    }
}




/*
 * Contructor and Destructor
 */

//Contructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    if(isFirstRun()){
        DatabaseSetupDLG *setupWizard = new DatabaseSetupDLG(this);
        setupWizard->exec();
        setupWizard->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    //this->setWindowFlags(Qt::);
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    d.connect();
    refresh();
    QDir myroot(".");
    qDebug() << "Starting in: " << myroot.absolutePath();
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
    d.disconnect();

}



/*
 * UI Members
 */

//Button for backup input selection
void MainWindow::on_button1_released()
{
      QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
              "/",
              QFileDialog::ShowDirsOnly
              |QFileDialog::DontResolveSymlinks);
       ui->lineEdit_backupFrom->setText(fileName);
}

//Button for mtb output location
void MainWindow::on_button2_released()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save m10 Backup file"), "",
        tr("m10 Backup File (*.mtb);;All Files (*)"));
    ui->lineEdit_outputFolder->setText(fileName);
}

//Backup Button
void MainWindow::on_button3_released()
{
    if(ui->lineEdit_backupFrom->text()==""&&ui->lineEdit_outputFolder->text()==""){
        return;
    }
    if(isBackingUp){
        QMessageBox::warning(this,"WARNING!","There is already a backup being run! Please wait till it finishes before starting a new one.");
        return;
    }
    //Perform Backup
    ui->progressBar->setVisible(true);
    QString backupFrom = ui->lineEdit_backupFrom->text();
    QString backupTo = ui->lineEdit_outputFolder->text();
    int length = backupTo.length()-1;
    QString subString = backupTo.right(3);
    qDebug() << subString;
    if(subString!="mtb"){
        backupTo.replace(backupTo.length()-4,".mtb");

        ui->lineEdit_outputFolder->setText(backupTo);
    }
    if(!checkForFileExists(backupTo)){
        performBackup(backupFrom,backupTo);
    }
    else{
        QMessageBox msgBox;
        msgBox.warning(this,"File Overwrite","Warning, you are about to overwrite a file! Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setStandardButtons(QMessageBox::No);
        int reg = msgBox.exec();

        switch (reg){

        case QMessageBox::Yes :
            qDebug() << "You Pressed Yes!" << endl;
            performBackup(backupFrom,backupTo);
            break;
        case QMessageBox::No :
            qDebug() << " You Pressed No" << endl;
            break;

        }
    }

}

//Called when selection in backups list is changed
void MainWindow::on_listWidget_2_itemSelectionChanged()
{
    QList<QListWidgetItem *> itemsSelected = ui->listWidget_2->selectedItems();
    if(itemsSelected.length()==1){
         QString itemSelected = itemsSelected.at(0)->text();
         qDebug() << "You have selected" << itemSelected;
         int id=0;
         for(int i=0;i<ui->listWidget_2->count();i++){
             if(ui->listWidget_2->item(i)->text()==itemSelected){
                 qDebug("Match!");
                 qDebug() << "ID is" << id;
                 break;
             }
             else{
                 id++;
             }
         }
        changeUI(id);
    }
    else
    {
        qDebug() << "Too many things selected!" << endl;
    }
}

//Menu Item "Load Previous Backup"
void MainWindow::on_actionLoad_Previous_Backup_triggered()
{

    QList<QString> myPrefs;
    QString mtpFileName = QFileDialog::getOpenFileName(this,
    tr("Open File"),mtpDefault,
    tr("m10 Backup File (*.mtp);;All Files (*)"));

    QFile fileToRead(mtpFileName);

    if(!fileToRead.open(QIODevice::ReadOnly)){
        qDebug() << "Read Failed!" << endl;
    }

    QDataStream in(&fileToRead);
    in.setVersion(QDataStream::Qt_5_3);
    in >> myPrefs;
    fileToRead.flush();
    fileToRead.close();

    for(int i =0; i<myPrefs.length();i++){
        qDebug() <<myPrefs.at(i) << endl;
    }

    d.addNewBackup(getCurrentID(),myPrefs.at(1),myPrefs.at(2),myPrefs.at(3),myPrefs.at(4));
    refresh();
}

//Menu Item "New Backup"
void MainWindow::on_actionNew_Backup_triggered()
{
    NewBackup* n = new NewBackup();
    n->show();
}

//Menu Item "Open MTB"
void MainWindow::on_actionLoad_mtb_Backup_File_triggered()
{
   ui->listWidget->clear();
   QString fileName = QFileDialog::getOpenFileName(this,
   tr("Open File"),"",
   tr("m10 Backup File (*.mtb);;All Files (*)"));
   QFile file(fileName);
   if(!file.exists()){
       return;
   }
   QuazipUtil q;
   QStringList files = q.listFiles(fileName);
   for(int i =0; i<files.length();i++){
          ui->listWidget->addItem("/"+files.at(i));
   }


}

//Menu Item "Quit"
void MainWindow::on_actionQuit_triggered()
{
    qDebug() << "Killing" << endl;
    MainWindow::~MainWindow();
}

//Button for Canceling Backup
void MainWindow::on_pushButton_2_clicked()
{
    mThread.endPrematurely();
    t->endPrematurely();
}
