#include "icontoolbar.h"
#include "ui_icontoolbar.h"

IconToolBar::IconToolBar(QWidget* parent) :
    BaseWidget(parent),
    ui(new Ui::IconToolBar)
{
    ui->setupUi(this);
    m_backgroundColor = QColor(40, 129, 169);
    m_backgroundImage = QPixmap();
    setMouseTracking(true);
}

IconToolBar::~IconToolBar()
{
    delete ui;
}

void IconToolBar::addItem(IconToolbarItem* item)
{
    item->setIndex(m_items.count());
    m_items << item;
    update();
}

const QList<IconToolbarItem*>& IconToolBar::items() const
{
    return m_items;
}

void IconToolBar::setItems(const QList<IconToolbarItem*>& newItems)
{
    m_items = newItems;
}

void IconToolBar::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    if (m_backgroundImage.isNull())
    {
        painter.fillRect(clientRc, QBrush(m_backgroundColor));
    }
    else
    {
        painter.drawPixmap(clientRc, m_backgroundImage, m_backgroundImage.rect());
    }



    int l = 16;
    for (int i = 0; i < m_items.count(); i++)
    {
        IconToolbarItem* item = m_items.at(i);
        QRect rc(l, 8, 96, 96);
        if (item->selected())
        {
            painter.setPen(QColor(255, 255, 255, 80));
            painter.setBrush(QColor(255, 255, 255, 80));
            painter.drawRoundRect(rc);
        }
        else if (rc.contains(curPt))
        {
            painter.setPen(QColor(255, 255, 255, 0));
            painter.setBrush(QColor(255, 255, 255, 80));
            painter.drawRoundRect(rc);
        }

        QRect iconRc(l + 24, 16, 48, 48);

        painter.drawPixmap(iconRc, item->icon(), item->icon().rect());

        QRect textRc(l, 72, 96, 24);
        QFont font = painter.font();
        font.setPixelSize(14);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(textRc, Qt::AlignCenter, item->caption());
        item->setRect(rc);
        l += 96 + 16;
    }

    painter.end();

}

void IconToolBar::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        IconToolbarItem* item = m_items.at(i);
        if (item->rect().contains(curPt))
        {
            selectItem(item);
            emit clickItem(item);
        }
    }

    update();

}

void IconToolBar::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

const QPixmap& IconToolBar::backgroundImage() const
{
    return m_backgroundImage;
}

void IconToolBar::setBackgroundImage(const QPixmap& newBackgroundImage)
{
    m_backgroundImage = newBackgroundImage;
    update();
}

void IconToolBar::selectItem(IconToolbarItem* selItem)
{
    if (selItem->canSelected() == false)
    {
        return;
    }
    for (int i = 0; i < m_items.count(); i++)
    {
        IconToolbarItem* item = m_items.at(i);
        if (item->canSelected())
        {
            item->setSelected(item == selItem);
        }
    }
}



const QColor& IconToolBar::backgroundColor() const
{
    return m_backgroundColor;
}

void IconToolBar::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
    update();
}
