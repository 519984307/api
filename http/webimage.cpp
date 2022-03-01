#include "webimage.h"

WebImage::WebImage(QObject* parent) : QObject(parent)
{

}

bool WebImage::download(QString url, QString savePath)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply* reply = manager->get(request);
    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(10000);
    loop.exec();
    if (timer.isActive())
    {
        timer.stop();
    }
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (code == 200)
    {
        QByteArray data = reply->readAll();
        QFile file(savePath);
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.close();
    }

    delete manager;
    return code == 200;
}
