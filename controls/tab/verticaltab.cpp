#include "verticaltab.h"
#include "ui_verticaltab.h"

VerticalTab::VerticalTab(QWidget* parent) :
    ParentTab(parent),
    ui(new Ui::VerticalTab)
{
    ui->setupUi(this);
    m_defaultButtonWidth = 32;
    setMouseTracking(true);
}

VerticalTab::~VerticalTab()
{
    delete ui;
}

void VerticalTab::paintEvent(QPaintEvent* event)
{
    QRect clientRc = m_helper->clientRect();
    QPoint pt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);

    int t = 16;
    int l = (width() - m_defaultButtonWidth) / 2;
    for (int i = 0; i < m_items.count(); i++)
    {
        TabItem* item = m_items.at(i);
        QRect itemRc = QRect(l, t, m_defaultButtonWidth, item->caption().count() * 18 + 32);
        item->setRect(itemRc);
        painter.save();
        if (item->isActive())
        {
            painter.setBrush(Qt::white);
            painter.setPen(Qt::lightGray);
            painter.drawRect(itemRc);
            painter.setPen(Qt::black);

        }


        else if (itemRc.contains(pt))
        {
            painter.setBrush(QColor(241, 242, 244));
            painter.setPen(Qt::lightGray);
            painter.drawRect(itemRc);
            painter.setPen(Qt::black);

        }


        int n = t + 16;
        for (int j = 0; j < item->caption().count(); j++)
        {
            QRect textRc(l, n, m_defaultButtonWidth, 18);
            painter.drawText(textRc, Qt::AlignCenter, item->caption().at(j));
            n += 18;
        }
        painter.restore();
        t += item->caption().count() * 18 + 38;
    }
    painter.end();
}

void VerticalTab::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void VerticalTab::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    TabItem* selItem = nullptr;
    for (int i = 0; i < m_items.count(); i++)
    {
        TabItem* item = m_items.at(i);
        if (item->rect().contains(pt))
        {
            selItem = item;
            item->setIsActive(true);
        }
        else
        {
            item->setIsActive(false);
        }
    }
    if (selItem != nullptr)
    {
        emit tabItemClick(selItem);
        if (event->button() == Qt::RightButton)
        {
            if (selItem->actions.count() == 0)
            {
                return;
            }
            QPoint menuPt = QPoint(selItem->rect().right() + 2, pt.y());
            menuPt = this->mapToGlobal(menuPt);

            QMenu* menu = new QMenu();
            menu->addActions(selItem->actions);
            menu->exec(menuPt);
            delete  menu;

        }
    }

    update();
}
