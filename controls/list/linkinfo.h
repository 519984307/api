#ifndef LINKINFO_H
#define LINKINFO_H

#include <QObject>
#include <QRect>
#include <QDateTime>

class LinkInfo : public QObject
{
    Q_OBJECT
public:
    explicit LinkInfo(QObject* parent = nullptr);

    const QString& name() const;
    void setName(const QString& newName);

    const QString& url() const;
    void setUrl(const QString& newUrl);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    const QDateTime& createDateTime() const;
    void setCreateDateTime(const QDateTime& newCreateDateTime);

signals:
private:
    QString m_name;
    QString m_url;
    QDateTime m_createDateTime;
    QRect m_rect;

};

#endif // LINKINFO_H
