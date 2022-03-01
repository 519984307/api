#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include "../base/widgethelper.h"
#include "mapwidgetobject.h"
#include <QMutex>
namespace Ui
{
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget* parent = nullptr);
    ~MapWidget();

    QString backgroundFilePath() const;
    void setBackgroundFilePath(const QString& backgroundFilePath);
    QList<MapWidgetObject*> objects;
    MapWidgetObject* newMapObject() const;
    void setNewMapObject(MapWidgetObject* newMapObject);
    int mapLeft() const;
    void setMapLeft(int mapLeft);

    int mapTop() const;
    void setMapTop(int mapTop);
    void clearObjects();

    bool mapObjectsMoveEnabled() const;
    void setMapObjectsMoveEnabled(bool mapObjectsMoveEnabled);

    MapWidgetObject* selMapObject() const;
    void setSelMapObject(MapWidgetObject* selMapObject);
    void deleteSelectMapObject();
    static QMutex locker;
signals:
    void onAddNewMapWidgetObject(MapWidget* mapWidget, MapWidgetObject* newObj);
    void onMoveMapWidgetObject(MapWidget* mapWidget, MapWidgetObject* obj);
protected:
    void paintEvent(QPaintEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::MapWidget* ui;
    QPixmap m_backgroundImage;
    QString m_backgroundFilePath;
    int m_mapLeft;
    int m_mapTop;
    WidgetHelper m_helper;
    MapWidgetObject* m_newMapObject;
    MapWidgetObject* m_movedMapObject;
    MapWidgetObject* m_selMapObject;
    bool m_mapObjectsMoveEnabled;
};

#endif // MAPWIDGET_H
