#include "dmsqldb.h"

DmSQLDb::DmSQLDb(QObject* parent) : QObject(parent)
{
    dpi_alloc_env(&m_henv);
    dpi_alloc_con(m_henv, &m_hcon);
}

bool DmSQLDb::connectDb(QString ip, QString dbName, QString userName, QString pwd)
{
    string s_ip, s_userName, s_pwd;
    s_ip = ip.toStdString();
    sdbyte* svr = (sdbyte*)(s_ip.c_str());
    s_userName = userName.toStdString();
    sdbyte* user = (sdbyte*)(s_userName.c_str());
    s_pwd = pwd.toStdString();
    sdbyte* spwd = (sdbyte*)(s_pwd.c_str());

    DPIRETURN ret = dpi_login(m_hcon, svr, user, spwd);
    bool m_isOpen = ret == DSQL_SUCCESS;
    return m_isOpen ;
}

dhcon DmSQLDb::hcon() const
{
    return m_hcon;
}

const QString& DmSQLDb::databaseName() const
{
    return m_databaseName;
}

void DmSQLDb::setDatabaseName(const QString& newDatabaseName)
{
    m_databaseName = newDatabaseName;
}
