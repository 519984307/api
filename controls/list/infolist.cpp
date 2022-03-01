#include "infolist.h"
#include "ui_infolist.h"

InfoList::InfoList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::InfoList)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    setMouseTracking(true);
}

InfoList::~InfoList()
{
    delete ui;
}

InfoListItem* InfoList::addItem(QString caption)
{
    InfoListItem* item = new InfoListItem(this);
    item->setCaption(caption);
    m_items << item;
    update();
    return item;
}

InfoListItem* InfoList::findItemByUuid(const QString& uuid)
{
    for (int i = 0; i < m_items.count(); i++)
    {
        InfoListItem* item = m_items.at(i);
        if (item->uuid() == uuid)
            return item;
    }
    return nullptr;
}

void InfoList::clearItems()
{
    qDeleteAll(m_items);
    m_items.clear();
    m_helper->setItemsTop(16);
    update();
}

void InfoList::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPoint pt = m_helper->cursorPos();
    QPainter painter;
    QRect clientRc = m_helper->clientRect();
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.fillRect(clientRc, QBrush(Qt::white));
    int t = m_helper->itemsTop();
    for (int i = 0; i < m_items.count(); i++)
    {
        InfoListItem* item = m_items.at(i);

        QRect itemRc(16, t, width() - 32, 32);
        item->setRect(itemRc);
        if (itemRc.contains(pt))
        {
            painter.fillRect(itemRc, QColor(242, 242, 242));
        }
        else
        {
            painter.fillRect(itemRc, Qt::NoBrush);
        }

        QPen pen = painter.pen();
        pen.setWidth(2);
        pen.setColor(item->color());
        painter.setPen(pen);
        painter.drawEllipse(44, t + 12, 8, 8);


        QRect textRc(64, t, width() - 80, 32);

        pen = painter.pen();
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter.setPen(pen);

        QFont font = painter.font();
        font.setPixelSize(16);

        painter.setFont(font);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, item->caption());

        t += 40;
    }
    painter.end();
}

void InfoList::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    m_helper->moveTop(y);


}

void InfoList::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (m_helper->mousedownFlag() == true)
    {
        QPoint pt = m_helper->cursorPos();

        int y = pt.y() - m_helper->mouseMovePoint().y();
        m_helper->moveTop(y);
        m_helper->setMouseMovePoint(pt);

    }

    update();
}

void InfoList::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    m_helper->startMouseDown();
}

void InfoList::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    QPoint curPt = m_helper->cursorPos();
    m_helper->startMouseUp();
    if (m_helper->isClicked())
    {
        for (int i = 0; i < m_items.count(); i++)
        {
            InfoListItem* item = m_items.at(i);
            if (item->rect().contains(curPt))
            {
                emit clickInfoListItem(item);
                break;
            }
        }

    }
    else
    {
        qDebug() << "drag1";
    }
}

void InfoList::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event)

}
