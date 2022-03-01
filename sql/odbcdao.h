#ifndef DMDAO_H
#define DMDAO_H

#include "abstractdao.h"
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <memory>
#include <qsqldatabase.h>
using namespace std;
class ODBCDao : public AbstractDao {
    Q_OBJECT
public:
    ~ODBCDao();
    static shared_ptr<ODBCDao> instance();
    void loadConfig();
    explicit ODBCDao(QObject* parent = nullptr);
    QString dbtype() const;
    void setDbtype(const QString& dbtype);

    QString dbname() const;
    void setDbname(const QString& dbname);
    bool select(QString sql, QSqlQuery& qry);
    bool execute(QString sql);
signals:
private:
    static shared_ptr<ODBCDao> m_dmdao;
    QString m_driver;
    QString m_ip;
    int m_port;
    QString m_dbname;
    QString m_user;
    QString m_pwd;
    QSqlDatabase m_db;
    QString m_dbtype;
};
ODBCDao* odbcdao();
QString dbName();
#endif // DMDAO_H
