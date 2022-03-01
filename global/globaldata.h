#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QUuid>

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject* parent = nullptr);
    static QString qssText;
    static QString areacode;
    static QString userName;
    static QString uid;
    static QString password;
    static QString baseUrl;
    static QString fileServerIp;
    static QString fileServerPort;
    static QString createUuid();
signals:
};
QString newNoDashUuid();
QString newDashUuid();
#endif // GLOBALDATA_H
