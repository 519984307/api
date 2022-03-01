#include "synchttp.h"

SyncHttp::SyncHttp(QWidget* parent)
    : QWidget(parent)
{
}

bool SyncHttp::downloadFile(QString url, QString path)
{
    return true;
}

void SyncHttp::setIpAndPort(const QString& ip, int port, QString protocol)
{
    m_baseUrl = QString("%1://%2:%3/").arg(protocol).arg(ip).arg(port);
    qDebug() << m_baseUrl;
}

int SyncHttp::postJsonData(const QString& params, QByteArray& data, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    qDebug() << m_baseUrl + params;
    requet.setUrl(QUrl(m_baseUrl + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->post(requet, data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttp::postJsonData2(const QString& url, QByteArray& data, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;

    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->post(requet, data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;

}



int SyncHttp::getJsonData(const QString& params, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(m_baseUrl + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttp::getJsonData(const QString& url, const QString& params, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttp::getHtmlData(const QString& url, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));

    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (code == 200)
    {
        ret = reply->readAll();
    }
    delete reply;
    delete manager;
    return code;
}
