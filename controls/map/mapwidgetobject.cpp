#include "mapwidgetobject.h"
QMap<int, QPixmap> MapWidgetObject::icons;
MapWidgetObject::MapWidgetObject(QObject* parent) : QObject(parent)
{
    m_iconIndex = 0;

}

int MapWidgetObject::width() const
{
    return m_width;
}

void MapWidgetObject::setWidth(int width)
{
    m_width = width;
}

int MapWidgetObject::height() const
{
    return m_height;
}

void MapWidgetObject::setHeight(int height)
{
    m_height = height;
}

int MapWidgetObject::left() const
{
    return m_left;
}

void MapWidgetObject::setLeft(int left)
{
    m_left = left;
}

int MapWidgetObject::top() const
{
    return m_top;
}

void MapWidgetObject::setTop(int top)
{
    m_top = top;
}

QString MapWidgetObject::devtype() const
{
    return m_devtype;
}

void MapWidgetObject::setDevtype(const QString& devtype)
{
    m_devtype = devtype;
}

QPixmap MapWidgetObject::icon() const
{
    return m_icon;
}

void MapWidgetObject::setIcon(const QPixmap& icon)
{
    m_icon = icon;
}

QPoint MapWidgetObject::centerPoint() const
{
    return m_centerPoint;
}

void MapWidgetObject::setCenterPoint(const QPoint& centerPoint)
{
    m_centerPoint = centerPoint;
}

QRect MapWidgetObject::viewRect() const
{
    return m_viewRect;
}

void MapWidgetObject::setViewRect(const QRect& viewRect)
{
    m_viewRect = viewRect;
}

int MapWidgetObject::id() const
{
    return m_id;
}

void MapWidgetObject::setId(int id)
{
    m_id = id;
}

QString MapWidgetObject::devId() const
{
    return m_devId;
}

void MapWidgetObject::setDevId(const QString& devId)
{
    m_devId = devId;
}

QString MapWidgetObject::name() const
{
    return m_name;
}

void MapWidgetObject::setName(const QString& name)
{
    m_name = name;
}

QString MapWidgetObject::devState() const
{
    return m_devState;
}

void MapWidgetObject::setDevState(const QString& devState)
{
    m_devState = devState;
}

int MapWidgetObject::iconIndex() const
{
    return m_iconIndex;
}

void MapWidgetObject::setIconIndex(int iconIndex)
{
    m_iconIndex = iconIndex;
}


