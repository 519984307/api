#ifndef DMQUERY_H
#define DMQUERY_H

#include <QObject>
#include "dmapi.h"
#include <QTextCodec>
#include <QMessageBox>
#include "dmvalueobject.h"
using namespace std;
class DmValueObject;
class DmQuery : public QObject
{
    Q_OBJECT
public:
    explicit DmQuery(QObject* parent = nullptr);

    DmDataBase* database() const;
    void setDatabase(DmDataBase* database);
    bool execute(QString sql);
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


signals:
private:
    DmDataBase* m_database;
    dhstmt m_dhstmt;
    DPIRETURN executeSQL(QString sql);
    QMap<QString, int> m_conInfos;


};

#endif // DMQUERY_H
