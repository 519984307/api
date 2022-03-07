#ifndef HTTPFILETRANSFERCLIENT_H
#define HTTPFILETRANSFERCLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpMultiPart>
#include <QDebug>
#include <QEventLoop>
#include <QFile>

class HttpFileTransferClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpFileTransferClient(QObject* parent = nullptr);
    bool download(QString url, QMap<QString, QString>& values, QString saveFileName);
    bool upload(QString url, QMap<QString, QString>& values, QString savefieldName, QString saveFileName);

signals:

};

#endif // HTTPFILETRANSFERCLIENT_H
