#include "selectcard.h"
#include "ui_selectcard.h"

SelectCard::SelectCard(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SelectCard)
{
    ui->setupUi(this);
    m_stackedWidget = nullptr;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setMaxLeft(16);
    m_helper->setItemsLeft(16);
    setMouseTracking(true);
    m_drawObj = new DrawObject(this);
    addMenus();
}

SelectCard::~SelectCard()
{
    delete ui;
}

SelectCardItem* SelectCard::addItem(QString caption, int id)
{
    SelectCardItem* item = new SelectCardItem();
    item->setId(id);
    item->setCaption(caption);
    items << item;
    update();
    return item;

}

SelectCardItem* SelectCard::addItem(QString caption, QString uuid, QWidget* w)
{
    SelectCardItem* item = new SelectCardItem(this);
    item->setCaption(caption);
    if (uuid != "")
    {
        item->setUuid(uuid);
    }

    item->setWidget(w);
    if (m_stackedWidget != nullptr)
    {
        m_stackedWidget->addWidget(w);
        m_stackedWidget->setCurrentWidget(w);
    }
    items << item;
    setSelected(item);
    update();

    return item;
}

SelectCardItem* SelectCard::openOrAddItem(QString caption, QString uuid, QWidget* w)
{
    SelectCardItem* item = itemByUuid(uuid);
    if (item == nullptr)
    {
        item = addItem(caption, uuid, w);
        setSelected(item);
    }
    else
    {
        setSelected(item);

    }
    update();
    QApplication::processEvents();
    makeItemShow(item);
    return item;
}

void SelectCard::setSelected(SelectCardItem* otherItem)
{
    SelectCardItem* selItem = nullptr;
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        item->setSelected(item == otherItem);
        if (item->selected())
        {
            selItem = item;

        }
    }
    update();
    if (selItem != nullptr)
    {
        if (m_stackedWidget != nullptr)
        {
            if (selItem->widget() != nullptr)
            {
                m_stackedWidget->setCurrentWidget(selItem->widget());
            }
        }
        emit itemSelect(selItem);
    }
}

bool SelectCard::hasItemId(int id)
{

    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id() == id)
        {
            return true;
        }

    }
    return false;
}

void SelectCard::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_rightMousePt = m_helper->cursorPos();
        update();
        return;
    }
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->canClose())
        {
            if (item->closeRect().contains(pt))
            {
                items.removeAt(i);
                emit itemRemove(item);
                delete  item;
                update();
                return;
            }
        }

        if (item->rect().contains(pt))
        {
            setSelected(item);
            return;
        }

    }

}

void SelectCard::updateItemText(int id, QString& s)
{
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id() == id)
        {
            item->caption() = s;

        }

    }
    update();
}

void SelectCard::deleteItemById(int id)
{
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id() == id)
        {
            deleteItem(item);
            break;

        }

    }
    update();
}

void SelectCard::deletItemByUuid(QString uuid)
{
    for (int i = items.count() - 1; i >= 0; i--)
    {
        SelectCardItem* item = items.at(i);
        if (item->uuid() == uuid)
        {
            deleteItem(item);


        }

    }
    update();
}

void SelectCard::deleteItem(SelectCardItem* item)
{
    if (item->canClose())
    {
        int i = items.indexOf(item);
        items.removeAt(i);
        emit itemRemove(item);
        delete  item;
        update();
        QApplication::processEvents();
    }

}

SelectCardItem* SelectCard::getPointInItem()
{
    QPoint pt = m_rightMousePt;
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->rect().contains(pt))
        {
            return item;
        }
    }
    return nullptr;
}

void SelectCard::onMenuItemTriggerd()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == QStringLiteral("复制标签内容"))
    {
        SelectCardItem* item = getPointInItem();
        if (item == nullptr)
        {
            return;
        }
        qApp->clipboard()->setText(item->caption());
    }
    else if (act->text() == QStringLiteral("移动到最左端"))
    {
        m_helper->setItemsLeft(m_helper->maxLeft());
    }
    else if (act->text() == QStringLiteral("标签位置反转"))
    {
        std::reverse(items.begin(), items.end());
        update();

    }
    else if (act->text() == QStringLiteral("全部关闭标签"))
    {
        for (int i = items.count() - 1; i >= 0; i--)
        {
            SelectCardItem* item = items.at(i);

            deleteItem(item);

        }
        m_helper->setItemsLeft(m_helper->maxLeft());

    }
    else if (act->text() == QStringLiteral("关闭当前标签"))
    {
        SelectCardItem* item = getPointInItem();
        if (item == nullptr)
        {
            return;
        }
        deleteItem(item);
    }
    else if (act->text() == QStringLiteral("关闭其他标签"))
    {
        SelectCardItem* selItem = getPointInItem();
        for (int i = items.count() - 1; i >= 0; i--)
        {
            SelectCardItem* item = items.at(i);
            if (item == selItem)
            {
                continue;
            }

            deleteItem(item);

        }
    }
    else if (act->text() == QStringLiteral("关闭左侧标签"))
    {
        SelectCardItem* selItem = getPointInItem();
        for (int i = items.count() - 1; i >= 0; i--)
        {
            SelectCardItem* item = items.at(i);
            if (item == selItem)
            {
                continue;
            }
            if (item->rect().left() < m_rightMousePt.x())
            {
                deleteItem(item);
            }



        }
        makeItemShow(selItem);
    }
    else if (act->text() == QStringLiteral("关闭右侧标签"))
    {
        SelectCardItem* selItem = getPointInItem();
        for (int i = items.count() - 1; i >= 0; i--)
        {
            SelectCardItem* item = items.at(i);
            if (item == selItem)
            {
                continue;
            }
            if (item->rect().left() > m_rightMousePt.x())
            {
                deleteItem(item);
            }



        }
    }
    else if (act->text() == QStringLiteral("移动标签到末尾"))
    {
        SelectCardItem* item = getPointInItem();
        if (item == nullptr)
        {
            return;
        }
        item = items.takeAt(items.indexOf(item));
        items << item;
        update();

    }
    else if (act->text() == QStringLiteral("移动标签到最前"))
    {
        SelectCardItem* item = getPointInItem();
        if (item == nullptr)
        {
            return;
        }
        item = items.takeAt(items.indexOf(item));
        items.insert(0, item);
        update();

    }
    else if (act->text() == QStringLiteral("在独立的窗口显示"))
    {
        SelectCardItem* item = getPointInItem();
        floatSelectWindow(item);


    }
    else if (act->text() == QStringLiteral("截取当前标签窗口"))
    {
        SelectCardItem* selItem = getPointInItem();
        if (selItem == nullptr)
        {
            return;
        }
        QWidget* w = selItem->widget();
        if (w == nullptr)
        {
            return;
        }
        QPixmap pix = selItem->widget()->grab();
        qApp->clipboard()->setPixmap(pix);


    }


}

void SelectCard::paintEvent(QPaintEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    int itemsWidth = 0;
    int l = m_helper->itemsLeft();

    for (int i = 0; i < items.count(); i++)
    {
        if (i == 0)
        {
            painter.setPen(QColor(197, 197, 197));
            painter.drawLine(0, height(), l, height());
        }
        SelectCardItem* item = items.at(i);
        item->setIconAreaWidth(item->icon().isNull() ? 0 : height() + 12);
        QFontMetrics fm = painter.fontMetrics();
        int w = item->iconAreaWidth() + fm.width(item->caption());
        QRect itemRc = QRect(l, 0, w + 32, height());
        item->setRect(itemRc);
        item->setCloseRect(QRect(itemRc.right() - 20, (height() - 16) / 2, 16, 16));
        if (item->selected())
        {

            painter.fillRect(item->rect(), QBrush(QColor(255, 255, 255)));
        }
        else
        {
            if (item->rect().contains(pt))
            {
                painter.fillRect(item->rect(), QBrush(QColor(243, 243, 243)));
            }
            else
            {
                painter.fillRect(item->rect(), QBrush(QColor(237, 237, 237)));
            }

        }
        if (item->canClose())
        {
            QColor closeColor = item->closeRect().contains(pt) ? Qt::red : Qt::black;
            m_drawObj->drawCloseButton(painter, item->closeRect(), closeColor);
        }


        //绘制线条
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l, height());
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l + w + 32, 0);

        if (!item->icon().isNull())
        {
            QRect iconRc(l + 6, 0, height(), height());
            painter.drawPixmap(iconRc, item->icon(), item->icon().rect());
            item->setIconRect(iconRc);
        }

        QRect rc;

        rc = QRect(l + item->iconAreaWidth() + (item->icon().isNull() ? 6 : 0), 0, w - item->iconAreaWidth(), height());

        painter.setPen(QColor(0, 0, 0));
        painter.drawText(rc, Qt::AlignCenter, item->caption());
        if (item->selected() == false)
        {
            painter.setPen(QColor(197, 197, 197));
            painter.drawLine(l, height(), l + w + 32, height());
        }
        l = l + w + 32;
        itemsWidth = itemsWidth + w + 32;
    }
    if (items.count() > 0)
    {
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l, height());
        painter.drawLine(l, height(), width(), height());
    }

    m_helper->setItemsWidth(itemsWidth);
    if (items.count() > 0)
    {
        m_helper->setLastRect(items.last()->rect());
    }
    painter.end();

}

void SelectCard::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void SelectCard::wheelEvent(QWheelEvent* event)
{
    int x = event->angleDelta().y();
    int itemLeft = m_helper->itemsLeft() + x;
    if ((m_helper->itemsWidth() < width()) || (itemLeft > m_helper->maxLeft()))
    {
        itemLeft = m_helper->maxLeft();
    }
    if ((x < 0) && (m_helper->itemsWidth() > width()) && (m_helper->lastRect().right() < width()))
    {
        itemLeft -= x;
    }

    m_helper->setItemsLeft(itemLeft);

}

void SelectCard::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    SelectCardItem* selItem = nullptr;
    for (SelectCardItem* item : items)
    {
        if (item->iconRect().contains(pt))
        {
            selItem = item;
            break;
        }
    }
    if (selItem != nullptr)
    {
        floatSelectWindow(selItem);
    }

}

QStackedWidget* SelectCard::getStackedWidget() const
{
    return m_stackedWidget;
}

void SelectCard::setStackedWidget(QStackedWidget* stackedWidget)
{
    m_stackedWidget = stackedWidget;
}

void SelectCard::floatSelectWindow(SelectCardItem* item)
{
    if (item == nullptr)
    {
        return;
    }
    if (!item->canClose())
    {
        return;
    }
    items.removeOne(item);
    m_stackedWidget->removeWidget(item->widget());
    NewSelectCardWidgetWindow* window = new NewSelectCardWidgetWindow();
    window->setWindowTitle(item->caption());
    window->setWindowIcon(item->icon());
    window->setCentralWidget(item->widget());
    QWidget* w = item->widget();
    window->setWidget(w);
    window->show();




    delete item;
    update();
    QApplication::processEvents();
}

SelectCardItem* SelectCard::itemByUuid(QString uuid)
{
    for (SelectCardItem* item : items)
    {
        if (item->uuid() == uuid)
        {
            return item;
        }
    }
    return nullptr;
}

void SelectCard::makeItemShow(SelectCardItem* item)
{
    if (m_helper->itemsWidth() < width())
    {
        m_helper->setItemsLeft(m_helper->maxLeft());
        return;
    }
    if (item == nullptr)
    {

        m_helper->setItemsLeft(m_helper->maxLeft());

    }
    else
    {
        QRect rc = item->rect();
        int l = rc.left();
        int r = rc.right();
        if (r > width())
        {
            int w = r - width();
            int s = m_helper->itemsLeft();
            s = s - w - 16;
            m_helper->setItemsLeft(s);
        }
        else if (r < 0)
        {
            int w = -r + rc.width();
            int s = m_helper->itemsLeft();
            s = s + w + 16;
            m_helper->setItemsLeft(s);
        }
        else
        {
            update();
        }
    }


}

void SelectCard::addMenus()
{
    QStringList menuNames;
    menuNames << QStringLiteral("复制标签内容") << "-"
              << QStringLiteral("移动到最左端")
              << QStringLiteral("移动标签到最前")
              << QStringLiteral("移动标签到末尾")
              << QStringLiteral("标签位置反转")
              << QStringLiteral("-")
              << QStringLiteral("关闭当前标签")
              << QStringLiteral("关闭其他标签")
              << QStringLiteral("关闭左侧标签")
              << QStringLiteral("关闭右侧标签")
              << QStringLiteral("全部关闭标签")
              << QStringLiteral("-")
              << QStringLiteral("截取当前标签窗口")
              << QStringLiteral("-")
              << QStringLiteral("在独立的窗口显示");
    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction();
        if (menuNames[i] == "-")
        {
            act->setSeparator(true);
        }
        else
        {
            act->setText(menuNames[i]);
            connect(act, &QAction::triggered, this, &SelectCard::onMenuItemTriggerd);
        }

        addAction(act);
    }

}
