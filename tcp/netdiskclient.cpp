#include "netdiskclient.h"

NetDiskClient::NetDiskClient(QObject* parent)
    : AbstractDistClient(parent)
{

    m_ip = "127.0.0.1";
    m_port = 9001;
}



bool NetDiskClient::connectHost()
{
//    m_socket->connectToHost(m_ip, m_port);
//    m_isConnected = m_socket->isOpen();
    return m_isConnected;
}

bool NetDiskClient::isConnected() const
{
    return m_isConnected;
}

void NetDiskClient::setIsConnected(bool isConnected)
{
    m_isConnected = isConnected;
}

void NetDiskClient::uploadFile(QString filename)
{
    QTcpSocket* socket = new QTcpSocket();
    qDebug() << filename;
    QCryptographicHash md5(QCryptographicHash::Md5);
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    md5.addData(data);
    QString md5str = md5.result().toHex().toLower();

    socket->connectToHost(m_ip, m_port);


    QString cmd = "upload\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    socket->write(cmdData);
    int sendSize = socket->write(data);
    qDebug() << data.size();
    qDebug() << sendSize;

    while (socket->waitForBytesWritten())
    {
        QApplication::processEvents();
    }
    socket->flush();
    socket->disconnectFromHost();
    socket->close();
    delete socket;

}

void NetDiskClient::uploadFile(QString filename, QString md5)
{
    QTcpSocket* socket = new QTcpSocket();
    qDebug() << filename;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    socket->connectToHost(m_ip, m_port);


    QString cmd = "upload\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    socket->write(cmdData);
    int sendSize = socket->write(data);
    qDebug() << data.size();
    qDebug() << sendSize;

    while (socket->waitForBytesWritten())
    {
        QApplication::processEvents();
    }
    socket->flush();
    socket->disconnectFromHost();
    socket->close();
    delete socket;
}

bool NetDiskClient::uploadFileByPath(QString serverPathName, QString pathName)
{

    qDebug() << serverPathName;
    qDebug() << pathName;
    QFileInfo fileInfo(pathName);
    if (!fileInfo.exists())
    {
        return true;
    }

    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost(m_ip, m_port);
    socketWrite(socket, "uploadfile");
    socketWrite(socket, serverPathName);

    NetDiskFileStream* stream = new NetDiskFileStream(this);
    stream->setPathName(pathName);
    stream->write(socket);
    delete stream;


    while (socket->bytesAvailable() == 0)
    {
        QApplication::processEvents();
    }
    QString ret = socketReadLine(socket);
    socket->disconnectFromHost();
    socket->close();



    delete socket;
    ret = ret.simplified();
    return ret == "true";


}

void NetDiskClient::downloadFileByMd5(QString md5, QString fileName)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost(m_ip, m_port);

    QString cmd = "download\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    socket->write(cmdData);
    cmdData.clear();
    cmdData.append(md5 + "\n");
    socket->write(cmdData);
    QByteArray data;
    while (socket->waitForReadyRead(3000))
    {
        data.append(socket->readAll());
        qDebug() << "readdata";
    }
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.flush();
    file.close();
    socket->disconnectFromHost();
    socket->close();
    delete socket;

}

bool NetDiskClient::downloadFileByPath(QString serverPathName, QString pathName)
{
    qDebug() << serverPathName;
    qDebug() << pathName;
    QFileInfo info(pathName);
    QDir dir;
    dir.mkpath(info.absolutePath());


    QTcpSocket* socket = new QTcpSocket(this);




    socket->connectToHost(m_ip, m_port);
    socket->waitForConnected();
    qDebug() << "client connected" << socket->isOpen();
    socketWrite(socket, "downloadfile");
    socketWrite(socket, serverPathName);

    NetDiskFileStream* stream = new NetDiskFileStream(this);
    quint64 fileSize, md5Size;
    QByteArray md5Data, fileData;
    stream->read(socket, md5Size, fileSize, md5Data, fileData);
    delete stream;
    QString serverMd5 = md5Data;
    QString clientMd5;

    if (fileData.size() > 0)
    {
        QFile file(pathName);
        bool ret = file.open(QIODevice::WriteOnly);
        qDebug() << "fileOpen" << ret;
        file.write(fileData);
        file.flush();
        file.close();

        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(fileData);
        clientMd5 = md5.result().toHex().toLower();

    }








    socket->disconnectFromHost();
    socket->close();
    return (serverMd5 == clientMd5);


}
