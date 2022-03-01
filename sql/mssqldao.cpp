#include "mssqldao.h"

shared_ptr<MsSQLDao> MsSQLDao::m_instance = nullptr;
shared_ptr<MsSQLDao> MsSQLDao::instance()
{
    if (m_instance == nullptr) {
        m_instance = shared_ptr<MsSQLDao>(new MsSQLDao());
    }
    return m_instance;
}

bool MsSQLDao::connectDB()
{
    loadInfoFromConfig();
    m_DbInstance.close();
    m_DbInstance.removeDatabase("db1");
    QString connStr = QString("Driver={sql server};server=%1;database=%2;uid=%3;pwd=%4;")
                          .arg(m_ip)
                          .arg(m_db)
                          .arg(m_user)
                          .arg(m_pwd);
    m_DbInstance = QSqlDatabase::addDatabase("QODBC", "db1");
    m_DbInstance.setDatabaseName(connStr);
    m_DbInstance.open();
    m_isConnected = m_DbInstance.isOpen();

    return m_isConnected;
}

void MsSQLDao::loadInfoFromConfig()
{
    QSettings ini(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    ini.beginGroup("database");
    m_ip = ini.value("ip").toString();
    m_db = ini.value("db").toString();
    m_user = ini.value("user").toString();
    m_pwd = ini.value("pwd").toString();
    ini.endGroup();
}

void MsSQLDao::getInfoFromConfig(QString& ip, QString& db, QString& user, QString& pwd)
{
    ip = m_ip;
    db = m_db;
    user = m_user;
    pwd = m_pwd;
}

void MsSQLDao::saveInfoToConfig(QString ip, QString db, QString user, QString pwd)
{
    QSettings ini(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    ini.beginGroup("database");
    m_ip = ip;
    ini.setValue("ip", ip);
    m_db = db;
    ini.setValue("db", db);
    m_user = user;
    ini.setValue("user", user);
    m_pwd = pwd;
    ini.setValue("pwd", pwd);

    ini.endGroup();
}

bool MsSQLDao::isConnected()
{
    return m_isConnected;
}

bool MsSQLDao::testConnected(QString ip, QString db, QString user, QString pwd)
{
    QSqlDatabase m_testdb;
    m_testdb.close();
    m_testdb.removeDatabase("db2");
    QString connStr = QString("Driver={sql server};server=%1;database=%2;uid=%3;pwd=%4;")
                          .arg(ip)
                          .arg(db)
                          .arg(user)
                          .arg(pwd);
    m_testdb = QSqlDatabase::addDatabase("QODBC", "db2");
    m_testdb.setDatabaseName(connStr);
    m_testdb.open();
    bool ret = m_testdb.isOpen();
    if (ret == true) {
        QMessageBox::information(nullptr, "提示", "连接成功");
    } else {
        QMessageBox::information(nullptr, "提示", "连接失败，原因是:" + m_testdb.lastError().text());
    }
    m_testdb.close();
    return ret;
}

bool MsSQLDao::select(QString sql, QSqlQuery& qry)
{
    qry = QSqlQuery(m_DbInstance);
    return qry.exec(sql);
}

void MsSQLDao::execute(QString sql)
{
    QSqlQuery qry(m_DbInstance);
    int ret = qry.exec(sql);

    if (ret == false) {
        qDebug() << sql;
        qDebug() << qry.lastError();
    } else {
        qDebug() << sql;
    }
}

MsSQLDao::MsSQLDao(QObject* parent)
    : QObject(parent)
{
}

shared_ptr<MsSQLDao> msSQLDao()
{
    return MsSQLDao::instance();
}
