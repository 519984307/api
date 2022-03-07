#ifndef DMSQLDB_H
#define DMSQLDB_H

#include <QObject>

#include <QDebug>
extern "C" {
#include "DPI.h"
}
using namespace std;

class DmSQLDb : public QObject
{
    Q_OBJECT
public:
    explicit DmSQLDb(QObject* parent = nullptr);

    bool connectDb(QString ip, QString dbName, QString userName, QString pwd);
    dhcon hcon() const;

    const QString& databaseName() const;
    void setDatabaseName(const QString& newDatabaseName);

signals:
private:
    dhenv m_henv;
    dhcon m_hcon;
    QString m_databaseName;

};

#endif // DMSQLDB_H
