#ifndef DMDATABASE_H
#define DMDATABASE_H

#include <QObject>
#include "DPI.h"
#include <QDebug>

class DmDataBase : public QObject
{
    Q_OBJECT
public:
    explicit DmDataBase(QObject* parent = nullptr);

    QString server() const;
    void setServer(const QString& server);

    QString userName() const;
    void setUserName(const QString& userName);

    QString passWord() const;
    void setPassWord(const QString& passWord);
    void open();
    void close();
    dhcon hcon() const;

signals:

private:
    QString m_server;
    QString m_userName;
    QString m_passWord;
    dhenv m_dhenv;
    dhcon m_hcon;

};

#endif // DMDATABASE_H
