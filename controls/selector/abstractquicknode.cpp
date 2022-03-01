#include "abstractquicknode.h"

AbstractQuickNode::AbstractQuickNode(QObject* parent) : QObject(parent)
{

}

QRect AbstractQuickNode::rect() const
{
    return m_rect;
}

void AbstractQuickNode::setRect(const QRect& rect)
{
    m_rect = rect;
}

QString AbstractQuickNode::caption() const
{
    return m_caption;
}

void AbstractQuickNode::setCaption(const QString& caption)
{
    m_caption = caption;
}

int AbstractQuickNode::startPos() const
{
    return m_startPos;
}

void AbstractQuickNode::setStartPos(int startPos)
{
    m_startPos = startPos;
}
