#include "dmdatabase.h"
#ifdef DM_DPI_WIN32
QSqlDatabase::QSqlDatabase(QObject* parent) : QObject(parent)
{

}

QString QSqlDatabase::server() const
{
    return m_server;
}

void QSqlDatabase::setServer(const QString& server)
{
    m_server = server;
}

QString QSqlDatabase::userName() const
{
    return m_userName;
}

void QSqlDatabase::setUserName(const QString& userName)
{
    m_userName = userName;
}

QString QSqlDatabase::passWord() const
{
    return m_passWord;
}

void QSqlDatabase::setPassWord(const QString& passWord)
{
    m_passWord = passWord;
}

bool QSqlDatabase::open()
{
    //获取环境句柄
    DPIRETURN ret = dpi_alloc_env(&m_dhenv);

    dpi_alloc_con(m_dhenv, &m_hcon);

    string s1, s2, s3;
    s1 = m_server.toStdString();
    sdbyte* svr = (sdbyte*)(s1.c_str());
    s2 = m_userName.toStdString();
    sdbyte* user = (sdbyte*)(s2.c_str());
    s3 = m_passWord.toStdString();
    sdbyte* pwd = (sdbyte*)(s3.c_str());

    ret = dpi_login(m_hcon, svr, user, pwd);
    m_isOpen=ret ==DSQL_SUCCESS;
    return m_isOpen ;
}

void QSqlDatabase::close()
{
    dpi_logout(m_hcon);
}

dhcon QSqlDatabase::hcon() const
{
    return m_hcon;
}


LastError QSqlDatabase::lastError()
{
    LastError err;
    err.lastError=m_isOpen==true?"连接成功":"连接失败";
    return err;
}

bool QSqlDatabase::isOpen() const
{
    return m_isOpen;
}

void QSqlDatabase::setIsOpen(bool isOpen)
{
    m_isOpen = isOpen;
}
#endif




