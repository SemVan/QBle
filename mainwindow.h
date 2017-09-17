#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ble_linker.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ble_linker *linker;
    QList<QString> devices;
private slots:
    void newDevFound(QString devName, QString address);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
