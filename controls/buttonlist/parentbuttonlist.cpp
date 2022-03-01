#include "parentbuttonlist.h"

ParentButtonList::ParentButtonList(QWidget* parent) : QWidget(parent)
{

    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setMaxLeft(16);
    m_helper->setItemsLeft(16);
    setMouseTracking(true);
    m_activeIndex = 0;
    m_maxCaptionLen = 0;
}

const QList<ButtonListItem*>& ParentButtonList::items() const
{
    return m_items;
}

void ParentButtonList::setItems(const QList<ButtonListItem*>& newItems)
{
    m_items = newItems;
}
void ParentButtonList::addButtons(QStringList& buttonNames)
{
    for (int i = 0; i < buttonNames.count(); i++)
    {
        ButtonListItem* item = new ButtonListItem(this);
        item->setCaption(buttonNames.at(i));
        int n = buttonNames.at(i).length();
        if (n > m_maxCaptionLen)
        {
            m_maxCaptionLen = n;
        }
        item->setIndex(m_items.count());
        m_items << item;
    }
    update();
}

int ParentButtonList::activeIndex() const
{
    return m_activeIndex;
}

void ParentButtonList::setActiveIndex(int newActiveIndex)
{
    m_activeIndex = newActiveIndex;
}

int ParentButtonList::maxCaptionLen() const
{
    return m_maxCaptionLen;
}

void ParentButtonList::setMaxCaptionLen(int newMaxCaptionLen)
{
    m_maxCaptionLen = newMaxCaptionLen;
}
