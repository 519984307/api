#ifndef SYNCHTTP_H
#define SYNCHTTP_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QtCore/QTextCodec>
#else
#include <QtCore5Compat/QTextCodec>
#endif
#include <QWidget>

class SyncHttp : public QWidget
{
    Q_OBJECT
public:
    explicit SyncHttp(QWidget* parent = nullptr);
    bool downloadFile(QString url, QString path);
    void setIpAndPort(const QString& ip, int port, QString protocol = "http");
    int postJsonData(const QString& params, QByteArray& data, QByteArray& ret);
    int postJsonData2(const QString& url, QByteArray& data, QByteArray& ret);
    int getJsonData(const QString& params, QByteArray& ret);
    int getJsonData(const QString& url, const QString& params, QByteArray& ret);
    int getHtmlData(const QString& url, QByteArray& ret);
signals:

private:
    QString m_baseUrl;
};

#endif // SYNCHTTP_H
