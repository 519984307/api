#ifndef MAP3DDISGNVIEWER_H
#define MAP3DDISGNVIEWER_H

#include <QWidget>
#include <QMouseEvent>

#include "../base/basewidget.h"
#include "../base/controloperation.h"
#include "map3dobject.h"
#include "../api/draw/drawobject.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui
{
class Map3dDisgnViewer;
}

class Map3dDisgnViewer : public BaseWidget
{
    Q_OBJECT

public:
    explicit Map3dDisgnViewer(QWidget* parent = nullptr);
    ~Map3dDisgnViewer();
    QList<Map3dObject*> m_objects;
    void paintEvent(QPaintEvent* event);

    ControlOperation operation() const;
    void setOperation(ControlOperation newOperation);
    void addBaseMap(QString fileName);


    bool showBasemap() const;
    void setShowBasemap(bool newShowBasemap);

    void saveToFile(QString fileName);
    void loadFromFile(QString fileName);
    void exportToFile(QString fileName);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
    Ui::Map3dDisgnViewer* ui;
    ControlOperation m_operation;
    QVector<QPoint> m_addPoints;
    DrawObject* m_draw;
    QPoint m_originPoint;
    QPixmap m_baseMap;
    bool m_showBasemap;
};

#endif // MAP3DDISGNVIEWER_H
