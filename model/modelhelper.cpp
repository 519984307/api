#include "modelhelper.h"


void itemMoveUp(QTableView* lvData, QStandardItemModel* model)
{
    QModelIndex index = lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == 0)
    {
        return;
    }
    QList<QStandardItem*> items = model->takeRow(row);
    row--;
    model->insertRow(row, items);
    index = model->indexFromItem(items.at(0));
    lvData->setCurrentIndex(index);

}

void itemMoveDown(QTableView* lvData, QStandardItemModel* model)
{
    QModelIndex index = lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == (model->rowCount() - 1))
    {
        return;
    }
    QList<QStandardItem*> items = model->takeRow(row);
    row++;
    model->insertRow(row, items);
    index = model->indexFromItem(items.at(0));
    lvData->setCurrentIndex(index);
}

void itemClickNext(QTableView* lvData, QStandardItemModel* model)
{
    QModelIndex index = lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == (model->rowCount() - 1))
    {
        return;
    }
    row++;
    index = model->index(row, 0);
    lvData->setCurrentIndex(index);
    emit lvData->clicked(index);
}

void itemClickPre(QTableView* lvData, QStandardItemModel* model)
{
    QModelIndex index = lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == 0)
    {
        return;
    }
    row--;
    index = model->index(row, 0);
    lvData->setCurrentIndex(index);
    emit lvData->clicked(index);
}
