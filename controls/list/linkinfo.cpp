#include "linkinfo.h"

LinkInfo::LinkInfo(QObject* parent) : QObject(parent)
{

}

const QString& LinkInfo::name() const
{
    return m_name;
}

void LinkInfo::setName(const QString& newName)
{
    m_name = newName;
}

const QString& LinkInfo::url() const
{
    return m_url;
}

void LinkInfo::setUrl(const QString& newUrl)
{
    m_url = newUrl;
}

const QRect& LinkInfo::rect() const
{
    return m_rect;
}

void LinkInfo::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

const QDateTime& LinkInfo::createDateTime() const
{
    return m_createDateTime;
}

void LinkInfo::setCreateDateTime(const QDateTime& newCreateDateTime)
{
    m_createDateTime = newCreateDateTime;
}
