#include "fnchartyvalue.h"

FnChartYValue::FnChartYValue(QObject* parent) : QObject(parent)
{

}

double FnChartYValue::value() const
{
    return m_value;
}

void FnChartYValue::setValue(double value)
{
    m_value = value;
}

int FnChartYValue::x() const
{
    return m_x;
}

void FnChartYValue::setX(int x)
{
    m_x = x;
}

int FnChartYValue::y() const
{
    return m_y;
}

void FnChartYValue::setY(int y)
{
    m_y = y;
}

QString FnChartYValue::caption() const
{
    return m_caption;
}

void FnChartYValue::setCaption(const QString& caption)
{
    m_caption = caption;
}
