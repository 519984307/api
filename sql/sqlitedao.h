#ifndef SQLITEDAO_H
#define SQLITEDAO_H

#include "sqlitewrapper.h"
#include <QApplication>
#include <QObject>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>

class SqliteDao : public QObject
{
    Q_OBJECT
public:
    static SqliteDao* instance();
    static void freeInstance();
    SqliteWrapper* sqliteWrapper() const;
    bool transaction();
    void commit();
signals:

private:
    explicit SqliteDao(QObject* parent = nullptr);
    static SqliteDao* m_instance;
    SqliteWrapper* m_sqliteWrapper;
};
SqliteDao* sqliteDao();
#endif // SQLITEDAO_H
