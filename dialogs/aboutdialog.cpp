#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_btnClose_clicked()
{
    close();
}

QPixmap AboutDialog::icon() const
{
    return m_icon;
}

void AboutDialog::setIcon(const QPixmap& icon)
{
    m_icon = icon;
    m_icon = m_icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->lblLogo->setPixmap(m_icon);
}

QString AboutDialog::appName() const
{
    return m_appName;
}

void AboutDialog::setAppName(const QString& appName)
{
    m_appName = appName;
    ui->lblAppName->setText(m_appName);
}

void showAboutDialog(QString appName, QPixmap icon)
{
    AboutDialog* dlg = new AboutDialog();
    dlg->setAppName(appName);
    dlg->setWindowTitle("关于\"" + appName + "\"");
    dlg->setIcon(icon);
    dlg->exec();
    delete dlg;

}
