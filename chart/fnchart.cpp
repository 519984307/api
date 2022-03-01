#include "fnchart.h"
#include "ui_fnchart.h"

FnChart::FnChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnChart)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    resetOrigin();

}

FnChart::~FnChart()
{
    delete ui;
}

int FnChart::originX() const
{
    return m_originX;
}

void FnChart::setOriginX(int originX)
{
    m_originX = originX;
}

int FnChart::originY() const
{
    return m_originY;
}

void FnChart::setOriginY(int originY)
{
    m_originY = originY;
}

int FnChart::zoomX() const
{
    return m_zoomX;
}

void FnChart::setZoomX(int zoomX)
{
    m_zoomX = zoomX;
}

int FnChart::zoomY() const
{
    return m_zoomY;
}

void FnChart::resetOrigin()
{
    m_originX = 64;
    m_originY = height() - 32;
    m_xLabelWidth = 120;
    m_startX = m_originX;
    m_startY = m_originY;
    update();
}

void FnChart::addXLabel(QString caption)
{
    FnChartXLabel* xlabel = new FnChartXLabel(this);
    xlabel->setCaption(caption);
    m_xlabels << xlabel;
    update();
}

void FnChart::paintEvent(QPaintEvent* event)
{
    QStringList labelInfos;
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    //绘制线条
    painter.drawLine(0, m_originY, width(), m_originY);
    painter.drawLine(m_originX, height() - 32, m_originX, 0);



    //绘制x轴标签
    QMap<QString, int> labelMap;
    int m = m_startX + m_xLabelWidth;
    for (int i = 0; i < m_xlabels.count(); i++)
    {
        FnChartXLabel* xlabel = m_xlabels.at(i);
        xlabel->setX(m);
        QRect textRc = QRect(m - m_xLabelWidth / 2, m_originY + 6, m_xLabelWidth, 24);
        xlabel->labelRect = QRect(m - m_xLabelWidth / 2, 0, m_xLabelWidth, height());
        if (m_xLabelWidth >= 120)
        {
            painter.drawText(textRc, Qt::AlignCenter, xlabel->caption());
        }

        labelMap.insert(xlabel->caption(), m);
        m += m_xLabelWidth;
    }
    //绘制y轴

    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);
        if (!dataValues->isShow())
            continue;
        QPoint prePt;
        painter.save();
        QPen pen = painter.pen();
        pen.setColor(dataValues->color());
        pen.setWidth(2);
        painter.setPen(pen);
        for (int j = 0; j < m_xlabels.count(); j++)
        {
            QString caption = m_xlabels.at(j)->caption();
            FnChartYValue* value = dataValues->getValueByCaption(caption);
            double v = value == nullptr ? 0 : value->value();
            int y = m_startY - v * 10;

            int x = labelMap[caption];

            if ((abs(curPt.x() - x) <= 10) && (value != nullptr))
            {
                if (labelInfos.count() == 0)
                {
                    labelInfos << value->caption();
                }
                labelInfos << QString("%1    %2").arg(dataValues->caption()).arg(value->value());

            }

            if (value != nullptr)
            {
                value->setY(y);
                value->setX(x);

            }
            QPoint pt = QPoint(x, y);
            if (j == 0)
            {
                prePt = QPoint(x, y);
            }
            else
            {

                QPointF tempPt1 = QPointF((pt.x() + prePt.x()) / 2, prePt.y());
                QPointF tempPt2 = QPointF((pt.x() + prePt.x()) / 2, pt.y());
                QPainterPath path;
                path.moveTo(prePt);
                path.cubicTo(tempPt1, tempPt2, pt);
                painter.drawPath(path);


                prePt = pt;
            }
            painter.setBrush(QBrush(dataValues->color()));
            painter.drawEllipse(pt.x() - 4, pt.y() - 4, 8, 8);
            painter.setBrush(Qt::NoBrush);

        }
        painter.restore();
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
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, dataValues->caption());

        painter.restore();
        t += 36;

    }
    QPen pen = painter.pen();
    pen.setColor(QColor(197, 197, 197));
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawLine(0, m_startY, width(), m_startY);
    painter.drawLine(curPt.x(), 0, curPt.x(), height());
    if (labelInfos.count() > 0)
    {
        painter.setPen(Qt::black);
        int t = curPt.y();
        for (int i = 0; i < labelInfos.count(); i++)
        {
            QFont font = painter.font();
            font.setBold(i == 0 ? true : false);
            painter.setFont(font);

            painter.drawText(curPt.x() + 6, t, labelInfos[i]);
            t += 24;

        }

    }
    painter.end();
}

void FnChart::mousePressEvent(QMouseEvent* event)
{

    m_helper->startMouseDown();

}

void FnChart::mouseReleaseEvent(QMouseEvent* event)
{

    m_helper->startMouseUp();
}

void FnChart::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint pt = m_helper->cursorPos();
        int x = pt.x() - m_helper->mousedownPoint().x();
        int y = pt.y() - m_helper->mousedownPoint().y();
        m_startX += x;
        m_startY += y;
        m_helper->setMousedownPoint(pt);


    }
    update();

}

void FnChart::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F5)
    {
        resetOrigin();

    }
}

void FnChart::resizeEvent(QResizeEvent* event)
{
    resetOrigin();
}

void FnChart::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);
        if (dataValues->colorRect().contains(pt))
        {
            dataValues->setIsShow(!dataValues->isShow());
        }

    }
    update();
}

void FnChart::wheelEvent(QWheelEvent* event)
{
    int x = event->angleDelta().y();
    qDebug() << x;
    if (qApp->keyboardModifiers() == Qt::ControlModifier)
    {
        qDebug() << "Qt::AltModifier" << x;
        m_xLabelWidth += (x > 0 ? 10 : -10);

    }
    else
    {
        m_startX += x;
    }

    update();
}

int FnChart::xLabelWidth() const
{
    return m_xLabelWidth;
}

void FnChart::setXLabelWidth(int xLabelWidth)
{
    m_xLabelWidth = xLabelWidth;
}

void FnChart::addChartValues(FnChartValues* values)
{
    m_series << values;
    update();
}
