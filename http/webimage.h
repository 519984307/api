#ifndef WEBIMAGE_H
#define WEBIMAGE_H

#include <QObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QTimer>

class WebImage : public QObject
{
    Q_OBJECT
public:
    explicit WebImage(QObject* parent = nullptr);
    bool download(QString url, QString savePath);
signals:

};

#endif // WEBIMAGE_H
