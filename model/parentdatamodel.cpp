#include "parentdatamodel.h"

ParentDataModel::ParentDataModel(QObject* parent)
    : QObject(parent)
{
}

int ParentDataModel::id()
{
    return m_id;
}

void ParentDataModel::setId(int id)
{
    m_id = id;
}

int ParentDataModel::pid()
{
    return m_pid;
}

void ParentDataModel::setPid(int pid)
{
    m_pid = pid;
}

QString ParentDataModel::name()
{
    return m_name;
}

QString ParentDataModel::name() const
{
    return m_name;
}

void ParentDataModel::setName(const QString& name)
{
    m_name = name;
}

QString ParentDataModel::remark()
{
    return m_remark;
}

QString ParentDataModel::remark() const
{
    return m_remark;
}

void ParentDataModel::setRemark(const QString& remark)
{
    m_remark = remark;
}

int ParentDataModel::sid() const
{
    return m_sid;
}

void ParentDataModel::setSid(int sid)
{
    m_sid = sid;
}

QString ParentDataModel::devid() const
{
    return m_devid;
}

void ParentDataModel::setDevid(const QString& devid)
{
    m_devid = devid;
}

QString ParentDataModel::objuuid() const
{
    return m_objuuid;
}

void ParentDataModel::setObjuuid(const QString& objuuid)
{
    m_objuuid = objuuid;
}

int ParentDataModel::uid() const
{
    return m_uid;
}

void ParentDataModel::setUid(int uid)
{
    m_uid = uid;
}

QString ParentDataModel::path() const
{
    return m_path;
}

void ParentDataModel::setPath(const QString &path)
{
    m_path = path;
}
