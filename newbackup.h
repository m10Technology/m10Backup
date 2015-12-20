#ifndef NEWBACKUP_H
#define NEWBACKUP_H

#include <QDialog>

namespace Ui {
class NewBackup;
}

class NewBackup : public QDialog
{
    Q_OBJECT

public:
    explicit NewBackup(QWidget *parent = 0);
    ~NewBackup();

private slots:
    bool on_pushButton_clicked();

    void on_backupOnce_clicked();

    void on_scheduleBackup_clicked();

    void on_pushButton_2_clicked();

    void on_button1_clicked();

    void on_button2_clicked();

private:
    Ui::NewBackup *ui;
};

#endif // NEWBACKUP_H
