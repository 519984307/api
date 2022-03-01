#include "fnpointchart.h"
#include "ui_fnpointchart.h"

FnPointChart::FnPointChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnPointChart)
{
    ui->setupUi(this);
    m_zoomValue = 2;
    setMouseTracking(true);
}

FnPointChart::~FnPointChart()
{
    delete ui;
}

void FnPointChart::addChartValues(FnChartValues* values)
{
    m_series << values;
    update();
}

void FnPointChart::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    int m = 0;
    int n = 0;
    for (int i = 0; i < m_series.count(); i++)
    {

        FnChartValues* dataValues = m_series.at(i);
        QColor color = dataValues->color();
        painter.setPen(color);
        for (int j = 0; j < dataValues->pointNumber(); j++)
        {
            for (int k = 0; k < m_zoomValue; k++)
            {
                QRect rc = QRect(m, n, m_zoomValue, m_zoomValue);
                painter.fillRect(rc, QBrush(color));
                if (m + m_zoomValue >= (width() - 300))
                {
                    m = 0;
                    n += m_zoomValue;
                }
                else
                {
                    m += m_zoomValue;
                }
            }
        }

    }

    int t = 16;
    int l = width() - 200;
    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);

        painter.save();
        QRect rc = QRect(l, t, 24, 24);
        dataValues->setColorRect(rc);
        painter.fillRect(rc, dataValues->isShow() ? dataValues->color() : QColor(197, 197, 197));
        QRect textRc = QRect(l + 36, t, 160, 24);
        painter.setPen(Qt::black);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter,
                         QString("%1 %2").arg(dataValues->caption()).arg(dataValues->pointNumber()));

        painter.restore();
        t += 36;

    }
    painter.end();

}

int FnPointChart::zoomValue() const
{
    return m_zoomValue;
}

void FnPointChart::setZoomValue(int zoomValue)
{
    m_zoomValue = zoomValue;
}

void FnPointChart::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    if (y > 0)
    {
        m_zoomValue -= 2;
    }
    else
    {
        m_zoomValue += 2;
    }
    if (m_zoomValue < 2)
    {
        m_zoomValue = 2;
    }
    update();
}
