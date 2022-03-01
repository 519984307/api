#include "roundedbuttonlist.h"
#include "ui_roundedbuttonlist.h"

RoundedButtonList::RoundedButtonList(QWidget* parent) :
    ParentButtonList(parent),
    ui(new Ui::RoundedButtonList)
{
    ui->setupUi(this);
    m_drawObj = new DrawObject(this);
    m_buttonColor = Qt::gray;
    m_buttonDarkColor = m_buttonColor.darker();
    m_buttonLightColor = Qt::lightGray;
}

RoundedButtonList::~RoundedButtonList()
{
    delete ui;
}

int RoundedButtonList::buttonsWidth(QPainter& painter)
{

    QString s = "我";
    QFontMetrics fm = painter.fontMetrics();
    int w = fm.width(s) * m_maxCaptionLen + 32;
    for (int i = 0; i < m_items.count(); i++)
    {
        ButtonListItem* item = m_items.at(i);
        item->setWidth(w);
    }


    return w * m_items.count();

}

void RoundedButtonList::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter;
    QPoint curPt = m_helper->cursorPos();
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(Qt::white));

    QFont font = painter.font();
    font.setPixelSize(14);
    painter.setFont(font);

    int btnWidth = buttonsWidth(painter);
    int l = (width() - btnWidth) / 2;
    for (int i = 0; i < m_items.count(); i++)
    {
        ButtonListItem* item = m_items.at(i);
        int w = item->width();
        item->setRect(QRect(l, 8, w, height() - 16));
        QColor btnColor;
        if (i == m_activeIndex)
        {
            btnColor = m_buttonDarkColor;
        }
        else if (item->rect().contains(curPt))
        {
            btnColor = m_buttonLightColor;
        }
        else
        {
            btnColor = m_buttonColor;
        }
        if (i == 0)
        {
            m_drawObj->drawRoundRect(painter, item->rect(), btnColor, DrawObjectRectStyle::DrawLeft);
        }
        else if (i == (m_items.count() - 1))
        {
            m_drawObj->drawRoundRect(painter, item->rect(), btnColor, DrawObjectRectStyle::DrawRight);
        }
        else
        {
            m_drawObj->drawRoundRect(painter, item->rect(), btnColor, DrawObjectRectStyle::DrawNone);
        }

        painter.setPen(Qt::white);
        painter.drawText(item->rect(), Qt::AlignCenter, item->caption());
        if (i < (m_items.count() - 1))
        {
            painter.drawLine(item->rect().right(), item->rect().top(), item->rect().right(), item->rect().bottom());
        }


        l += w;
    }
    painter.end();
}

void RoundedButtonList::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    update();
}

void RoundedButtonList::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        ButtonListItem* item = m_items.at(i);
        if (item->rect().contains(curPt))
        {
            m_activeIndex = i;
            emit clickButton(item);
            break;
        }

    }
    update();
}

const QColor& RoundedButtonList::buttonLightColor() const
{
    return m_buttonLightColor;
}

void RoundedButtonList::setButtonLightColor(const QColor& newButtonLightColor)
{
    m_buttonLightColor = newButtonLightColor;
}

const QColor& RoundedButtonList::buttonDarkColor() const
{
    return m_buttonDarkColor;
}

void RoundedButtonList::setButtonDarkColor(const QColor& newButtonDarkColor)
{
    m_buttonDarkColor = newButtonDarkColor;
}

const QColor& RoundedButtonList::buttonColor() const
{
    return m_buttonColor;
}

void RoundedButtonList::setButtonColor(const QColor& newButtonColor)
{
    m_buttonColor = newButtonColor;
}
