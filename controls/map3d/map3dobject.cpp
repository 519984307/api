#include "map3dobject.h"

Map3dObject::Map3dObject(QObject* parent) : QObject(parent)
{

}

QJsonObject Map3dObject::toJsonObject()
{
    QJsonObject jobj;

    QJsonArray jpoints;
    for (int i = 0; i < points.count(); i++)
    {
        QJsonObject jpoint;
        jpoint["x"] = points.at(i).x();
        jpoint["y"] = points.at(i).y();
        jpoints.append(jpoint);
    }
    jobj["points"] = jpoints;

    return jobj;

}

QJsonObject Map3dObject::toExportJsonObject()
{
    QJsonObject jobj;
    QPoint centerPt = centerPoint();

    QJsonArray jpoints;
    for (int i = 0; i < points.count(); i++)
    {
        QJsonObject jpoint;
        jpoint["x"] = points.at(i).x() - centerPt.x();
        jpoint["z"] = points.at(i).y() - centerPt.y();
        jpoints.append(jpoint);
    }
    jobj["points"] = jpoints;

    return jobj;

}

void Map3dObject::fromJsonObject(QJsonObject& jobj)
{
    QJsonArray jpoints = jobj["points"].toArray();
    for (int i = 0; i < jpoints.count(); i++)
    {
        QJsonObject jpoint = jpoints.at(i).toObject();
        points << QPoint(jpoint["x"].toInt(), jpoint["y"].toInt());
    }

}

QPoint Map3dObject::centerPoint()
{
    int l = 1000000;
    int r = -1000000;
    int t = 10000000;
    int b = -1000000;

    if (points.count() == 0)
    {
        return QPoint(0, 0);
    }

    for (int i = 0; i < points.count(); i++)
    {
        QPoint pt = points.at(i);

        if (pt.x() > r)
        {
            r = pt.x();
        }
        if (pt.x() < l)
        {
            l = pt.x();
        }
        if (pt.y() > b)
        {
            b = pt.y();
        }
        if (pt.x() < t)
        {
            t = pt.y();
        }


    }

    return QPoint((l + r) / 2, (t + b) / 2);

}
