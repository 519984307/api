#ifndef COUNTLABELVIEW_H
#define COUNTLABELVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QAction>
#include "../base/fnwidgetapi.h"
#include "../base/widgethelper.h"
#include "../../dialogs/setvaluedialog.h"
#include "countlabelitem.h"


namespace Ui
{
class CountLabelView;
}

class CountLabelView : public QWidget
{
    Q_OBJECT

public:
    explicit CountLabelView(QWidget* parent = nullptr);
    ~CountLabelView();
    void addMenus();
    void loadCountLabel(QString caption, QString uuid);
    void updateValues();
signals:
    void addCountLabel(CountLabelItem* item);
    void updateCountLabelValue(CountLabelItem* item);
    void clickLabel(CountLabelItem* item);
public slots:
    void onAddActionTriggered();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::CountLabelView* ui;
    WidgetHelper* m_helper;
    QAction* m_addAction;
    QList<CountLabelItem*> m_items;
};

#endif // COUNTLABELVIEW_H
