#include "fnchartxlabel.h"

FnChartXLabel::FnChartXLabel(QObject* parent) : QObject(parent)
{

}

QString FnChartXLabel::caption() const
{
    return m_caption;
}

void FnChartXLabel::setCaption(const QString& caption)
{
    m_caption = caption;
}

int FnChartXLabel::x() const
{
    return m_x;
}

void FnChartXLabel::setX(int x)
{
    m_x = x;
}

int FnChartXLabel::y() const
{
    return m_y;
}

void FnChartXLabel::setY(int y)
{
    m_y = y;
}
