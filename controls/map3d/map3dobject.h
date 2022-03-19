#ifndef MAP3DOBJECT_H
#define MAP3DOBJECT_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>
#include <QPolygon>
#include "map3dobjectpropertydialog.h"
#include "../api/color/colorutils.h"
const QString OBJ_OBJECT = "object";
const QString OBJ_PLANE = "plane";

class Map3dObjectPropertyDialog;
class Map3dObject : public QObject
{
    Q_OBJECT
public:
    explicit Map3dObject(QObject* parent = nullptr);
    QVector<QPoint> points;
    QJsonObject toJsonObject();
    QJsonObject toExportJsonObject();
    void fromJsonObject(QJsonObject& jobj);
    QPoint centerPoint();

    QPoint exportPosition() const;
    void setExportPosition(QPoint newExportPosition);
    QPolygon polygon();


    bool selected() const;
    void setSelected(bool newSelected);

    const QColor& color() const;
    void setColor(const QColor& newColor);

    const QString& name() const;
    void setName(const QString& newName);

    double height() const;
    void setHeight(double newHeight);

    const QString& objectType() const;
    void setObjectType(const QString& newObjectType);
    void moveBy(int x, int y);

    int iconIndex() const;
    void setIconIndex(int newIconIndex);

signals:
private:
    QPoint m_exportPosition;
    bool m_selected;
    QColor m_color;
    QString m_name;
    double m_height;
    QString m_objectType;
    int m_iconIndex;

};

#endif // MAP3DOBJECT_H
