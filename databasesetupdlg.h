#ifndef DATABASESETUPDLG_H
#define DATABASESETUPDLG_H

#include "mainwindow.h"
#include "databasemanager.h"
#include <QDialog>

namespace Ui {
class DatabaseSetupDLG;
}

class DatabaseSetupDLG : public QDialog
{
    Q_OBJECT

public:
    void setParent(DatabaseManager *p);
    explicit DatabaseSetupDLG(QWidget *parent = 0);
    ~DatabaseSetupDLG();

private slots:
    void on_button_info_clicked();

    void on_button_mtp_clicked();

    void on_button_mtb_clicked();

    void on_pushButton_clicked();

private:
    DatabaseManager *myParent;
    Ui::DatabaseSetupDLG *ui;
};

#endif // DATABASESETUPDLG_H
