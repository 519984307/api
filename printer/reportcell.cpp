#include "reportcell.h"

ReportCell::ReportCell(QObject* parent) : QObject(parent)
{

}

const QString& ReportCell::text() const
{
    return m_text;
}

void ReportCell::setText(const QString& newText)
{
    m_text = newText;
}

int ReportCell::left() const
{
    return m_left;
}

void ReportCell::setLeft(int newLeft)
{
    m_left = newLeft;
}

int ReportCell::top() const
{
    return m_top;
}

void ReportCell::setTop(int newTop)
{
    m_top = newTop;
}

int ReportCell::width() const
{
    return m_width;
}

void ReportCell::setWidth(int newWidth)
{
    m_width = newWidth;
}

int ReportCell::height() const
{
    return m_height;
}

void ReportCell::setHeight(int newHeight)
{
    m_height = newHeight;
}

int ReportCell::right()
{
    return m_left + m_width;
}

void ReportCell::setRectMm(int leftMm, int topMm, int widthMm, int BottomMm)
{
    m_left = MmToPt(leftMm);
    m_top = MmToPt(topMm);
    m_width = MmToPt(widthMm);
    m_height = MmToPt(BottomMm);
}

int ReportCell::MmToPt(int m)
{
    return m * 4;
}
