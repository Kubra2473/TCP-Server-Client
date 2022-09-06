#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSever = new TcpSever;
    QString str;
    str = "network ip:"+tcpSever->returnOutIP()+" port:1414";
    str =  str + "\n\nlocal ip:"+tcpSever->getIPAddress();
    ui->label_3->setText(str);
    if(!tcpSever->listen(QHostAddress::Any,1414)){
        this->close();
    }
    connect(tcpSever,SIGNAL(alreadyRead()),this,SLOT(readMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpSever;
}


void MainWindow::readMessage()
{
    /*ui->label_2->setText(QString("Mesaj:").arg(QString::number(tcpSever->returnPeer()),
                                                tcpSever->returnReadSomething()));*/
}

void MainWindow::on_pushButton_clicked()
{
   // tcpSever->setSendMessage(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString Str = tcpSever->returnOutIP();
    clipboard->setText(Str);
}
