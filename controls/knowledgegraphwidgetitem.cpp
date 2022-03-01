#include "knowledgegraphwidgetitem.h"

KnowledgeGraphWidgetItem::KnowledgeGraphWidgetItem(QObject* parent)
    : QObject(parent)
{
    static QColor colors[12] = { QColor(229, 77, 66), QColor(243, 123, 29), QColor(251, 189, 8),
        QColor(141, 198, 63), QColor(57, 181, 74), QColor(28, 187, 180), QColor(0, 129, 255),
        QColor(103, 57, 182), QColor(156, 38, 176), QColor(224, 57, 151), QColor(165, 103, 63), QColor(135, 153, 163) };
    int i = qrand() % 12;
    m_color = colors[i];
    i = qrand() % 12;
    m_childColor = colors[i];
    m_parentItem = nullptr;
}

int KnowledgeGraphWidgetItem::id() const
{
    return m_id;
}

void KnowledgeGraphWidgetItem::setId(int id)
{
    m_id = id;
}

QString KnowledgeGraphWidgetItem::name() const
{
    return m_name;
}

void KnowledgeGraphWidgetItem::setName(const QString& name)
{
    m_name = name;
}

QString KnowledgeGraphWidgetItem::value() const
{
    return m_value;
}

void KnowledgeGraphWidgetItem::setValue(const QString& value)
{
    m_value = value;
}

KnowledgeGraphWidgetItem* KnowledgeGraphWidgetItem::parentItem() const
{
    return m_parentItem;
}

void KnowledgeGraphWidgetItem::setParentItem(KnowledgeGraphWidgetItem* parentItem)
{
    m_parentItem = parentItem;
}

int KnowledgeGraphWidgetItem::childsNum() const
{
    return m_childsNum;
}

void KnowledgeGraphWidgetItem::setChildsNum(int childsNum)
{
    m_childsNum = childsNum;
}

QColor KnowledgeGraphWidgetItem::color() const
{
    return m_color;
}

void KnowledgeGraphWidgetItem::setColor(const QColor& color)
{
    m_color = color;
}

QColor KnowledgeGraphWidgetItem::childColor() const
{
    return m_childColor;
}

void KnowledgeGraphWidgetItem::setChildColor(const QColor& childColor)
{
    m_childColor = childColor;
}

int KnowledgeGraphWidgetItem::index() const
{
    return m_index;
}

void KnowledgeGraphWidgetItem::setIndex(int index)
{
    m_index = index;
}

int KnowledgeGraphWidgetItem::startAngle() const
{
    return m_startAngle;
}

void KnowledgeGraphWidgetItem::setStartAngle(int startAngle)
{
    m_startAngle = startAngle;
}

bool KnowledgeGraphWidgetItem::hasCheck() const
{
    return m_hasCheck;
}

void KnowledgeGraphWidgetItem::setHasCheck(bool hasCheck)
{
    m_hasCheck = hasCheck;
}
