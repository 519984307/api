#include "netdiskfilestream.h"

NetDiskFileStream::NetDiskFileStream(QObject* parent) : QObject(parent)
{

}

const QString& NetDiskFileStream::PathName() const
{
    return m_PathName;
}

void NetDiskFileStream::setPathName(const QString& newPathName)
{
    m_PathName = newPathName;
}

void NetDiskFileStream::write(QTcpSocket* socket)
{
    //1 总大小  int
    //2 md5内容大小 int
    //3  文件大小 int
    //4 md5内容
    //5 文件内容


    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_6);
    //设置头
    out << quint64(0) << quint64(0) << quint64(0);




    QFile file(m_PathName);
    file.open(QIODevice::ReadOnly);
    QByteArray fileData = file.readAll();

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(fileData);
    QByteArray md5Data = md5.result().toHex().toLower();
    out << md5Data;
    out << fileData;
    out.device()->seek(0);
    out << quint64(block.size());
    out.device()->seek(sizeof(quint64));
    out << quint64(md5Data.size());
    out.device()->seek(sizeof(quint64) * 2);
    out << quint64(fileData.size());






    out.device()->seek(0);
    socket->write(block, block.size());

    socket->waitForBytesWritten();


}

void NetDiskFileStream::read(QTcpSocket* socket, quint64& md5Size, quint64& fileSize,  QByteArray& md5Data, QByteArray& fileData)
{
    while (socket->bytesAvailable() == 0)
    {
        QApplication::processEvents();
    }
    QByteArray data;
    do
    {
        data.append(socket->readAll());
    }
    while (socket->waitForReadyRead(100));
    qDebug() << "client" << data.size();
    QDataStream stream(data);
    quint64 allSize;
    stream.device()->seek(0);
    stream >> allSize;
    qDebug() << allSize;
    stream >> md5Size;
    qDebug() << md5Size;

    stream >> fileSize;
    qDebug() << fileSize;
    md5Data.resize(32);
    stream >> md5Data;
    qDebug() << md5Data;
    fileData.resize(fileSize);
    stream >> fileData;

}


