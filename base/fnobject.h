#ifndef FNOBJECT_H
#define FNOBJECT_H

#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QList>
#include "../global/globaldata.h"

class FnObject : public QObject
{
    Q_OBJECT
public:
    explicit FnObject(QObject* parent = nullptr);

    QString uuid() const;
    void setUuid(const QString& uuid);

    QString name() const;
    void setName(const QString& name);

    QString remark() const;
    void setRemark(const QString& remark);

    QDateTime createTime() const;
    void setCreateTime(const QDateTime& createTime);

    QString value() const;
    void setValue(const QString& value);

    int index() const;
    void setIndex(int index);

    int id() const;
    void setId(int id);

    const QString& caption() const;
    void setCaption(const QString& newCaption);

signals:

protected:
    QString m_uuid;
    QString m_name;
    QString m_caption;
    QString m_remark;
    QDateTime m_createTime;
    QString m_value;
    int m_index;
    int m_id;

};

template<typename T>
T getObjectByUuid(QList<T>& list, QString uuid)
{
    for (int i = 0; i < list.count(); i++)
    {
        T t = list.at(i);
        if (t->uuid() == uuid)
        {
            return t;
        }

    }
    return nullptr;
}

template<typename T>
T getObjectByName(QList<T>& list, QString name)
{
    for (int i = 0; i < list.count(); i++)
    {
        T t = list.at(i);
        if (t->name() == name)
        {
            return t;
        }

    }
    return nullptr;
}

#endif // FNOBJECT_H
