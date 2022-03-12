#include "widgethelper.h"

WidgetHelper::WidgetHelper(QObject* parent) : QObject(parent)
{
    m_mousedownFlag = false;
    m_factor = 1;
    m_maxLeft = 0;
    m_maxTop = 16;
    m_isTouch = false;
    m_control = nullptr;

}

bool WidgetHelper::mousedownFlag() const
{
    return m_mousedownFlag;
}

void WidgetHelper::setMousedownFlag(bool mousedownFlag)
{
    m_mousedownFlag = mousedownFlag;
    m_control->update();
}

QPoint WidgetHelper::mousedownPoint() const
{
    return m_mousedownPoint;
}

void WidgetHelper::setMousedownPoint(const QPoint& mousedownPoint)
{
    m_mousedownPoint = mousedownPoint;
}

void WidgetHelper::startMouseDown()
{
    m_mousedownFlag = true;
    m_mousedownPoint = cursorPos();
    m_mouseMovePoint = m_mousedownPoint;
    m_control->update();


}

void WidgetHelper::startMouseUp()
{
    m_mousedownFlag = false;
    m_control->update();
}

void WidgetHelper::mouseMove(int& x, int& y)
{
    QPoint pt = cursorPos();

    x = pt.x() - m_mousedownPoint.x();
    y = pt.y() - m_mousedownPoint.y();
    m_mousedownPoint = pt;

}

QWidget* WidgetHelper::control() const
{
    return m_control;
}

void WidgetHelper::setControl(QWidget* control)
{
    m_control = control;
}

QPoint WidgetHelper::cursorPos()
{
    if (m_control == nullptr)
    {
        return QPoint(0, 0);
    }
    QPoint pt = m_control->cursor().pos();
    pt = m_control->mapFromGlobal(pt);
    pt = QPoint(pt.x() / m_factor, pt.y() / m_factor);
    return pt;
}

QPoint WidgetHelper::virtualCurPos(double dx, double dy)
{
    QPoint pt = cursorPos();
    pt = QPoint(pt.x() + dx, pt.y() + dy);
    return pt;
}

int WidgetHelper::itemsTop() const
{
    return m_itemsTop;
}

void WidgetHelper::setItemsTop(int itemsTop)
{
    m_itemsTop = itemsTop;
    m_control->update();


}

void WidgetHelper::moveTop(int d)
{
    int y = m_itemsTop + d;
    if (y > m_maxTop)
    {
        y = m_maxTop;
    }
    setItemsTop(y);
}

QRect WidgetHelper::clientRect()
{
    return QRect(0, 0, m_control->width(), m_control->height());
}

QRect WidgetHelper::needDrawClientRect(int minTop, int maxHeight)
{
    return QRect(0, minTop, m_control->width(), maxHeight);
}

QPoint WidgetHelper::centerPos()
{
    return QPoint(m_control->width() / 2, m_control->height() / 2);
}

int WidgetHelper::radius()
{
    int r = m_control->width() <= m_control->height() ? m_control->width() :
            m_control->height();
    return r / 2;
}

double WidgetHelper::factor() const
{
    return m_factor;
}

void WidgetHelper::setFactor(double factor)
{
    m_factor = factor;
    m_control->update();
}

QPoint WidgetHelper::mouseMovePoint() const
{
    return m_mouseMovePoint;
}

void WidgetHelper::setMouseMovePoint(const QPoint& mouseMovePoint)
{
    m_mouseMovePoint = mouseMovePoint;
}

void WidgetHelper::setMouseMovePoint()
{
    m_mouseMovePoint = cursorPos();
}

QRect WidgetHelper::innerRect(QRect rc)
{
    return QRect(rc.left() + 1, rc.top() + 1, rc.width() - 2, rc.height() - 2);
}

int WidgetHelper::maxLeft() const
{
    return m_maxLeft;
}

void WidgetHelper::setMaxLeft(int maxLeft)
{
    m_maxLeft = maxLeft;
}

int WidgetHelper::itemsLeft() const
{
    return m_itemsLeft;
}

void WidgetHelper::setItemsLeft(int itemsLeft)
{
    m_itemsLeft = itemsLeft;
    m_control->update();
}

int WidgetHelper::itemsWidth() const
{
    return m_itemsWidth;
}

void WidgetHelper::setItemsWidth(int itemsWidth)
{
    m_itemsWidth = itemsWidth;
}

int WidgetHelper::maxTop() const
{
    return m_maxTop;
}

void WidgetHelper::setMaxTop(int newMaxTop)
{
    m_maxTop = newMaxTop;
}

bool WidgetHelper::isClicked()
{
    bool ret = false;

    if ((m_mouseMovePoint.x() == m_mousedownPoint.x()) &&
        (m_mouseMovePoint.y() == m_mousedownPoint.y()))
    {
        ret = true;
    }

    return ret;
}

bool WidgetHelper::isTwoPoint() const
{
    return m_isTwoPoint;
}

void WidgetHelper::setIsTwoPoint(bool newIsTwoPoint)
{
    m_isTwoPoint = newIsTwoPoint;
}

bool WidgetHelper::isTouch() const
{
    return m_isTouch;
}

void WidgetHelper::setIsTouch(bool newIsTouch)
{
    m_isTouch = newIsTouch;
}

void WidgetHelper::startTouch()
{
    m_isTouch = true;
    m_control->update();

}

void WidgetHelper::endTouch()
{
    m_isTouch = false;
    m_control->update();
}

QPoint WidgetHelper::startTouchPoint0() const
{
    return m_startTouchPoint0;
}

void WidgetHelper::setStartTouchPoint0(QPoint newStartTouchPoint0)
{
    m_startTouchPoint0 = newStartTouchPoint0;
}

QPoint WidgetHelper::startTouchPoint1() const
{
    return m_startTouchPoint1;
}

void WidgetHelper::setStartTouchPoint1(QPoint newStartTouchPoint1)
{
    m_startTouchPoint1 = newStartTouchPoint1;
}

QRect WidgetHelper::lastRect() const
{
    return m_lastRect;
}

void WidgetHelper::setLastRect(const QRect& lastRect)
{
    m_lastRect = lastRect;
}
