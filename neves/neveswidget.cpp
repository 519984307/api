#include "neveswidget.h"
#include "ui_neveswidget.h"

NevesWidget::NevesWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::NevesWidget)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_selectItem = nullptr;
    m_baseWidth = 300;
    for (int i = 0; i < 7; i++)
    {
        NevesWidgetItem* item = new NevesWidgetItem(this);
        item->setShape(NevesWidgetItemShape(i));
        item->setIndex(i);
        items << item;

    }
}

NevesWidget::~NevesWidget()
{
    delete ui;
}

void NevesWidget::paintEvent(QPaintEvent* event)
{
    QRect clientRect = QRect(0, 0, width(), height());
    QPainter painter;
    painter.begin(this);
    painter.fillRect(clientRect, QBrush(Qt::white));
    for (int i = 0; i < 7; i++)
    {
        items[i]->drawShape(painter);
    }
    painter.end();

}

void NevesWidget::mousePressEvent(QMouseEvent* event)
{

    m_helper->setMousedownFlag(true);
    QPoint pt = m_helper->cursorPos();
    m_helper->setMousedownPoint(pt);
    m_selectItem = nullptr;
    int index = -1;
    for (int i = 0; i < 7; i++)
    {
        if (items[i]->polygon.containsPoint(pt, Qt::WindingFill))
        {
            m_selectItem = items[i];
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        items.removeOne(m_selectItem);
        items << m_selectItem;
    }
    update();

}

void NevesWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        if (m_selectItem != nullptr)
        {
            QPoint pt = m_helper->cursorPos();
            int x = pt.x() - m_helper->mousedownPoint().x();
            int y = pt.y() - m_helper->mousedownPoint().y();
            m_selectItem->setCenter(QPoint(
                                        m_selectItem->center().x() + x,
                                        m_selectItem->center().y() + y));
            m_helper->setMousedownPoint(pt);
        }

        update();
    }

}

NevesWidgetItem* NevesWidget::selectItem() const
{
    return m_selectItem;
}

void NevesWidget::setSelectItem(NevesWidgetItem* newSelectItem)
{
    m_selectItem = newSelectItem;
}

QPoint NevesWidget::center() const
{
    return m_center;
}

void NevesWidget::setCenter(QPoint newCenter)
{
    m_center = newCenter;
}

void NevesWidget::reset()
{

    sort(items.begin(), items.end(), [](NevesWidgetItem * item1, NevesWidgetItem * item2)
    {
        return item1->index() < item2->index();
    }
        );

    items[0]->setCenter(QPoint(m_center.x(), m_center.y() + m_baseWidth / 4));
    items[0]->setBaseWidth(m_baseWidth / 4);
    items[0]->setColor(QColor(220, 43, 12));

    items[1]->setCenter(QPoint(m_center.x() - m_baseWidth / 4, m_center.y()));
    items[1]->setBaseWidth(m_baseWidth / 4);
    items[1]->setColor(QColor(34, 158, 22));

    items[2]->setCenter(QPoint(m_center.x() + 3 * (m_baseWidth / 8), m_center.y() + m_baseWidth / 4));
    items[2]->setBaseWidth(m_baseWidth / 8);
    items[2]->setColor(QColor(233, 90, 118));

    items[3]->setCenter(QPoint(m_center.x() + 3 * (m_baseWidth / 8), m_center.y() - 3 * (m_baseWidth / 8)));
    items[3]->setBaseWidth(m_baseWidth / 8);
    items[3]->setColor(QColor(123, 201, 19));

    items[4]->setCenter(QPoint(m_center.x(), m_center.y() - (m_baseWidth / 8)));
    items[4]->setBaseWidth(m_baseWidth / 8);
    items[4]->setColor(QColor(22, 59, 198));

    items[5]->setCenter(QPoint(m_center.x() - m_baseWidth / 8, m_center.y() - 3 * (m_baseWidth / 8)));
    items[5]->setBaseWidth(m_baseWidth / 8);
    items[5]->setColor(QColor(23, 212, 1));

    items[6]->setCenter(QPoint(m_center.x() + m_baseWidth / 4, m_center.y()));
    items[6]->setBaseWidth(m_baseWidth / 4);
    items[6]->setColor(Qt::darkYellow);

    update();
}

int NevesWidget::baseWidth() const
{
    return m_baseWidth;
}

void NevesWidget::setBaseWidth(int newBaseWidth)
{
    m_baseWidth = newBaseWidth;
}
