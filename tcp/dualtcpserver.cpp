#include "dualtcpserver.h"

DualTcpServer::DualTcpServer(QObject* parent)
    : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &DualTcpServer::onTcpServerNewConnection);
    subTcpServer = new QTcpServer(this);
    connect(subTcpServer, &QTcpServer::newConnection, this, &DualTcpServer::onSubTcpServerNewConnection);
}

bool DualTcpServer::startServer(QString ip, int port, int subPort)
{
    if (tcpServer->isListening())
    {
        return false;
    }
    m_ip = ip;
    m_port = port;
    m_subPort = subPort;
    tcpServer->listen(QHostAddress::Any, m_port);
    subTcpServer->listen(QHostAddress::Any, m_subPort);
    return true;
}

void DualTcpServer::writeLn(QString s)
{
    s = s + "\n";
    QString info = QString("共%1个客户端连接").arg(m_clients.count());
    emit onWriteLn(nullptr, info);
    for (int i = 0; i < m_clients.count(); i++)
    {
        QTcpSocket* socket = m_clients[i];
        QByteArray ba = s.toLocal8Bit();
        socket->write(ba);
        socket->flush();
        emit onWriteLn(socket, s);
    }
}

void DualTcpServer::writeUtf16LeLn(QString s)
{
    s = s + "\n";
    QString info = QString("共%1个客户端连接").arg(m_clients.count());
    emit onWriteLn(nullptr, info);
    for (int i = 0; i < m_clients.count(); i++)
    {
        QTcpSocket* socket = m_clients[i];
        QTextCodec* code = QTextCodec::codecForName("UTF16-LE");
        QByteArray ba = code->fromUnicode(s);
        socket->write(ba);
        socket->flush();
        emit onWriteLn(socket, s);
    }
}

void DualTcpServer::onTcpServerNewConnection()
{
    QTcpSocket* socket = tcpServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &DualTcpServer::onTcpServerReadyRead);
}

void DualTcpServer::onSubTcpServerNewConnection()
{
    QTcpSocket* socket = subTcpServer->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &DualTcpServer::socketDisconnect);
    m_clients << socket;
}

void DualTcpServer::onTcpServerReadyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QString msg = QTextCodec::codecForName("gb2312")->toUnicode(socket->readAll()).simplified();
    emit onTcpServerExecute(msg);
}

void DualTcpServer::socketDisconnect()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    m_clients.removeOne(socket);
    emit onWriteLn(nullptr, "客户端端口断开");
    emit onWriteLn(nullptr, QString("共有%1个客户端").arg(m_clients.count()));
}
