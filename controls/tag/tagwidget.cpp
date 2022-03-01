#include "tagwidget.h"
#include "ui_tagwidget.h"

TagWidget::TagWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::TagWidget)
{
    ui->setupUi(this);
    m_itemsLeft = 0;
    m_mousedownFlag = false;
    m_currentSelectedIndex = -1;
}

TagWidget::~TagWidget()
{
    delete ui;
}

void TagWidget::addTag(int id, QString caption)
{
    TagWidgetItem* item = new TagWidgetItem(this);
    item->setId(id);
    item->setCaption(caption);
    item->setIndex(items.count());
    items << item;

    update();


}

void TagWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    int l = m_itemsLeft;
    int m = 0;
    for (int i = 0; i < items.count(); i++)
    {
        TagWidgetItem* item = items.at(i);
        QFont font = painter.font();
        font.setFamily("宋体");
        font.setPointSize(item->selected() ? 13 : 11);
        font.setBold(item->selected());
        painter.setFont(font);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.boundingRect(item->caption()).width() + 24;

        item->rect = QRect(l, 0, w, height());
        painter.drawText(item->rect, Qt::AlignCenter, item->caption());

        l += w;
        m += w;
    }
    m_itemsWidth = m;

    painter.end();

}

void TagWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    m_mousedownPoint = pt;
    m_mouseclickPoint = pt;
    m_mousedownFlag = true;
    update();

}

void TagWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    if (m_mousedownFlag)
    {
        m_itemsLeft += pt.x() - m_mousedownPoint.x();
        if (m_itemsWidth < width())
        {
            m_itemsLeft = 0;
        }
        else if (m_itemsLeft > 0)
        {
            m_itemsLeft = 0;
        }
        else if (m_itemsLeft + (m_itemsWidth - width() + 24) < 0)
        {
            m_itemsLeft = -(m_itemsWidth - width() + 24);
        }

        qDebug() << m_itemsLeft;
        m_mousedownPoint = pt;
    }
    update();
}

void TagWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_mousedownFlag = false;

    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);

    m_mousedownFlag = false;
    if ((m_mouseclickPoint.x() == pt.x()) && (m_mouseclickPoint.y() == pt.y()))
    {
        for (int i = 0; i < items.count(); i++)
        {
            TagWidgetItem* item = items.at(i);
            if (item->rect.contains(pt))
            {
                item->setSelected(true);
                m_currentSelectedIndex = item->index();
                emit onItemSelected(item);
            }
            else
            {
                item->setSelected(false);
            }
        }
    }


    update();
}

int TagWidget::currentSelectedIndex() const
{
    return m_currentSelectedIndex;
}




int TagWidget::itemsLeft() const
{
    return m_itemsLeft;
}

void TagWidget::setItemsLeft(int itemsLeft)
{
    m_itemsLeft = itemsLeft;
}

void TagWidget::setSelectedByIndex(int index)
{
    for (int i = 0; i < items.count(); i++)
    {
        TagWidgetItem* item = items.at(i);
        if (item->index() == index)
        {
            m_currentSelectedIndex = index;
            item->setSelected(true);
            emit onItemSelected(item);
        }
        else
        {
            item->setSelected(false);
        }

    }
    update();
}

void TagWidget::clearItems()
{
    qDeleteAll(items);
    items.clear();
}
