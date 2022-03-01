#include "fnobject.h"

FnObject::FnObject(QObject* parent) : QObject(parent)
{
    m_createTime = QDateTime::currentDateTime();
    m_uuid = newNoDashUuid();

}

QString FnObject::uuid() const
{
    return m_uuid;
}

void FnObject::setUuid(const QString& uuid)
{
    m_uuid = uuid;
}

QString FnObject::name() const
{
    return m_name;
}

void FnObject::setName(const QString& name)
{
    m_name = name;
}

QString FnObject::remark() const
{
    return m_remark;
}

void FnObject::setRemark(const QString& remark)
{
    m_remark = remark;
}

QDateTime FnObject::createTime() const
{
    return m_createTime;
}

void FnObject::setCreateTime(const QDateTime& createTime)
{
    m_createTime = createTime;
}

QString FnObject::value() const
{
    return m_value;
}

void FnObject::setValue(const QString& value)
{
    m_value = value;
}

int FnObject::index() const
{
    return m_index;
}

void FnObject::setIndex(int index)
{
    m_index = index;
}

int FnObject::id() const
{
    return m_id;
}

void FnObject::setId(int id)
{
    m_id = id;
}

const QString& FnObject::caption() const
{
    return m_caption;
}

void FnObject::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}








