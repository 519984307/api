#include "buttonlist.h"
#include "ui_buttonlist.h"

ButtonList::ButtonList(QWidget* parent) :
    ParentButtonList(parent),
    ui(new Ui::ButtonList)
{
    ui->setupUi(this);

}

ButtonList::~ButtonList()
{
    delete ui;
}





void ButtonList::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter;
    QPoint pt = m_helper->cursorPos();
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    int l = m_helper->itemsLeft();
    int m = 0;
    for (int i = 0; i < m_items.count(); i++)
    {
        ButtonListItem* item = m_items.at(i);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width(item->caption()) + 32;
        QRect rc(l, (height() - 24) / 2, w, 24);
        item->setRect(rc);
        QPen pen = painter.pen();

        pen.setWidthF(.5);
        if ((rc.contains(pt)) && (m_helper->mousedownFlag() == false))
        {

            pen.setColor(QColor(0, 120, 212));
            painter.setBrush(QColor(224, 238, 249));

        }
        else
        {
            pen.setColor(QColor(208, 208, 208));

            painter.setBrush(QColor(253, 253, 253));

        }
        painter.setPen(pen);



        painter.drawRoundedRect(rc, 3, 3);
        painter.setPen(Qt::black);
        painter.drawText(rc, Qt::AlignCenter, item->caption());

        l += w + 8;
        m += w + 8;
    }
    painter.end();
    m_helper->setItemsWidth(m);
    if (m_items.count() > 0)
    {
        m_helper->setLastRect(m_items.last()->rect());
    }

}

void ButtonList::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    update();

}

void ButtonList::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    m_helper->startMouseDown();
    update();
}

void ButtonList::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    m_helper->startMouseUp();
    update();
    QPoint pt = m_helper->cursorPos();
    for (ButtonListItem* item : qAsConst(m_items))
    {

        if (item->rect().contains(pt))
        {
            emit clickButton(item);
        }


    }

}

void ButtonList::wheelEvent(QWheelEvent* event)
{
    QRect rc = m_helper->clientRect();
    int x = event->angleDelta().y();
    int l = m_helper->itemsLeft();
    l += x;
    if ((l > m_helper->maxLeft()) || (m_helper->itemsWidth() < width()))
    {
        l = m_helper->maxLeft();
    }
    else if ((x < 0) && (rc.contains(m_helper->lastRect())))
    {
        l = width() - m_helper->itemsWidth();

    }
    m_helper->setItemsLeft(l);

}
