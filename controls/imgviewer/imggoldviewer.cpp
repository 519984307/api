#include "imggoldviewer.h"
#include "ui_imggoldviewer.h"


ImgGoldViewer::ImgGoldViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImgGoldViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_drawObj = new DrawObject(this);
    m_drawCommand = tpNone;
    setMouseTracking(true);

}

ImgGoldViewer::~ImgGoldViewer()
{
    delete ui;
}

void ImgGoldViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::red);
    painter.scale(m_helper->factor(), m_helper->factor());
    if (!m_srcImg.isNull())
    {
        QRect imgRc(0, 0, m_srcImg.width(), m_srcImg.height());
        painter.drawPixmap(imgRc, m_srcImg, m_srcImg.rect());

    }
    int w;
    int h;
    if (m_helper->mousedownFlag() == true)
    {
        if (m_drawCommand == tpHorRect)
        {
            w = m_helper->mouseMovePoint().x() - m_helper->mousedownPoint().x();
            h = w * 0.618;
            m_drawRect = QRect(m_helper->mousedownPoint().x(), m_helper->mousedownPoint().y(), w, h);
            painter.drawRect(m_drawRect);
        }
        else if (m_drawCommand == tpVerRect)
        {
            w = m_helper->mouseMovePoint().x() - m_helper->mousedownPoint().x();
            h = w * 1.618;
            m_drawRect = QRect(m_helper->mousedownPoint().x(), m_helper->mousedownPoint().y(), w, h);
            painter.drawRect(m_drawRect);

        }
        else if (m_drawCommand == tpLeftGoldSpiral)
        {
            m_drawObj->drawLeftGoldSpiral(painter, m_helper->mousedownPoint(),
                                          m_helper->mouseMovePoint().x() - m_helper->mousedownPoint().x());

        }
    }
    for (int i = 0; i < m_rects.count(); i++)
    {
        ImgGoldRect* obj = m_rects.at(i);
        if ((obj->rectType() == tpHorRect) || (obj->rectType() == tpVerRect))
        {
            painter.setPen(obj->color());
            painter.drawRect(obj->rect());
        }
    }


    painter.end();

}

void ImgGoldViewer::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();

}

void ImgGoldViewer::mouseReleaseEvent(QMouseEvent* event)
{

    if (m_drawCommand != tpNone)
    {
        ImgGoldRect* obj = new ImgGoldRect(this);
        obj->setRect(m_drawRect);
        obj->setRectType(m_drawCommand);
        m_rects << obj;

        m_drawCommand = tpNone;
        update();
    }
    m_helper->startMouseUp();
}

void ImgGoldViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_helper->mousedownFlag())
    {
        return;
    }
    m_helper->setMouseMovePoint();
    update();
}

void ImgGoldViewer::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    double factor = m_helper->factor();
    factor = factor * (y > 0 ? 1.1 : 0.9);
    m_helper->setFactor(factor);

}

ImgGoldRectCommand ImgGoldViewer::drawCommand() const
{
    return m_drawCommand;
}

void ImgGoldViewer::setDrawCommand(const ImgGoldRectCommand& drawCommand)
{
    m_drawCommand = drawCommand;
}



QPixmap ImgGoldViewer::srcImg() const
{
    return m_srcImg;
}

void ImgGoldViewer::setSrcImg(const QPixmap& srcImg)
{
    m_srcImg = srcImg;
    update();
}
