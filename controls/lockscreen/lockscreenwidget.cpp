#include "lockscreenwidget.h"
#include "ui_lockscreenwidget.h"

LockScreenWidget::LockScreenWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LockScreenWidget)
{
    ui->setupUi(this);
    initItems();
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);

}

LockScreenWidget::~LockScreenWidget()
{
    delete ui;
}

void LockScreenWidget::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.fillRect(m_helper->clientRect(), Qt::black);
    int w = width() <= height() ? width() : height();
    int t = (height() - w) / 2;
    int l = (width() - w) / 2;
    int itemW = w / 3;
    int n = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            painter.save();
            LockScreenItem* item = m_items.at(n);
            if (m_paths.contains(item))
            {
                painter.setPen(Qt::green);
            }
            else
            {
                painter.setPen(Qt::white);
            }

            item->setRow(i);
            item->setCol(j);
            QRect itemRc(l + j * itemW + itemW * 0.25, t + i * itemW + itemW * 0.25, itemW * 0.5, itemW * 0.5);
            item->setRect(itemRc);
            painter.drawEllipse(itemRc);

            painter.setBrush(Qt::white);
            painter.setPen(Qt::white);

            if (m_paths.contains(item))
            {
                painter.setBrush(Qt::green);
                painter.setPen(Qt::green);
            }
            else
            {
                painter.setBrush(Qt::white);
                painter.setPen(Qt::white);
            }
            QRect itemCenterRc(l + j * itemW + itemW * 0.47, t + i * itemW + itemW * 0.47, itemW * 0.06, itemW * 0.06);
            painter.drawEllipse(itemCenterRc);
            item->setCenterRect(itemCenterRc);
            item->setCenterPoint(QPoint(l + j * itemW + itemW * 0.5, t + i * itemW + itemW * 0.5));
            painter.restore();
            n++;
        }
    }
    QPen pen = painter.pen();
    pen.setColor(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen);
    LockScreenItem* preItem = nullptr;
    for (int i = 0; i < m_paths.count(); i++)
    {
        LockScreenItem* item = m_paths.at(i);
        if (preItem == nullptr)
        {
            preItem = item;
        }
        else
        {
            painter.drawLine(preItem->centerPoint(), item->centerPoint());
            preItem = item;
        }
    }
    if (m_helper->mousedownFlag())
    {
        if (m_paths.count() > 0)
        {
            LockScreenItem* lastItem = m_paths.last();
            painter.drawLine(lastItem->centerPoint(), curPt);

        }
    }

    painter.end();

}

void LockScreenWidget::mousePressEvent(QMouseEvent* event)
{
    m_paths.clear();
    m_helper->startMouseDown();
}

void LockScreenWidget::mouseReleaseEvent(QMouseEvent* event)
{

    m_helper->startMouseUp();

}

void LockScreenWidget::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void LockScreenWidget::mouseMoveEvent(QMouseEvent* event)
{
    LockScreenItem* item = nullptr;
    if (m_helper->mousedownFlag())
    {
        if (m_paths.count() > 0)
        {
            item = m_paths.last();
        }
        LockScreenItem* selItem = getHoverItem();
        if ((selItem != nullptr) && (item != selItem))
        {
            m_paths << selItem;
        }
        qDebug() << m_paths.count();


    }
    update();

}

LockScreenItem* LockScreenWidget::getHoverItem()
{
    LockScreenItem* selItem = nullptr;
    QPoint pt = m_helper->cursorPos();

    for (auto item : m_items)
    {
        if (item->rect().contains(pt))
        {
            selItem = item;
            break;
        }
    }


    return selItem;

}

void LockScreenWidget::initItems()
{
    for (int i = 0; i < 9; i++)
    {
        LockScreenItem* item = new LockScreenItem(this);

        item->setValue(QString("%1").arg(i));
        m_items << item;
    }
}
