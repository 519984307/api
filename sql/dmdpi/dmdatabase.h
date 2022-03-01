#ifndef DMDATABASE_H
#define DMDATABASE_H
#ifdef DM_DPI_WIN32
#include <QObject>
#include "./include/DPI.h"
#include <QDebug>
using namespace std;
struct LastError{
    QString lastError;
    QString text()
    {
        return lastError;
    }
};

class QSqlDatabase : public QObject
{
    Q_OBJECT
public:
    explicit QSqlDatabase(QObject* parent = nullptr);

    QString server() const;
    void setServer(const QString& server);

    QString userName() const;
    void setUserName(const QString& userName);

    QString passWord() const;
    void setPassWord(const QString& passWord);
    bool open();
    void close();
    dhcon hcon() const;
    LastError lastError();

    bool isOpen() const;
    void setIsOpen(bool isOpen);

signals:

private:
    QString m_server;
    QString m_userName;
    QString m_passWord;
    dhenv m_dhenv;
    dhcon m_hcon;
    bool m_isOpen;

};
#endif
#endif // DMDATABASE_H
