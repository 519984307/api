#include "modelhelper.h"

ModelHelper::ModelHelper(QObject* parent) : QObject(parent)
{
    m_model = nullptr;
    m_checkboxExportColumn = nullptr;
}

ModelHelper::ModelHelper(QAbstractItemModel* model, QObject* parent)
{
    m_model = model;
    m_view = nullptr;
    m_checkboxExportColumn = nullptr;
    this->setParent(parent);

}

ModelHelper::ModelHelper(QAbstractItemModel* model, QTableView* view, QObject* parent)
{
    m_model = model;
    m_view = view;
    m_checkboxExportColumn = nullptr;
    this->setParent(parent);
    m_view->setModel(m_model);
}

QAbstractItemModel* ModelHelper::model() const
{
    return m_model;
}

void ModelHelper::setModel(QAbstractItemModel* model)
{
    m_model = model;
}

void ModelHelper::clearItems()
{
    m_model->removeRows(0, m_model->rowCount());
}

QStringList ModelHelper::getSelctItemsText(bool distincted)
{
    QStringList values;
    QSet<QString> valueSets;
    QItemSelectionModel* selModel = m_view->selectionModel();
    QModelIndexList indexes = selModel->selectedIndexes();
    for (int i = 0; i < indexes.count(); i++)
    {
        QModelIndex index = indexes[i];
        QString text = qvariant_cast<QString>(m_model->itemData(index)[Qt::DisplayRole]);
        if (text.trimmed() != "")
        {
            valueSets << text;
            values << text;
        }



    }

    return distincted ? valueSets.toList() : values;
}

QStringList ModelHelper::getColumnNames()
{

    QStringList stl;
    for (int i = 0; i < m_model->columnCount(); i++)
    {
        stl << m_model->headerData(i, Qt::Horizontal).toString();
    }
    return stl;

}

QTableView* ModelHelper::getView() const
{
    return m_view;
}

void ModelHelper::setView(QTableView* view)
{
    m_view = view;
}

void ModelHelper::saveDataAsCsvFile(QString path, bool inCludeColumn)
{
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(m_model);
     QSqlTableModel* sqlModel = dynamic_cast<QSqlTableModel*>(m_model);


    QString s = "";
    if (inCludeColumn)
    {
        QStringList cols;
        for (int i = 0; i < m_model->columnCount(); i++)
        {

                cols << "\"" + m_model->headerData(i, Qt::Horizontal).toString() + "\"";


        }
        s = cols.join(",") + "\n";

    }


    for (int j = 0; j < m_model->rowCount(); j++)
    {
        QStringList values;
        for (int i = 0; i < m_model->columnCount(); i++)
        {
            if (model!=nullptr)
            {
               values << "\"" + model->item(j, i)->text() + "\"";
            }else if (sqlModel!=nullptr)
            {
                values << "\"" + sqlModel->record(j).value(i).toString()+ "\"";
            }

        }
        s = s + values.join(",") + "\n";
    }
    s = s.trimmed();
    qDebug() << path;
    qDebug() << s;
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(s.toLocal8Bit());
    file.close();

}

void ModelHelper::saveDataAsCsvFile(bool inCludeColumn)
{
    QString path = QFileDialog::getSaveFileName();
    if (path == "")
    {
        return;
    }
    QFileInfo info(path);
    if (info.suffix() != ".csv")
    {
        path += ".csv";
    }
    saveDataAsCsvFile(path, inCludeColumn);


}


void ModelHelper::addDefaultContextMenus()
{
    for (int i=m_view->actions().count()-1;i>=0;i--)
    {
       QAction *act=m_view->actions().at(i);
       m_view->removeAction(act);
       delete act;
    }
    QStringList menuNames;
    menuNames << "复制表名称" << "复制表头" << "复制选中项(排除重复)" << "复制选中项"
              << "复制当前行('A','B'格式)" << "复制字段名(表名.字段名格式)"
              << "复制字段名(@表名.字段名格式)" << "复制字段名({@表名.字段名}格式)"
              << "-" << "选中当前行" << "选中当前列" << "全选" <<
              "-" << "导出csv文件" << "查看剪贴板";
    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        if (menuNames[i] == "-")
        {
            act->setSeparator(true);
        }
        else
        {
            act->setText(menuNames[i]);
            connect(act, &QAction::triggered, this, &ModelHelper::onActionTriggered);
        }

        m_view->addAction(act);
    }

}

void ModelHelper::selectAllItems()
{
    m_view->selectAll();

}

QCheckBox* ModelHelper::getCheckboxExportColumn() const
{
    return m_checkboxExportColumn;
}

void ModelHelper::setCheckboxExportColumn(QCheckBox* checkboxExportColumn)
{
    m_checkboxExportColumn = checkboxExportColumn;
}

QString ModelHelper::getTableName() const
{
    return m_tableName;
}

void ModelHelper::setTableName(const QString& tableName)
{
    m_tableName = tableName;
}

void ModelHelper::getTableFieldName(int dataType)
{
    QModelIndex index = m_view->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    QString s;
    if (dataType == 0)
    {
        s =  m_tableName + "." + m_model->headerData(index.column(), Qt::Horizontal).toString();

    }
    else if (dataType == 1)
    {
        s = "@" + m_tableName + "." + m_model->headerData(index.column(), Qt::Horizontal).toString();
    }
    else if (dataType == 2)
    {
        s = "${@" + m_tableName + "." + m_model->headerData(index.column(), Qt::Horizontal).toString() + "}";
    }

    qApp->clipboard()->setText(s);
}

void ModelHelper::onActionTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "复制表名称")
    {
        qApp->clipboard()->setText(m_tableName);
    }
    else if (act->text() == "复制选中项")
    {
        QStringList values = getSelctItemsText();
        qApp->clipboard()->setText(values.join("\n"));

    }
    else if (act->text() == "复制表头")
    {
        QStringList values = getColumnNames();
        qApp->clipboard()->setText(values.join(","));

    }
    else if (act->text() == "复制选中项(排除重复)")
    {
        QStringList values = getSelctItemsText(true);
        qApp->clipboard()->setText(values.join("\n"));
    }
    else if (act->text() == "导出csv文件")
    {
        bool b = true;
        if (m_checkboxExportColumn != nullptr)
        {
            b = m_checkboxExportColumn->isChecked();
        }
        saveDataAsCsvFile(b);
    }
    else if (act->text() == "全选")
    {
        selectAllItems();
    }
    else if (act->text() == "选中当前行")
    {
        QModelIndex index = m_view->currentIndex();
        if (!index.isValid())
        {
            return;
        }
        m_view->selectRow(index.row());
    }
    else if (act->text() == "选中当前列")
    {
        QModelIndex index = m_view->currentIndex();
        if (!index.isValid())
        {
            return;
        }
        m_view->selectColumn(index.column());
    }
    else if (act->text() == "复制当前行('A','B'格式)")
    {
        QModelIndex index = m_view->currentIndex();
        if (!index.isValid())
        {
            return;
        }
        m_view->selectRow(index.row());

        QStringList values;

        QItemSelectionModel* selModel = m_view->selectionModel();
        QModelIndexList indexes = selModel->selectedIndexes();
        for (int i = 0; i < indexes.count(); i++)
        {
            QModelIndex index = indexes[i];
            QString text = qvariant_cast<QString>(m_model->itemData(index)[Qt::DisplayRole]);

            values << "'" + text + "'";


        }
        QString s = values.join(",");
        qApp->clipboard()->setText(s);

    }
    else if (act->text() == "查看剪贴板")
    {
        showClipBoardViewer();
    }
    else if (act->text() == "复制字段名(表名.字段名格式)")
    {
        getTableFieldName(0);
    }
    else if (act->text() == "复制字段名(@表名.字段名格式)")
    {
        getTableFieldName(1);
    }
    else if (act->text() == "复制字段名({@表名.字段名}格式)")
    {
        getTableFieldName(2);
    }

}


