#ifndef SQLRUNWIDGET_H
#define SQLRUNWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QClipboard>
#include <QAction>
#include "../dbcontrols/modelhelper.h"

namespace Ui
{
class SqlRunWidget;
}

class SqlRunWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SqlRunWidget(QWidget* parent = nullptr);
    ~SqlRunWidget();

    QSqlDatabase db() const;
    void setDb(const QSqlDatabase& db);
    QString uuid() const;
    void setUuid(const QString& uuid);

    QString sql() const;
    void setSql(const QString& sql);


signals:
    void saveSql(QString uuid, QString sql);
private slots:
    void on_btnRun_clicked();


private:
    Ui::SqlRunWidget* ui;
    QSqlDatabase m_db;
    QStandardItemModel* m_model;
    QString m_uuid;
    QString m_sql;
    ModelHelper* m_helper;
};

#endif // SQLRUNWIDGET_H
