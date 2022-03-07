#ifndef ABSTRACTDISKCLIENT_H
#define ABSTRACTDISKCLIENT_H

#include <QObject>

class AbstractDiskClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDiskClient(QObject* parent = nullptr);

    const QString& ip() const;
    void setIp(const QString& newIp);

    int port() const;
    void setPort(int newPort);
    virtual bool uploadFileByPath(QString serverPathName, QString pathName);
    virtual bool uploadFileByPath(QString serverPath, QString serverFileName, QString pathName);
    virtual bool downloadFileByPath(QString serverPathName, QString pathName);
signals:
protected:
    QString m_ip;
    int m_port;
};

#endif // ABSTRACTDISKCLIENT_H
