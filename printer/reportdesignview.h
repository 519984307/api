#ifndef REPORTDESIGNVIEW_H
#define REPORTDESIGNVIEW_H

#include <QWidget>
#include "../controls/base/fnwidgetapi.h"
#include "../controls/base/widgethelper.h"
#include "reportcell.h"
#include "../draw/drawobject.h"
#include "../controls/base/controloperation.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "reportcellpropertydialog.h"


namespace Ui
{
class ReportDesignView;
}

class ReportDesignView : public QWidget
{
    Q_OBJECT

public:
    explicit ReportDesignView(QWidget* parent = nullptr);
    ~ReportDesignView();
    QList<ReportCell*> cells;
    QList<ReportCell*> copyCells;
    ControlOperation operation() const;
    void setOperation(ControlOperation newOperation);
    void deselectAll();
    void setSelectCellsHorTile();
    void setSelectCellsVerTile();
    void getSelectCells(QList<ReportCell*>& selCells);
    void copySelectCells();
    void pasteSelectCells();

    const QString& fileName() const;
    void setFileName(const QString& newFileName);
    void saveToFile(QString fileName);
    void loadFromFile(QString fileName);
    void processSelectCells(std::function<void(ReportCell* cell)> processCell);
    ReportCell* getFirstSelectCell();
    QPoint getCursorPoint();

    int getSelectCellsCount();

    void showCellPropertyDialog(ReportCell* cell);

    void fitToMaxHeight();
    double calSelectCellsSumWidth();
    void resetSelectCellsHeightByFactor(double factor);
    ///删除选中对象
    void deleteSelectCells();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::ReportDesignView* ui;
    WidgetHelper* m_helper;
    double m_pageLeft;
    double m_pageTop;
    ControlOperation m_operation;
    DrawObject* m_drawObj;
    QString m_fileName;
};


#endif // REPORTDESIGNVIEW_H
