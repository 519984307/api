#include "rsschannel.h"

RssChannel::RssChannel(QObject* parent) : QObject(parent)
{


}

QString RssChannel::url() const
{
    return m_url;
}

void RssChannel::setUrl(const QString& url)
{
    m_url = url;
}

void RssChannel::openUrl(const QString& url)
{
    m_url = url;
    SyncHttpObject* http = new SyncHttpObject();
    QByteArray ret;
    http->getHtmlData(m_url, ret);
    QDomDocument doc;
    doc.setContent(ret);
    QDomElement rssNode = doc.documentElement();
    QDomNode channelNode = rssNode.firstChild();
    for (int i = 0; i < channelNode.childNodes().count(); i++)
    {
        QDomNode itemNode = channelNode.childNodes().at(i);
        if (itemNode.nodeName() == "item")
        {
            RssInfo rssInfo;
            for (int j = 0; j < itemNode.childNodes().count(); j++)
            {
                QDomNode infoNode = itemNode.childNodes().at(j);
                QString name = infoNode.nodeName();
                QString value = infoNode.toElement().text();
                if (name == "title")
                {
                    rssInfo.title = value;
                }
                else if (name == "content")
                {
                    rssInfo.content = value;
                }
            }
            items << rssInfo;
        }
    }


    delete http;
}
