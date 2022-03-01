#ifndef PARENTDATAMODEL_H
#define PARENTDATAMODEL_H

#include <QObject>

class ParentDataModel : public QObject {
    Q_OBJECT
public:
    explicit ParentDataModel(QObject* parent = nullptr);

    int id();
    void setId(int id);

    int pid();
    void setPid(int pid);

    QString name();
    QString name() const;
    void setName(const QString& name);

    QString remark();
    QString remark() const;
    void setRemark(const QString& remark);

    int sid() const;
    void setSid(int sid);

    QString devid() const;
    void setDevid(const QString& devid);

    QString objuuid() const;
    void setObjuuid(const QString& objuuid);

    int uid() const;
    void setUid(int uid);

    QString path() const;
    void setPath(const QString& path);

signals:

private:
    int m_id;
    int m_pid;
    int m_sid;
    int m_uid;
    QString m_devid;
    QString m_name;
    QString m_remark;
    QString m_objuuid;
    QString m_path;
};

#endif // PARENTDATAMODEL_H
