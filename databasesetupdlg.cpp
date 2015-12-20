#include "databasesetupdlg.h"
#include "ui_databasesetupdlg.h"
#include <QFileDialog>
#include <QList>
#include <QString>
#include <QDebug>
#include <QTextStream>

 QString info;
 QString info2;
 QString info3;


 void DatabaseSetupDLG::setParent(DatabaseManager *p)
 {
   myParent = p;
 }

 DatabaseSetupDLG::DatabaseSetupDLG(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetupDLG)
{
    ui->setupUi(this);

}

DatabaseSetupDLG::~DatabaseSetupDLG()
{
    delete ui;
}

void DatabaseSetupDLG::on_button_info_clicked()
{
    info = QFileDialog::getExistingDirectory(this,tr("Choose Path"),"/");
    ui->lineEdit_Info->setText(info);

}

void DatabaseSetupDLG::on_button_mtp_clicked()
{
    info2 = QFileDialog::getExistingDirectory(this,tr("Choose Path"),"/");
    ui->lineEdit_mtp->setText(info2);

}

void DatabaseSetupDLG::on_button_mtb_clicked()
{
    info3 = QFileDialog::getExistingDirectory(this,tr("Choose Path"),"/");
    ui->lineEdit_mtb->setText(info3);

}

void DatabaseSetupDLG::on_pushButton_clicked()
{
    qDebug() << "Adding to file" << info << " " << info2 << " " << info3 << endl;
    QList<QString> itemsToWrite;
    itemsToWrite.append("###THIS IS AN M10 BACKUP CONFIG FILE DO NOT EDIT!!!!###\n");
    itemsToWrite.append(ui->lineEdit_Info->text()+ "\n");
    itemsToWrite.append(ui->lineEdit_mtp->text() + "\n");
    itemsToWrite.append(ui->lineEdit_mtb->text() + "\n");
    itemsToWrite.append("###END###");

    QFile fileToWrite("./m10Backup.conf");

    if(!fileToWrite.open(QIODevice::WriteOnly)){
        qDebug() << "Write Failed!" << endl;
    }

    QTextStream ts(&fileToWrite);
    for(int i=0; i<itemsToWrite.length();i++){
        ts << itemsToWrite.at(i);
    }
    fileToWrite.flush();
    fileToWrite.close();

    this->setVisible(false);
}
