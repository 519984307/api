#ifndef DBTABLEWIDGET_H
#define DBTABLEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "modelhelper.h"
#include <QAction>
#include <QClipboard>

namespace Ui
{
class DbTableWidget;
}

class DbTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DbTableWidget(QWidget* parent = nullptr);
    ~DbTableWidget();

    QString tableName() const;
    void setTableName(const QString& tableName);



    QSqlDatabase db() const;
    void setDb(const QSqlDatabase& db);

private slots:

    void on_btnRefresh_clicked();

private:
    Ui::DbTableWidget* ui;
    QString m_tableName;
    QSqlDatabase m_db;
    QSqlTableModel* m_model;
    ModelHelper* m_helper;
};

#endif // DBTABLEWIDGET_H
