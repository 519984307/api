#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#include <QObject>
#include <winsock2.h>
#include <QHostInfo>
#include <QUdpSocket>
#include <QDate>
#include <QEventLoop>

class NtpClient : public QObject
{
    Q_OBJECT
public:
    explicit NtpClient(QObject* parent = nullptr);

    const QString& hostName() const;
    void setHostName(const QString& newHostName);
    bool connectToHost();
    void readingDataGrams();

    const QDateTime& dateTime() const;
    void setDateTime(const QDateTime& newDateTime);

signals:
public slots:
    void connectsucess();

private:
    QString m_hostName;
    QHostInfo m_hostInfo;
    QUdpSocket* m_udpSocket;
    QDateTime m_dateTime;
};
QDateTime getServerTime(QString hostName = "ntp.aliyun.com");

#endif // NTPCLIENT_H
