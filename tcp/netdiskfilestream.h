#ifndef NETDISKFILESTREAM_H
#define NETDISKFILESTREAM_H

#include <QObject>
#include <QDataStream>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QApplication>

class NetDiskFileStream : public QObject
{
    Q_OBJECT
public:
    explicit NetDiskFileStream(QObject* parent = nullptr);

    const QString& PathName() const;
    void setPathName(const QString& newPathName);
    void write(QTcpSocket* socket);
    void read(QTcpSocket* socket, quint64& md5Size, quint64& fileSize, QByteArray& md5Data,
              QByteArray& fileData);
signals:
private:
    QString m_PathName;

};

#endif // NETDISKFILESTREAM_H
