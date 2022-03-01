#include "sockethelp.h"



void socketWrite(QTcpSocket* socket, QString s)
{
    QByteArray cmdData;

    QString cmd = s + "\n";
    cmdData.append(cmd.toUtf8());
    socket->write(cmdData);
    qDebug() << s;



}

void socketWriteEnd(QTcpSocket* socket)
{
    while (socket->waitForBytesWritten())
    {
        QApplication::processEvents();
    }
    socket->flush();
}

QString socketReadLine(QTcpSocket* socket)
{
    QString ret;
    do
    {
        QByteArray s = socket->readLine();
        ret += QString::fromUtf8(s);
        if (s.endsWith("\n"))
        {
            break;
        }
    }
    while (socket->waitForReadyRead(100));
    ret = ret.simplified();
    return ret;
}

int socketWriteFile(QTcpSocket* socket, QString pathName)
{
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    socket->write(data);
    file.close();
    return data.size();
}
