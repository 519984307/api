#include "parenttab.h"

ParentTab::ParentTab(QWidget* parent) : QWidget(parent)
{
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);

}

TabItem* ParentTab::addItem(QString caption)
{
    TabItem* item = new TabItem(this);
    item->setCaption(caption);
    item->setIndex(m_items.count());
    m_items << item;
    update();
    return item;

}

int ParentTab::activeIndex() const
{
    return m_activeIndex;
}

void ParentTab::setActiveIndex(int activeIndex)
{
    m_activeIndex = activeIndex;
    TabItem* selItem = nullptr;
    for (int i = 0; i < m_items.count(); i++)
    {
        TabItem* item = m_items.at(i);
        item->setIsActive(item->index() == m_activeIndex);
        if (item->isActive())
        {
            selItem = item;
        }
    }
    if (selItem != nullptr)
    {
        emit tabItemClick(selItem);
    }
    update();
}

int ParentTab::defaultButtonWidth() const
{
    return m_defaultButtonWidth;
}

void ParentTab::setDefaultButtonWidth(int defaultButtonWidth)
{
    m_defaultButtonWidth = defaultButtonWidth;
}

QList<QAction*>& ParentTab::tabItemActions(QString caption)
{
    static QList<QAction*> ret;
    for (TabItem* item : m_items)
    {
        if (item->caption() == caption)
        {
            return item->actions;
        }
    }
    return ret;
}

void ParentTab::clearItems()
{
    qDeleteAll(m_items);
    m_items.clear();
    update();
}

