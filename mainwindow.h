#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool isBackingUp;
    int getCurrentID();
    void refresh();
    bool checkForFileExists(QString fileLocation);
    bool performBackup(QString from,QString to);
    void toggleIsBackingUp();
    void changeUI(int conformID);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionLoad_mtb_Backup_File_triggered();

    void on_button1_released();

    void on_button2_released();

    void on_button3_released();

    void on_actionNew_Backup_triggered();

private:
    QString getDefaultMtp();
    Ui::MainWindow *ui;
    bool isFirstRun();

private slots:
    void setMyPercent(int percent);
    void on_actionLoad_Previous_Backup_triggered();
    void on_listWidget_2_itemSelectionChanged();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
