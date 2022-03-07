#ifndef DMSQLQUERY_H
#define DMSQLQUERY_H

#include <QObject>
#include "dmsqldb.h"
#include <QJsonArray>
#include <QJsonObject>
extern "C" {
#include "DPItypes.h"
#include "DPI.h"
#include "DPIext.h"
}

class DmSQLQuery : public QObject
{
    Q_OBJECT
public:
    explicit DmSQLQuery(QObject* parent = nullptr);
    bool select(DmSQLDb* db, QString sql, QJsonArray& rows);
    bool insert(DmSQLDb* db, QString tableName, QJsonArray& cols);
    bool update(DmSQLDb* db, QString tableName, QString whereStr, QJsonArray& cols);
    bool update(DmSQLDb* db, QString tableName, QString fieldName, QString value, QJsonArray& cols);
    int rowCount(DmSQLDb* db, QString tableName, QString fieldName, QString value);
    void close();
    DPIRETURN open();
    void getColInfos();
    DmSQLDb* database() const;
    void setDatabase(DmSQLDb* newDatabase);
    int colCount();
    DPIRETURN selectSQL(QString sql);
    bool next();
    QString fieldValue(int i);
    bool execute(QString sql);
    bool saveBlob(DmSQLDb* db, QString sql, QByteArray& data);
    QByteArray getBlob(DmSQLDb* db, QString sql);
signals:
private:
    dhstmt m_dhstmt;
    DmSQLDb* m_database;
    QMap<QString, int> m_conInfos;
    QString m_sql;
    DPIRETURN executeSQL(QString sql);
    DPIRETURN prepareSQL(QString sql);
};

#endif // DMSQLQUERY_H
