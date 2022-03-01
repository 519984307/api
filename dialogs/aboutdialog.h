#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget* parent = nullptr);
    ~AboutDialog();

    QString appName() const;
    void setAppName(const QString& appName);

    QPixmap icon() const;
    void setIcon(const QPixmap& icon);

private slots:
    void on_btnClose_clicked();

private:
    Ui::AboutDialog* ui;
    QString m_appName;
    QPixmap m_icon;
};
void showAboutDialog(QString appName, QPixmap icon);

#endif // ABOUTDIALOG_H
