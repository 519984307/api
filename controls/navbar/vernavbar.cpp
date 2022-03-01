#include "vernavbar.h"
#include "ui_vernavbar.h"

VerNavBar::VerNavBar(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::VerNavBar)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_seletedItem = nullptr;
}

VerNavBar::~VerNavBar()
{
    delete ui;
}

void VerNavBar::addItems(QStringList& captions)
{
    for (int i = 0; i < captions.count(); i++) {
        SelectionItem* item = new SelectionItem(this);
        item->setCaption(captions[i]);
        m_items << item;
    }
    update();
}

SelectionItem* VerNavBar::getItem(const QString& caption)
{
    for (int i = 0; i < m_items.count(); i++) {
        if (m_items.at(i)->caption() == caption) {
            return m_items.at(i);
        }
    }
    return nullptr;
}

void VerNavBar::paintEvent(QPaintEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(42, 42, 49));
    int t = 0;
    QFont font = painter.font();
    font.setPixelSize(10);
#ifdef WIN64
    font.setFamily("微软雅黑");
#endif
    painter.setFont(font);
    for (int i = 0; i < m_items.count(); i++) {
        SelectionItem* item = m_items.at(i);
        painter.setPen(Qt::white);
        QRect itemRc;
        itemRc.setRect(0, t, width(), 32);
        item->setItemRect(itemRc);
        if ((itemRc.contains(pt)) || (item->selected())) {
            painter.fillRect(itemRc, QColor(19, 24, 36));
        }
        if (item->selected()) {
            painter.setPen(QColor(255, 92, 56));
        } else {
            painter.setPen(Qt::white);
        }
        if (!item->icon().isNull()) {
            QRect iconRect;
            iconRect.setRect(14, t + 14, 8, 8);
            painter.drawPixmap(iconRect, item->icon(), item->icon().rect());
        }
        QRect textRc;

        textRc.setRect(48, t + 13, width() - 48, 10);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, item->caption());
        t = t + 32;
    }
    painter.end();
}

void VerNavBar::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void VerNavBar::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    for (int i = 0; i < m_items.count(); i++) {
        SelectionItem* item = m_items.at(i);
        item->setSelected(item->itemRect().contains(pt));
        if (item->selected()) {
            if (item != m_seletedItem) {
                emit onClickItem(item);
                m_seletedItem = item;
            }
        }
    }
    update();
}
