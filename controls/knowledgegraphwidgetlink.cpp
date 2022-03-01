#include "knowledgegraphwidgetlink.h"

KnowledgeGraphWidgetLink::KnowledgeGraphWidgetLink(QObject* parent)
    : QObject(parent)
{
    m_startItem = nullptr;
    m_endItem = nullptr;
}

QString KnowledgeGraphWidgetLink::startName() const
{
    return m_startName;
}

void KnowledgeGraphWidgetLink::setStartName(const QString& startName)
{
    m_startName = startName;
}

QString KnowledgeGraphWidgetLink::endName() const
{
    return m_endName;
}

void KnowledgeGraphWidgetLink::setEndName(const QString& endName)
{
    m_endName = endName;
}

void KnowledgeGraphWidgetLink::drawLine(QPainter& painter, QList<KnowledgeGraphWidgetItem*>& items)
{
    if (m_startItem == nullptr) {
        m_startItem = getItem(items, m_startName);
    }
    if (m_endItem == nullptr) {
        m_endItem = getItem(items, m_endName);
    }
    painter.setPen(QColor(197, 197, 197));
    painter.drawLine(m_startItem->center, m_endItem->center);
    painter.setPen(Qt::black);
}

KnowledgeGraphWidgetItem* KnowledgeGraphWidgetLink::getItem(QList<KnowledgeGraphWidgetItem*>& items, QString value)
{
    for (int i = 0; i < items.count(); i++) {
        KnowledgeGraphWidgetItem* item = items.at(i);
        if (item->value() == value) {
            return item;
        }
    }
    return nullptr;
}
