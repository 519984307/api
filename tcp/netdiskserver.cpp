#include "netdiskserver.h"

NetDiskServer::NetDiskServer(QObject* parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &NetDiskServer::newClientConnection);
    m_rootPath = QApplication::applicationDirPath() + "/files";
}

void NetDiskServer::newClientConnection()
{
    QTcpSocket* socket = this->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &NetDiskServer::onServerReadyRead);
    connect(socket, &QTcpSocket::aboutToClose, this, &NetDiskServer::onSocketClose);

    m_connectionCount++;
    qDebug() << "新客户端加入" << m_connectionCount;
}

void NetDiskServer::onServerReadyRead()
{
    qDebug() << "接收数据";
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray cmdData = socket->readLine();
    QString cmd = cmdData;
    cmd = cmd.simplified();
    qDebug() << "cmd" << cmd;
    if (cmd == "upload")
    {
        QByteArray data;

        while (true)
        {
            socket->waitForReadyRead(1000);
            int n = socket->bytesAvailable();
            if (n > 0)
            {
                qDebug() << "readData" << n ;
                data.append(socket->readAll());
                QApplication::processEvents();
            }
            else
            {
                break;
            }

        }

        qDebug() << data.size();
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(data);
        QString md5str = md5.result().toHex().toLower();
        qDebug() << md5str;
        QString path = getMd5FilePath(md5str);
        path = m_rootPath + path;
        QDir dir;
        dir.mkpath(path);
        QFile file(path + md5str);
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.flush();
        file.close();
    }
    else if (cmd == "uploadfile")
    {

        QString serverPath = socketReadLine(socket);
        serverPath = serverPath.toUtf8().simplified();
        qDebug() << "serverPath" << serverPath;
        NetDiskFileStream* stream = new NetDiskFileStream(this);

        quint64 md5Size, fileSize;
        QByteArray md5Data, fileData;
        stream->read(socket, md5Size, fileSize, md5Data, fileData);
        delete stream;



        QString clientMd5 = md5Data;
        clientMd5 = clientMd5.simplified();
        qDebug() << " server clientMd5" << clientMd5;









        qDebug() << "allData" << fileData.size();
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(fileData);
        QString md5str = md5.result().toHex().toLower();
        qDebug() << md5str;
        QString path = m_rootPath + serverPath;
        QDir dir;
        QFileInfo info(path);
        dir.mkpath(info.absolutePath());
        if (fileData.size() > 0)
        {
            QFile file(path);
            bool ret = file.open(QIODevice::WriteOnly);
            qDebug() << "fileOpen" << ret;
            file.write(fileData);
            file.flush();
            file.close();
        }

        if (clientMd5 == md5str)
        {
            socket->write("true\n");
        }
        else
        {
            socket->write("false\n");
        }
        qDebug() << (clientMd5 == md5str);
        socket->waitForBytesWritten();
        socket->flush();
        socket->disconnectFromHost();
        socket->close();



    }
    else if (cmd == "downloadfile")
    {

        QString serverPath = socket->readLine();
        serverPath = serverPath.simplified();
        qDebug() << "serverPath" << serverPath;
        NetDiskFileStream* stream = new NetDiskFileStream(this);
        stream->setPathName(m_rootPath + serverPath);
        stream->write(socket);

        delete stream;

        socket->disconnectFromHost();
        socket->close();




    }
    else if (cmd == "download")
    {
        QByteArray md5Data = socket->readLine();
        QString md5 = md5Data;
        md5 = md5.simplified();
        QString path = getMd5FilePath(md5);

        QString filePath = m_rootPath + path + md5;
        qDebug() << filePath;
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        socket->write(data);
        socket->flush();
        socket->waitForBytesWritten();
        file.close();
    }
}

const QString& NetDiskServer::rootPath() const
{
    return m_rootPath;
}

void NetDiskServer::setRootPath(const QString& newRootPath)
{
    m_rootPath = newRootPath;
}
QString NetDiskServer::getMd5FilePath(QString& md5str)
{
    int i = 0;
    QString s = "/";
    while (i < md5str.length())
    {
        s = s + md5str.mid(i, 2) + "/";
        i += 2;
    }
    return s;
}

void NetDiskServer::onSocketClose()
{
    m_connectionCount--;
    qDebug() << "客户端连接断开" << m_connectionCount;
}
