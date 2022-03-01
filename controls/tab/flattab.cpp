#include "flattab.h"
#include "ui_flattab.h"

FlatTab::FlatTab(QWidget* parent) :
    ParentTab(parent),
    ui(new Ui::FlatTab)
{
    ui->setupUi(this);

}

FlatTab::~FlatTab()
{
    clearItems();
    delete ui;
}

void FlatTab::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(m_helper->clientRect(), QBrush(QColor(17, 33, 79)));
    painter.setPen(Qt::white);
    int l = 0;
    for (int i = 0; i < m_items.count(); i++)
    {
        TabItem* item = m_items.at(i);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.boundingRect(item->caption()).width() + 32;
        QRect rc(l, 0, w, height());
        if (i == m_activeIndex)
        {
            painter.fillRect(rc, QBrush(QColor(172, 0, 0)));
        }
        painter.drawText(rc, Qt::AlignCenter, item->caption());
        item->setRect(rc);
        l += w;
    }
    painter.end();

}

void FlatTab::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        TabItem* item = m_items.at(i);
        if (item->rect().contains(curPt))
        {
            setActiveIndex(i);
            emit tabItemClick(item);
            break;
        }
    }

    update();

}
