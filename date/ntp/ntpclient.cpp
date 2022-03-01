#include "ntpclient.h"

NtpClient::NtpClient(QObject* parent) : QObject(parent)
{
    m_hostName = "ntp.aliyun.com";
}

const QString& NtpClient::hostName() const
{
    return m_hostName;
}

void NtpClient::setHostName(const QString& newHostName)
{
    m_hostName = newHostName;
}

bool NtpClient::connectToHost()
{
    m_hostInfo = QHostInfo::fromName(m_hostName);
    QList<QHostAddress> hostInfos = m_hostInfo.addresses();
    if (hostInfos.count() == 0)
    {
        return false;
    }
    QString ipAddress = hostInfos.first().toString();
    qDebug() << ipAddress;
    QEventLoop loop;
    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket, SIGNAL(connected()), this, SLOT(connectsucess()));
    connect(m_udpSocket, &QUdpSocket::readyRead, &loop, &QEventLoop::quit);
    m_udpSocket->connectToHost(m_hostName, 123);
    bool ret = m_udpSocket->isOpen();
    if (!ret)
    {
        return false;
    }
    loop.exec();
    readingDataGrams();
    return true;
}

void NtpClient::readingDataGrams()
{
    qDebug() << "readingDataGrams()";
    QByteArray newTime;
    QDateTime Epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));
    do
    {
        newTime.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->read(newTime.data(), newTime.size());
    }
    while (m_udpSocket->hasPendingDatagrams());

    QByteArray TransmitTimeStamp ;
    TransmitTimeStamp = newTime.right(8);
    quint32 seconds = TransmitTimeStamp[0];
    quint8 temp = 0;
    for (int j = 1; j <= 3; j++)
    {
        seconds = seconds << 8;
        temp = TransmitTimeStamp[j];
        seconds = seconds + temp;
    }
    m_dateTime.setTime_t(seconds - Epoch.secsTo(unixStart));
    m_udpSocket->disconnectFromHost();
    m_udpSocket->close();

}

void NtpClient::connectsucess()
{
    qDebug() << "connectsucess()";
    qint8 LI = 0; //无预告
    qint8 VN = 3; //版本号
    qint8 MODE = 3; //客户端几
    qint8 STRATUM = 0; //表示本地时钟层次水平
    qint8 POLL = 4; //测试间隔
    qint8 PREC = -6; //表示本地时钟精度
    QDateTime Epoch(QDate(1900, 1, 1));
    qint32 second = quint32(Epoch.secsTo(QDateTime::currentDateTime()));

    qint32 temp = 0;
    QByteArray timeRequest(48, 0);
    timeRequest[0] = (LI << 6) | (VN << 3) | (MODE);
    timeRequest[1] = STRATUM;
    timeRequest[2] = POLL;
    timeRequest[3] = PREC & 0xff;
    timeRequest[5] = 1;
    timeRequest[9] = 1;

    //40到43字节保存原始时间戳，即客户端发送的时间
    timeRequest[40] = (temp = (second & 0xff000000) >> 24);
    temp = 0;
    timeRequest[41] = (temp = (second & 0x00ff0000) >> 16);
    temp = 0;
    timeRequest[42] = (temp = (second & 0x0000ff00) >> 8);
    temp = 0;
    timeRequest[43] = ((second & 0x000000ff));
    m_udpSocket->flush();
    m_udpSocket->write(timeRequest);
    m_udpSocket->flush();
}

const QDateTime& NtpClient::dateTime() const
{
    return m_dateTime;
}

void NtpClient::setDateTime(const QDateTime& newDateTime)
{
    m_dateTime = newDateTime;
}

QDateTime getServerTime(QString hostName)
{
    NtpClient* c = new NtpClient(nullptr);
    c->setHostName(hostName);
    bool ret = c->connectToHost();
    QDateTime d;
    if (!ret)
    {
        d = QDateTime::fromString("2099-12-31", "yyyy-MM-dd");
        return d;
    }
    d = c->dateTime();
    delete c;
    return d;

}
