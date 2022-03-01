#include "odbcdao.h"
shared_ptr<ODBCDao> ODBCDao::m_dmdao = nullptr;
ODBCDao::~ODBCDao()
{
    qDebug() << "~ODBCDao()";
}

shared_ptr<ODBCDao> ODBCDao::instance()
{
    if (m_dmdao == nullptr) {
        m_dmdao = make_shared<ODBCDao>(new ODBCDao(nullptr));
    }
    return m_dmdao;
}

void ODBCDao::loadConfig()
{
    QSettings ini(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    ini.beginGroup("dmserver");
    m_driver = ini.value("DRIVER").toString();
    m_ip = ini.value("IP").toString();
    m_port = ini.value("PORT").toInt();
    m_dbname = ini.value("DBNAME").toString();
    m_user = ini.value("USER").toString();
    m_pwd = ini.value("PWD").toString();
    ini.endGroup();
    m_db = QSqlDatabase::addDatabase("QODBC");
    qDebug() << "ODBC 驱动是否有效? " << m_db.isValid();
    //如果用ip地址，加上端口号，如192.168.1.1, 1433
    QString connStr;
    if (m_dbtype.compare("SQLServer") == 0) {
        connStr = "Driver={" + m_driver + "};server=" + m_ip + ";database=" + m_dbname + ";uid=" + m_user + ";pwd=" + m_pwd + ";";
    } else if (m_dbtype.compare("DM") == 0) {
        connStr = "DRIVER={" + m_driver + "};server=" + m_ip + ";TCP_PORT=" + QString("%1").arg(m_port) + ";uid=" + m_user + ";pwd=" + m_pwd + ";";
    }
    m_db.setDatabaseName(connStr);
    if (!m_db.open()) {
        qDebug() << "数据库打开失败:" << m_db.lastError().text();
        qDebug() << connStr;
        return;
    } else {
        qDebug() << "数据库打开成功!";
    }
}

ODBCDao::ODBCDao(QObject* parent)
    : AbstractDao(parent)
{
    m_dbtype = "DM";
}

QString ODBCDao::dbtype() const
{
    return m_dbtype;
}

void ODBCDao::setDbtype(const QString& dbtype)
{
    m_dbtype = dbtype;
}

QString ODBCDao::dbname() const
{
    return m_dbname;
}

void ODBCDao::setDbname(const QString& dbname)
{
    m_dbname = dbname;
}

bool ODBCDao::select(QString sql, QSqlQuery& qry)
{
    qry = QSqlQuery(m_db);
    bool ret = qry.exec(sql);
    qDebug() << sql;
    return ret;
}

bool ODBCDao::execute(QString sql)
{
    QSqlQuery qry(m_db);
    bool ret = qry.exec(sql);
    qDebug() << sql;
    return ret;
}

ODBCDao* odbcdao()
{

    return ODBCDao::instance().get();
}

QString dbName()
{
    return odbcdao()->dbname();
}
