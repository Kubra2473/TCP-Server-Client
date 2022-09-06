#include "tcpsever.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <iostream>
#include "hex.h"
#include "cryptlib.h"
#include "modes.h"
#include "aes.h"
#include "cryptopp/files.h"
using namespace std;
using namespace CryptoPP;
std::string str = "11111111111111111111111111111111";
std::string str2 ="0000000000000000";
SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(&str[0]),str.size());
SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(&str2[0]),str.size());
QString newCipher;
HexEncoder encoder(new FileSink(std::cout));
TcpSever::TcpSever(QObject *parent):
    QTcpServer(parent),
    socket(new QTcpSocket),
    strTMP("pre")
{
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSomething()));
    connect(this,SIGNAL(alreadyRead()),this,SLOT(returnReadSomething()));
}
TcpSever::~TcpSever()
{
    delete socket;
}
QString TcpSever::getIPAddress()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    return ipAddress.isEmpty() ? QHostAddress(QHostAddress::LocalHost).toString() : ipAddress;
}
quint16 TcpSever::returnPeer()
{
    return socket->peerPort();
}

QString TcpSever::returnIP()
{
    return socket->peerAddress().toString();
}

QString TcpSever::returnOutIP()
{
    QString tmp = GetHtml("https://ip.cn/");
    qDebug() << "returnOutIP" << tmp;
    return GetNetIP(tmp);
}

QString TcpSever::returnReadSomething()
{
    qDebug()<<"Şifreli Metin Server:"<<strTMP;
    return strTMP;
}
void TcpSever::setSendMessage(QString str)
{
    socket->write(QByteArray(str.toLocal8Bit()));
}
void TcpSever::incomingConnection(qintptr handle)
{
    socket->setSocketDescriptor(handle);
}
void TcpSever::readSomething()
{
    strTMP = QString::fromLocal8Bit(socket->readAll());
    emit alreadyRead();
}

QString TcpSever::GetHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return QString(responseData);
}

QString TcpSever::GetNetIP(QString webCode)
{
    QString tmp = webCode.split("IP: ").last();
    return tmp.split("\n<br").first();
}
