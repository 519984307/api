#ifndef MAP3DOBJECT_H
#define MAP3DOBJECT_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>

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
signals:

};

#endif // MAP3DOBJECT_H
