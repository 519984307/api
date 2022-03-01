#ifndef NETDISKSERVER_H
#define NETDISKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QThread>
#include "sockethelp.h"
#include "netdiskfilestream.h"
#include <QAtomicInt>
class NetDiskServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NetDiskServer(QObject* parent = nullptr);

    const QString& rootPath() const;
    void setRootPath(const QString& newRootPath);
    QString getMd5FilePath(QString& md5str);
public:
    void onSocketClose();
    void newClientConnection();
    void onServerReadyRead();
signals:
private:
    QString m_rootPath;
    QAtomicInt m_connectionCount = 0;

};

#endif // NETDISKSERVER_H
