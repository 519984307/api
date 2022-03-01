#include "quickselector.h"
#include "ui_quickselector.h"

QuickSelector::QuickSelector(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::QuickSelector)
{
    ui->setupUi(this);
    m_selectButton = nullptr;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);
    m_showButton = true;
    init();
}

QuickSelector::~QuickSelector()
{
    delete ui;
}

void QuickSelector::paintEvent(QPaintEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    QPainter painter;
    QRect rc;
    painter.begin(this);
    painter.fillRect(m_helper->clientRect(), QBrush(Qt::white));
    if (m_showButton)
    {
        int l = 16;
        int t = 64;
        for (int i = 0; i < buttons.count(); i++)
        {
            painter.save();
            rc = QRect(l, t, 48, 48);
            painter.setPen(Qt::NoPen);
            if (rc.contains(pt))
            {
                painter.setBrush(QBrush(QColor(230, 230, 230)));
            }
            painter.drawRoundRect(rc);
            painter.setPen(Qt::black);
            QuickSelectorButton* button = buttons.at(i);
            button->setRect(rc);

            painter.drawText(rc, Qt::AlignCenter, button->caption());

            painter.restore();

            l += 60;
            if (l > (width() - 64))
            {
                l = 16;
                t += 60;
            }

        }
    }
    else
    {
        painter.save();
        QRect clipRc(0, 64, width(), height() - 64);
        painter.setClipRect(clipRc);

        int t = m_helper->itemsTop();
        int l = 16;
        for (int i = 0; i < buttons.count(); i++)
        {
            QuickSelectorButton* button = buttons.at(i);
            rc = QRect(l, t, width() - 32, 32);
            QRect textRc(l + 16, t, width() - 48, 32);
            button->setRect(rc);
            painter.setPen(Qt::NoPen);
            if (rc.contains(pt))
            {
                painter.setBrush(QBrush(QColor(230, 230, 230)));
            }
            else
            {
                painter.setBrush(Qt::NoBrush);
            }
            painter.drawRect(rc);
            painter.setPen(Qt::black);
            QFont font = painter.font();
            font.setBold(true);
            font.setPixelSize(18);
            painter.setFont(font);
            painter.drawText(textRc, button->caption(), Qt::AlignVCenter | Qt::AlignLeft);
            t += 32;
            for (int j = 0; j < button->items.count(); j++)
            {
                QuickSelectorItem* item = button->items.at(j);
                rc = QRect(l, t, width() - 32, 32);
                item->setRect(rc);
                QRect textRc(l + 16, t, width() - 48, 32);
                painter.setPen(Qt::NoPen);
                if (rc.contains(pt))
                {
                    painter.setBrush(QBrush(QColor(230, 230, 230)));
                }
                else
                {
                    painter.setBrush(Qt::NoBrush);
                }
                painter.drawRect(rc);
                painter.setPen(Qt::black);
                QFont font = painter.font();
                font.setBold(false);
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(textRc, item->caption(), Qt::AlignVCenter | Qt::AlignLeft);
                t += 32;
            }
        }
        painter.restore();


    }
    painter.end();
}

void QuickSelector::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void QuickSelector::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    if (m_showButton)
    {
        for (int i = 0; i < buttons.count(); i++)
        {
            QuickSelectorButton* button = buttons.at(i);
            if (button->rect().contains(pt))
            {
                m_showButton = false;
                m_selectButton = button;
                initStartPoses();
                m_helper->setItemsTop(128 - button->startPos());
                update();
            }
        }

    }
    else
    {
        for (int i = 0; i < buttons.count(); i++)
        {
            QuickSelectorButton* button = buttons.at(i);
            if (button->rect().contains(pt))
            {
                m_showButton = true;
                update();
            }
        }
    }

}

void QuickSelector::wheelEvent(QWheelEvent* event)
{
    int y = m_helper->itemsTop() + event->angleDelta().y();
    y = y > 64 ? 64 : y;
    m_helper->setItemsTop(y);

}

bool QuickSelector::showButton() const
{
    return m_showButton;
}

void QuickSelector::setShowButton(bool showButton)
{
    m_showButton = showButton;
}

void QuickSelector::init()
{
    QString s = "#&0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < s.length(); i++)
    {
        QuickSelectorButton* button = new QuickSelectorButton(this);
        button->setCaption(s.at(i));
        buttons << button;
    }
}

void QuickSelector::initStartPoses()
{
    int t = 64;
    for (int i = 0; i < buttons.count(); i++)
    {
        QuickSelectorButton* button = buttons.at(i);
        button->setStartPos(t);
        t += 32;
        for (int j = 0; j < button->items.count(); j++)
        {
            QuickSelectorItem* item = button->items.at(j);
            item->setStartPos(t);
            t += 32;
        }
    }
}
