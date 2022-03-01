#ifndef HTTPSTATUSINFO_H
#define HTTPSTATUSINFO_H

#include <QObject>
#include <QMap>
#include <memory>
#include <QDebug>

using namespace std;

class HttpStatusInfo : public QObject
{
    Q_OBJECT
public:
    explicit HttpStatusInfo(QObject* parent = nullptr);
    ~HttpStatusInfo();
    QString getStatusInfo(int code);
    static shared_ptr<HttpStatusInfo> m_instance;
signals:
private:
    QMap<int, QString> m_httpStatusInfos;

};
HttpStatusInfo* httpStatusInfo();

#endif // HTTPSTATUSINFO_H
