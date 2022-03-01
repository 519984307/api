#ifndef MODELHELPER_H
#define MODELHELPER_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTableView>
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSet>
#include <QHeaderView>
#include <QFileDialog>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QSqlField>
#include <QCheckBox>
#include <QSqlRecord>
#include "../../dialogs/clipboardviewdialog.h"

class ModelHelper : public QObject
{
    Q_OBJECT
public:
    explicit ModelHelper(QObject* parent = nullptr);
    ModelHelper(QAbstractItemModel* model, QObject* parent = nullptr);
    ModelHelper(QAbstractItemModel* model, QTableView* view, QObject* parent = nullptr);
    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel* model);

    ///删除数据
    void clearItems();
    QStringList getSelctItemsText(bool distincted = false);

    ///获取标题
    QStringList getColumnNames();

    QTableView* getView() const;
    void setView(QTableView* view);
    void saveDataAsCsvFile(QString path, bool inCludeColumn = true);
    void saveDataAsCsvFile(bool inCludeColumn = true);
    ///添加默认的右键菜单
    void addDefaultContextMenus();
    void selectAllItems();


    QCheckBox* getCheckboxExportColumn() const;
    void setCheckboxExportColumn(QCheckBox* checkboxExportColumn);

    QString getTableName() const;
    void setTableName(const QString& tableName);
    void getTableFieldName(int dataType = 0);

signals:
private:
    QAbstractItemModel* m_model;
    QTableView* m_view;
    QCheckBox* m_checkboxExportColumn;
    ///表名称
    QString m_tableName;

private slots:
    void onActionTriggered();

};

#endif // MODELHELPER_H
