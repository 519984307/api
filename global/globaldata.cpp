#include "globaldata.h"
QString GlobalData::qssText = "";
QString GlobalData::areacode = "";
QString GlobalData::userName = "";
QString GlobalData::password = "";
QString GlobalData::baseUrl = "";
QString GlobalData::uid = "";
QString GlobalData::fileServerIp = "127.0.0.1";
QString GlobalData::fileServerPort = "1480";
GlobalData::GlobalData(QObject* parent)
    : QObject(parent)
{
}

QString GlobalData::createUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    return ret;
}

QString newNoDashUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    ret = ret.replace("-", "");
    return ret;
}

QString newDashUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    return ret;
}
