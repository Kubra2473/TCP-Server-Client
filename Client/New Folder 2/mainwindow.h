#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string Encrypt(std::string a);

private slots:
    void on_pushButton_clicked();
    void readSSMessage();

    void on_pushButton_update_clicked();

    QString on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
};

#endif // MAINWINDOW_H
