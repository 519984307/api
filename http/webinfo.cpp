#include "webinfo.h"

WebInfo::WebInfo(QWidget* parent)
    : SyncHttp(parent)
{
    qDebug() << QSslSocket::sslLibraryBuildVersionString();
}

QString WebInfo::getTitle(QString url)
{
    QByteArray ret;
    getHtmlData(url, ret);
    //qDebug() << code;
    QTextCodec::codecForHtml(ret);
    QString s = ret;
    QRegExp reg("<title>.{1,}</title>");
    for (int i = 0; i = reg.indexIn(s, i), i >= 0; i += reg.matchedLength())
    {
        QString s = reg.cap(0);
        s = s.replace("<title>", "");
        s = s.replace("</title>", "");
        return s;
    }
    return "";
}

QImage WebInfo::getFavicon(QString url, bool& isBmp)
{
    QUrl u(url);
    QString protocol;
    if (url.indexOf("https") >= 0)
    {
        protocol = "https://";
    }
    else
    {
        protocol = "http://";
    }
    QString hostUrl = protocol + u.host() + "/favicon.ico";

    qDebug() << hostUrl;



    QByteArray ret;
    QImage img;
    int code = getHtmlData(hostUrl, ret);
    if (ret.size() == 0)
    {
        code = 0;
    }
    if (code == 200)
    {
        QBuffer buf(&ret);

        isBmp = this->isBmp(ret);
        if (isBmp)
        {
            img.load(&buf, "bmp");
        }
        else
        {
            img.load(&buf, "ico");
        }
    }

    return img;
}

bool WebInfo::isBmp(QByteArray& data)
{
    if ((data[0] == 'B') && (data[1] == 'M'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
