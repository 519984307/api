#include "dmdatabase.h"

DmDataBase::DmDataBase(QObject* parent) : QObject(parent)
{

}

QString DmDataBase::server() const
{
    return m_server;
}

void DmDataBase::setServer(const QString& server)
{
    m_server = server;
}

QString DmDataBase::userName() const
{
    return m_userName;
}

void DmDataBase::setUserName(const QString& userName)
{
    m_userName = userName;
}

QString DmDataBase::passWord() const
{
    return m_passWord;
}

void DmDataBase::setPassWord(const QString& passWord)
{
    m_passWord = passWord;
}

void DmDataBase::open()
{
    //获取环境句柄
    DPIRETURN ret = dpi_alloc_env(&m_dhenv);
    qDebug() << m_dhenv;
    qDebug() << ret;
    dpi_alloc_con(m_dhenv, &m_hcon);
    qDebug() << m_hcon;
    sdbyte* svr = (sdbyte*)("127.0.0.1");
    sdbyte* user = (sdbyte*)("SYSDBA");
    sdbyte* pwd = (sdbyte*)("Rs_new1234");
    ret = dpi_login(m_hcon, svr, user, pwd);
    qDebug() << ret;
}

void DmDataBase::close()
{
    dpi_logout(m_hcon);
}

dhcon DmDataBase::hcon() const
{
    return m_hcon;
}
