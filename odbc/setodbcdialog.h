#ifndef SETODBCDIALOG_H
#define SETODBCDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSettings>

namespace Ui
{
class SetOdbcDialog;
}

class SetOdbcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetOdbcDialog(QWidget* parent = nullptr);
    ~SetOdbcDialog();

    bool isConnected() const;
    void setIsConnected(bool isConnected);


    QString odbcName() ;
    void setOdbcName(const QString& odbcName);

    QString userName() ;
    void setUserName(const QString& userName);

    QString password() ;
    void setPassword(const QString& password);

    QString srcName();
    void setSrcName(const QString& srcName);
    void enumOdbcNames();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnTest_clicked();

private:
    Ui::SetOdbcDialog* ui;
    bool m_isConnected;
    QString m_srcName;
    QString m_odbcName;
    QString m_userName;
    QString m_password;
};

#endif // SETODBCDIALOG_H
