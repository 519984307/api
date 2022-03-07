#include "abstractdiskclient.h"

AbstractDiskClient::AbstractDiskClient(QObject* parent) : QObject(parent)
{

}

const QString& AbstractDiskClient::ip() const
{
    return m_ip;
}

void AbstractDiskClient::setIp(const QString& newIp)
{
    m_ip = newIp;
}

int AbstractDiskClient::port() const
{
    return m_port;
}

void AbstractDiskClient::setPort(int newPort)
{
    m_port = newPort;
}

bool AbstractDiskClient::uploadFileByPath(QString serverPathName, QString pathName)
{
    return true;
}

bool AbstractDiskClient::uploadFileByPath(QString serverPath, QString serverFileName, QString pathName)
{
    return true;
}

bool AbstractDiskClient::downloadFileByPath(QString serverPathName, QString pathName)
{
    return true;
}
