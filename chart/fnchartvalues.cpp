#include "fnchartvalues.h"

FnChartValues::FnChartValues(QObject* parent) : QObject(parent)
{
    m_color = QColor(rand() % 256, rand() % 256, rand() % 256);
    m_isShow = true;

}

QColor FnChartValues::color() const
{
    return m_color;
}

void FnChartValues::setColor(const QColor& color)
{
    m_color = color;
}

QString FnChartValues::caption() const
{
    return m_caption;
}

void FnChartValues::setCaption(const QString& caption)
{
    m_caption = caption;
}

QRect FnChartValues::colorRect() const
{
    return m_colorRect;
}

void FnChartValues::setColorRect(const QRect& colorRect)
{
    m_colorRect = colorRect;
}

bool FnChartValues::isShow() const
{
    return m_isShow;
}

void FnChartValues::setIsShow(bool isShow)
{
    m_isShow = isShow;
}

int FnChartValues::pointNumber() const
{
    return m_pointNumber;
}

void FnChartValues::setPointNumber(int pointNumber)
{
    m_pointNumber = pointNumber;
}

FnChartYValue* FnChartValues::getValueByCaption(QString caption)
{
    FnChartYValue* ret = nullptr;
    for (int i = 0; i < values.count(); i++)
    {
        FnChartYValue* value = values.at(i);
        if (value->caption() == caption)
        {
            ret = value;
            break;
        }
    }

    return ret;

}
