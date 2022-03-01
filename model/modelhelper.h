#ifndef MODELHELPER_H
#define MODELHELPER_H

#include <QObject>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

void itemMoveUp(QTableView* lvData, QStandardItemModel* model);
void itemMoveDown(QTableView* lvData, QStandardItemModel* model);
void itemClickNext(QTableView* lvData, QStandardItemModel* model);
void itemClickPre(QTableView* lvData, QStandardItemModel* model);
#endif // MODELHELPER_H
