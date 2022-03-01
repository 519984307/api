#include "setodbcdialog.h"
#include "ui_setodbcdialog.h"

SetOdbcDialog::SetOdbcDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetOdbcDialog)
{
    ui->setupUi(this);
    enumOdbcNames();
}

SetOdbcDialog::~SetOdbcDialog()
{
    delete ui;
}

void SetOdbcDialog::on_btnCancel_clicked()
{
    reject();
}

void SetOdbcDialog::on_btnOk_clicked()
{
    if (!m_isConnected)
    {
        QMessageBox::information(this, "提示", "连接测试未通过，请重新测试连接。");
        return;
    }
    accept();
}

void SetOdbcDialog::on_btnTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");



    db.setDatabaseName(ui->cbbOdbc->currentText());
    db.setUserName(ui->edtUser->text());
    db.setPassword(ui->edtPwd->text());
    db.open();
    bool ret = db.isOpen();
    m_isConnected = ret;
    if (ret)
    {
        QMessageBox::information(this, "提示", "连接成功！");

    }
    else
    {
        QMessageBox::information(this, "提示", "连接失败,失败原因是" + db.lastError().text());
    }
}

QString SetOdbcDialog::srcName()
{
    m_srcName = ui->edtSrcName->text();
    return m_srcName;
}

void SetOdbcDialog::setSrcName(const QString& srcName)
{
    m_srcName = srcName;
    ui->edtSrcName->setText(m_srcName);
}

void SetOdbcDialog::enumOdbcNames()
{
    QSettings reg1("HKEY_CURRENT_USER\\Software\\ODBC\\ODBC.INI", QSettings::NativeFormat);
    QStringList names1 = reg1.childGroups();
    ui->cbbOdbc->addItems(names1);



}

QString SetOdbcDialog::password()
{
    return ui->edtPwd->text();
}

void SetOdbcDialog::setPassword(const QString& password)
{
    m_password = password;
    ui->edtPwd->setText(m_password);
}

QString SetOdbcDialog::userName()
{
    return ui->edtUser->text();
}

void SetOdbcDialog::setUserName(const QString& userName)
{
    m_userName = userName;
    ui->edtUser->setText(m_userName);
}

QString SetOdbcDialog::odbcName()
{
    return ui->cbbOdbc->currentText();
}

void SetOdbcDialog::setOdbcName(const QString& odbcName)
{
    m_odbcName = odbcName;
    ui->cbbOdbc->setCurrentText(m_odbcName);
}

bool SetOdbcDialog::isConnected() const
{
    return m_isConnected;
}

void SetOdbcDialog::setIsConnected(bool isConnected)
{
    m_isConnected = isConnected;
}
