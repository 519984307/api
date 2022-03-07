#ifndef NETDISKCLIENT_H
#define NETDISKCLIENT_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QTcpSocket>
#include <QNetworkConfigurationManager>
#include <QApplication>
#include "sockethelp.h"
#include <QDir>
#include <QThread>
#include <QDataStream>
#include "netdiskfilestream.h"
#include "abstractdistclient.h"

class NetDiskClient : public AbstractDistClient
{
    Q_OBJECT
public:
    explicit NetDiskClient(QObject* parent = nullptr);


    bool connectHost();

    bool isConnected() const;
    void setIsConnected(bool isConnected);
    void uploadFile(QString filename);
    void uploadFile(QString filename, QString md5);
    bool uploadFileByPath(QString serverPathName, QString pathName);
    void downloadFileByMd5(QString md5, QString fileName);
    bool downloadFileByPath(QString serverPathName, QString pathName);

signals:

private:
    bool m_isConnected;

};

#endif // NETDISKCLIENT_H
