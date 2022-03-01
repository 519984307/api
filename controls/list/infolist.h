#ifndef INFOLIST_H
#define INFOLIST_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QWheelEvent>
#include "infolistitem.h"
#include "../base/widgethelper.h"


namespace Ui
{
class InfoList;
}

class InfoList : public QWidget
{
    Q_OBJECT

public:
    explicit InfoList(QWidget* parent = nullptr);
    ~InfoList();
    InfoListItem* addItem(QString caption);
    InfoListItem* findItemByUuid(const QString& uuid);
    void clearItems();
signals:
    void clickInfoListItem(InfoListItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    Ui::InfoList* ui;
    QList<InfoListItem*> m_items;
    WidgetHelper* m_helper;
};

#endif // INFOLIST_H
