#ifndef FNGRID_H
#define FNGRID_H

#include <QWidget>
#include "fngridrow.h"
#include <QPainter>
#include <QWheelEvent>
#include "fngridcelledit.h"
#include "../base/widgethelper.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui
{
class FnGrid;
}
class FnGridRow;
class FnGridCell;
class FnGrid : public QWidget
{
    Q_OBJECT

public:
    explicit FnGrid(QWidget* parent = nullptr);
    ~FnGrid();
    QList<FnGridRow*> gridRows;

    FnGridRow* appendRow(int rowHeight = 32);
    FnGridRow* appendChildRow(FnGridRow* parentRow, int rowHeight = 32);
    FnGridRow* getLastChildRow(FnGridRow* parentRow);
    void getSelectedCell();
    void setNextCells();
    //从Json载入模板
    void loadFromJson(QString pathName);
    //在指定行后插入新行
    FnGridRow*  insertRowAfterCurRow(FnGridRow* curRow, int rowHeight = 32);
    //在指定行前插入新行
    FnGridRow*  insertRowBeforeCurRow(FnGridRow* curRow, int rowHeight = 32);
    void setCellFocus(FnGridCell* cell);
    FnGridRow* getNextRow(FnGridCell* cell);
    FnGridRow* getRowByCode(QString code);
    bool isEditOnClick() const;
    void setIsEditOnClick(bool newIsEditOnClick);
    void removeRow(FnGridRow* row);
    FnGridCell* selectedCell();
    ///设置顺序号
    void setHeaderChildsOrder(FnGridRow* headerRow, int col = 0);
signals:
    void clickCell(FnGridCell* cell);
    void rightClickCell(FnGrid* grid, FnGridCell* cell);
    void selectCellKeyPress(FnGridCell* cell);

public slots:
    void onGridEditReturnPressed();

    void paintEvent(QPaintEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void leaveEvent(QEvent* event);
private:
    Ui::FnGrid* ui;
    FnGridCellEdit* m_gridEdit;
    FnGridCell* m_selectedCell;
    WidgetHelper* m_helper;
    bool m_isEditOnClick;
    void editCell();

};

#endif // FNGRID_H
