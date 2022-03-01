#ifndef QSqlQuery_H
#define QSqlQuery_H
#ifdef DM_DPI_WIN32
#include <QObject>
#include "dmapi.h"
#include <QTextCodec>
#include <QMessageBox>
#include "dmvalueobject.h"
#include "dmdatabase.h"

using namespace std;

struct QSqlError{
    QString text()
    {
        return "";
    }
};

class DmValueObject;
class QSqlQuery
{

public:

     QSqlQuery (QSqlDatabase* database);
     QSqlQuery (QSqlDatabase& database);
    QSqlQuery();
    QSqlDatabase* database() const;
    void setDatabase(QSqlDatabase* database);
    bool execute(QString sql);
    bool exec(QString sql);
    bool select(QString sql);
    void commit();
    void rollback();
    int colCount();
    bool next();
    DmValueObject value(int i);
    DmValueObject value(QString colName);
    void close();
    DPIRETURN open();
    void getColInfos();

    void prepare(QString sql);
    void exec();
    void clear();
    QSqlError lastError();
    void bindValue(int i,QByteArray &ba);


signals:
private:
    QSqlDatabase* m_database;
    dhstmt m_dhstmt=0;
    DPIRETURN executeSQL(QString sql);
    QMap<QString, int> m_conInfos;
    QString m_sql;

};


#endif
#endif // QSqlQuery_H
