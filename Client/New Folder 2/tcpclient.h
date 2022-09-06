#ifndef INDOORGUIDEDCLIENT_H
#define INDOORGUIDEDCLIENT_H
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QAbstractSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);
    ~TcpClient();
    void newConnect();
    void setIP(QString ip);
    void setPort(int port);
    void sendMessage(QString str);
    void sendDWMessage();
    bool returnConnectState();
    QString returnIP();
    QString returnPort();
    int returnError();
signals:
    void alreadyRead();
public slots:
    QString returnMessage();
private slots:
    void readMessage();
    void isConnect();
    void isDisconnect();
    void isError(QAbstractSocket::SocketError er);
protected:
    void incomingConnection(qintptr handle);
private:
    QTcpSocket *socket = Q_NULLPTR;
    QString clientIP;
    int clientPort;
    QString message;
    bool connectBool;
    QAbstractSocket::SocketError m_error;
};

#endif // INDOORGUIDEDCLIENT_H
