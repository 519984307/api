#ifndef WORDSTYLETABLE_H
#define WORDSTYLETABLE_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QPainter>
#include "../base/widgethelper.h"


#include "wordstyletablecell.h"
namespace Ui
{
class WordStyleTable;
}

class WordStyleTable : public QWidget
{
    Q_OBJECT

public:
    explicit WordStyleTable(QWidget* parent = nullptr);
    ~WordStyleTable();
    void loadFromJson(QString pathName);
    QJsonArray dataToJsonArray();
    QJsonArray notNullDataToJsonArray();
    void loadDataFromArray(QJsonArray& arr);
    QString cellValue(QString fieldName);
    WordStyleTableCell* findCellByName(QString name);
signals:
    void cellButtonClick(WordStyleTableCell* cell);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::WordStyleTable* ui;
    int m_marginLeft;
    int m_marginTop;
    int m_cellWidth;
    int m_cellHeight;
    QList<WordStyleTableCell*> m_cells;
    WidgetHelper*  m_helper;
    QMap<QString, WordStyleTableCell*> m_fieldCellMaps;

};

#endif // WORDSTYLETABLE_H
