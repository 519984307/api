#include "chatlistitem.h"
#include "ui_chatlistitem.h"

ChatListItem::ChatListItem(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ChatListItem)
{
    ui->setupUi(this);
    m_iconAlign = IaRight;
    m_textBackColor = QColor(158, 234, 106);
}

ChatListItem::~ChatListItem()
{
    delete ui;
}

void ChatListItem::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect iconRc, infoRc;
    QFontMetrics fm = painter.fontMetrics();
    int infoWidth = fm.width(m_info) + 24;
    if (m_iconAlign == IaLeft) {
        iconRc = QRect(12, 6, 24, 24);
        infoRc = QRect(48, 6, infoWidth, 24);
    } else {
        iconRc = QRect(width() - 36, 6, 24, 24);
        infoRc = QRect(width() - 48 - infoWidth, 6, infoWidth, 24);
    }

    painter.drawPixmap(iconRc, m_icon, m_icon.rect());
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_textBackColor);
    painter.drawRoundRect(infoRc, 10, 10);
    painter.setPen(Qt::black);
    painter.drawText(infoRc, Qt::AlignCenter, m_info);
    painter.end();
}

QColor ChatListItem::textBackColor() const
{
    return m_textBackColor;
}

void ChatListItem::setTextBackColor(const QColor& textBackColor)
{
    m_textBackColor = textBackColor;
}

IconAlign ChatListItem::iconAlign() const
{
    return m_iconAlign;
}

void ChatListItem::setIconAlign(const IconAlign& iconAlign)
{
    m_iconAlign = iconAlign;
    update();
}

QString ChatListItem::info() const
{
    return m_info;
}

void ChatListItem::setInfo(const QString& info)
{
    m_info = info;
}

QPixmap ChatListItem::icon() const
{
    return m_icon;
}

void ChatListItem::setIcon(const QPixmap& icon)
{
    m_icon = icon;
}
