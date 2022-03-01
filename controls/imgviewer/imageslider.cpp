#include "imageslider.h"
#include "ui_imageslider.h"

ImageSlider::ImageSlider(QWidget* parent) :
    ParentImageViewer(parent),
    ui(new Ui::ImageSlider)
{
    ui->setupUi(this);
    m_bottomColor = QColor(34, 34, 34);
    m_clientColor = QColor(43, 43, 43);
    m_snapLeft = 16;
    m_columnCount = 100000000;

}

ImageSlider::~ImageSlider()
{
    delete ui;
}

void ImageSlider::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    m_bottomRect = QRect(0, height() - 96, width(), 96);
    m_clientRect = QRect(0, 0, width(), height() - 96);
    m_centerRect = QRect(0, 16, width(), m_clientRect.height() - 64);
    QRect clientRc(-width() * 0.5, m_bottomRect.top() - 1, width() * 2, m_clientRect.height() + 2);
    painter.begin(this);
    painter.fillRect(m_clientRect, QBrush(m_clientColor));

    painter.fillRect(m_bottomRect, QBrush(m_bottomColor));
    int l = m_snapLeft;
    int t = m_bottomRect.top() + 16;
    for (int i = 0; i < images.count(); i++)
    {

        ImageObject* cell = images.at(i);
        QRect snapRc(l, t, 64, 64);
        cell->setSnapRect(snapRc);
        if ((clientRc.contains(snapRc)) || (cell->isSelected()))
        {
            cell->loadImage();
            if (cell->isSelected())
            {
                qDebug() << m_centerRect;
                double f1 = m_centerRect.width();
                f1 = f1 / m_centerRect.height();

                double f2 = cell->aspectRatio();

                m_centerImg = cell->pix().copy();
                if ((m_centerImg.width() > m_centerRect.width())
                    || (m_centerImg.height() > m_centerRect.height()))
                {
                    if (f1 > f2)
                    {
                        m_centerImg = m_centerImg.scaledToHeight(m_centerRect.height(), Qt::SmoothTransformation);
                    }
                    else
                    {
                        m_centerImg = m_centerImg.scaledToWidth(m_centerRect.width(), Qt::SmoothTransformation);
                    }

                }

                m_centerImgRect = QRect(m_centerRect.center().x() - m_centerImg.width() / 2,
                                        m_centerRect.center().y() - m_centerImg.height() / 2,
                                        m_centerImg.width(), m_centerImg.height());
                painter.drawPixmap(m_centerImgRect, m_centerImg, m_centerImg.rect());
            }

            painter.drawPixmap(snapRc, cell->pix(), cell->pix().rect());
        }
        else
        {
            if (cell->isSelected() == false)
            {
                cell->freeImage();
            }

        }




        l += 80;

    }

    painter.end();

}

void ImageSlider::wheelEvent(QWheelEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    if (m_bottomRect.contains(pt))
    {
        m_snapLeft += event->angleDelta().y();
        if (m_snapLeft > 16)
        {
            m_snapLeft = 16;
        }
        update();
    }

}

void ImageSlider::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    if (m_bottomRect.contains(pt))
    {
        ImageObject* testCell = nullptr;
        for (int i = 0; i < images.count(); i++)
        {
            ImageObject* cell = images.at(i);
            if (cell->snapRect().contains(pt))
            {
                testCell = cell;
                break;
            }
        }
        if (testCell != nullptr)
        {
            for (int i = 0; i < images.count(); i++)
            {
                ImageObject* cell = images.at(i);
                cell->setIsSelected(cell->snapRect().contains(pt));
            }
        }

    }

    update();


}
