#include "dualtcpclient.h"

DualTcpClient::DualTcpClient(QObject* parent)
    : QObject(parent)
{
}

DualTcpClient::~DualTcpClient()
{
    qDebug() << "~DualTcpClient()";
}
