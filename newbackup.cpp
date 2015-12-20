#include "newbackup.h"
#include "ui_newbackup.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDir>
#include <QSysInfo>
#include <QtCore>
#include <QMap>
#include <QDataStream>
#include <QFileDialog>

NewBackup::NewBackup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBackup)
{
    ui->setupUi(this);
}

NewBackup::~NewBackup()
{
    delete ui;
}

bool NewBackup::on_pushButton_clicked()
{
    //Create List Object to store all
    QList<QString> myPrefs;
    myPrefs.append("*** THIS IS AN M10 BACKUP PREFERENCES FILE ***");
    myPrefs.append(ui->lineEdit_bName->text());
    myPrefs.append(ui->lineEdit_backupFrom->text());
    myPrefs.append(ui->lineEdit_outputFolder->text());
    if(ui->backupOnce->isChecked()){
        myPrefs.append("0");
    }
    else if(ui->scheduleBackup->isChecked()){
        if(ui->checkBox->isChecked()){
            myPrefs.append("d");
        }
        else if(ui->checkBox_2->isChecked())
        {
            myPrefs.append("w");
        }
        else if(ui->checkBox_3->isChecked())
            myPrefs.append("m");
    }

    //Print out list for verification...
    qDebug() << "The Information to be Saved to file is: " << endl;
                for(int i = 0; i< myPrefs.length(); i++){
                        qDebug() << myPrefs.at(i);
                }


    //Write to file
                QFile fileToWrite("./"+ui->lineEdit_bName->text()+".mtp");

                if(!fileToWrite.open(QIODevice::WriteOnly)){
                    qDebug() << "Write Failed!" << endl;
                }

                QDataStream out(&fileToWrite);
                out.setVersion(QDataStream::Qt_5_3);
                out << myPrefs;
                fileToWrite.flush();
                fileToWrite.close();


    //Add to Database

    this->close();
}

void NewBackup::on_backupOnce_clicked()
{
    if(ui->backupOnce->isChecked()){
        ui->label->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
    }
}

void NewBackup::on_scheduleBackup_clicked()
{
    if(ui->scheduleBackup->isChecked()){
        ui->label->setEnabled(true);
        ui->checkBox->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
    }
}

void NewBackup::on_pushButton_2_clicked()
{
    this->close();
}

void NewBackup::on_button1_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
            "/",
            QFileDialog::ShowDirsOnly
            |QFileDialog::DontResolveSymlinks);
     ui->lineEdit_backupFrom->setText(fileName);
}

void NewBackup::on_button2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save m10 Backup file"), "",
        tr("m10 Backup File (*.mtb);;All Files (*)"));
    ui->lineEdit_outputFolder->setText(fileName);
}
