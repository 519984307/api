#ifndef MSSQLDAO_H
#define MSSQLDAO_H

#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <memory>
using namespace std;

class MsSQLDao : public QObject {
    Q_OBJECT
public:
    static shared_ptr<MsSQLDao> instance();

    bool connectDB();
    void loadInfoFromConfig();
    void getInfoFromConfig(QString& ip, QString& db, QString& user, QString& pwd);
    void saveInfoToConfig(QString ip, QString db, QString user, QString pwd);
    bool isConnected();
    bool testConnected(QString ip, QString db, QString user, QString pwd);
    bool select(QString sql, QSqlQuery& qry);
    void execute(QString sql);

private:
    explicit MsSQLDao(QObject* parent = nullptr);
    static shared_ptr<MsSQLDao> m_instance;
    QSqlDatabase m_DbInstance;
    QString m_ip;
    QString m_db;
    QString m_user;
    QString m_pwd;
    bool m_isConnected;
signals:

public slots:
};
shared_ptr<MsSQLDao> msSQLDao();

#endif // MSSQLDAO_H
