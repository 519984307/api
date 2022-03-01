#ifndef RSSCHANNEL_H
#define RSSCHANNEL_H

#include <QObject>
#include "synchttpobject.h"
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
struct RssInfo
{
    QString title;
    QString content;
};

class RssChannel : public QObject
{
    Q_OBJECT
public:
    explicit RssChannel(QObject* parent = nullptr);

    QString url() const;
    void setUrl(const QString& url);
    void openUrl(const QString& url);
    QList<RssInfo> items;

signals:

private:
    QString m_url;

};

#endif // RSSCHANNEL_H
