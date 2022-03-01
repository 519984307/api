#include "baseitem.h"

BaseItem::BaseItem(QObject* parent) : QObject(parent)
{
    m_selected = false;
    m_widget = nullptr;
    m_canClose = true;
    m_icon = QPixmap();
    m_iconAreaWidth = 0;
    m_iconRect = QRect(0, 0, 0, 0);
    m_number = 0;
    m_uuid = newNoDashUuid();
    m_canSelected = true;

}

QString BaseItem::caption() const
{
    return m_caption;
}

void BaseItem::setCaption(const QString& caption)
{
    m_caption = caption;
}

int BaseItem::id() const
{
    return m_id;
}

void BaseItem::setId(int id)
{
    m_id = id;
}

QRect BaseItem::rect() const
{
    return m_rect;
}

void BaseItem::setRect(const QRect& rect)
{
    m_rect = rect;
}

QRect BaseItem::closeRect() const
{
    return m_closeRect;
}

void BaseItem::setCloseRect(const QRect& closeRect)
{
    m_closeRect = closeRect;
}

bool BaseItem::selected() const
{
    return m_selected;
}

void BaseItem::setSelected(bool selected)
{
    m_selected = selected;
}

QString BaseItem::uuid() const
{
    return m_uuid;
}

void BaseItem::setUuid(const QString& uuid)
{
    m_uuid = uuid;
}

QWidget* BaseItem::widget() const
{
    return m_widget;
}

void BaseItem::setWidget(QWidget* widget)
{
    m_widget = widget;
}

bool BaseItem::canClose() const
{
    return m_canClose;
}

void BaseItem::setCanClose(bool canClose)
{
    m_canClose = canClose;
}

QPixmap BaseItem::icon() const
{
    return m_icon;
}

void BaseItem::setIcon(const QPixmap& icon)
{
    m_icon = icon;
}

int BaseItem::iconAreaWidth() const
{
    return m_iconAreaWidth;
}

void BaseItem::setIconAreaWidth(int iconAreaWidth)
{
    m_iconAreaWidth = iconAreaWidth;
}

QString BaseItem::value() const
{
    return m_value;
}

void BaseItem::setValue(const QString& value)
{
    m_value = value;
}

QPoint BaseItem::centerPoint() const
{
    return m_centerPoint;
}

void BaseItem::setCenterPoint(const QPoint& centerPoint)
{
    m_centerPoint = centerPoint;
}

int BaseItem::row() const
{
    return m_row;
}

void BaseItem::setRow(int row)
{
    m_row = row;
}

int BaseItem::col() const
{
    return m_col;
}

void BaseItem::setCol(int col)
{
    m_col = col;
}

QRect BaseItem::iconRect() const
{
    return m_iconRect;
}

void BaseItem::setIconRect(const QRect& iconRect)
{
    m_iconRect = iconRect;
}

int BaseItem::number() const
{
    return m_number;
}

void BaseItem::setNumber(int newNumber)
{
    m_number = newNumber;
}

const QColor& BaseItem::color() const
{
    return m_color;
}

void BaseItem::setColor(const QColor& newColor)
{
    m_color = newColor;
}

const QColor& BaseItem::backgroundColor() const
{
    return m_backgroundColor;
}

void BaseItem::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

int BaseItem::width() const
{
    return m_width;
}

void BaseItem::setWidth(int newWidth)
{
    m_width = newWidth;
}

const QString& BaseItem::name() const
{
    return m_name;
}

void BaseItem::setName(const QString& newName)
{
    m_name = newName;
}

const QString& BaseItem::path() const
{
    return m_path;
}

void BaseItem::setPath(const QString& newPath)
{
    m_path = newPath;
}

int BaseItem::index() const
{
    return m_index;
}

void BaseItem::setIndex(int newIndex)
{
    m_index = newIndex;
}

bool BaseItem::canSelected() const
{
    return m_canSelected;
}

void BaseItem::setCanSelected(bool newCanSelected)
{
    m_canSelected = newCanSelected;
}
