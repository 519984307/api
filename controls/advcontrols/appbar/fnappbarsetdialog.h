#ifndef FNAPPBARSETDIALOG_H
#define FNAPPBARSETDIALOG_H

#include <QDialog>
#include "fnappbarsetitemwidget.h"
#include <QListWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "fnappbaritem.h"


namespace Ui {
class FnAppBarSetDialog;
}

class FnAppBarSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FnAppBarSetDialog(QWidget *parent = nullptr);
    ~FnAppBarSetDialog();


    const QString &configPath() const;
    void setConfigPath(const QString &newConfigPath);
    void saveConfigs();


    const QList<FnAppBarItem *> &items() const;
    void setItems(const QList<FnAppBarItem *> &newItems);

private slots:
    void on_btnAdd_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::FnAppBarSetDialog *ui;
    QString m_configPath;
    QList<FnAppBarItem*> m_items;
};


#endif // FNAPPBARSETDIALOG_H
