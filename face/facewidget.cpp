#include "facewidget.h"
#include "ui_facewidget.h"

FaceWidget::FaceWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FaceWidget)
{
    ui->setupUi(this);
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    m_faceOneSideWidth = qrand() % 50 + 50;
    m_faceUpHeight = qrand() % 50 + 50;
    m_faceDownHeight = qrand() % 50 + 100;
    m_eyeWidth = qrand() % 20 + 3;
    m_eyeHeight = qrand() % 20 + 3;
    m_mouseHeight = 40 - qrand() % 80;
    m_mouseWidth = rand() % 50 + 50;
    m_eyeSelect = rand() % 100;
}

FaceWidget::~FaceWidget()
{
    delete ui;
}

int FaceWidget::faceOneSideWidth() const
{
    return m_faceOneSideWidth;
}

void FaceWidget::setFaceOneSideWidth(int faceOneSideWidth)
{
    m_faceOneSideWidth = faceOneSideWidth;
}

int FaceWidget::faceUpHeight() const
{
    return m_faceUpHeight;
}

void FaceWidget::setFaceUpHeight(int faceUpHeight)
{
    m_faceUpHeight = faceUpHeight;
}

int FaceWidget::faceDownHeight() const
{
    return m_faceDownHeight;
}

void FaceWidget::setFaceDownHeight(int faceDownHeight)
{
    m_faceDownHeight = faceDownHeight;
}

void FaceWidget::drawEye(QPainter& painter, QPoint pt, int w, int h, int n)
{

    if (n % 2 == 0)
    {
        painter.save();
        QRect rc = QRect(pt.x() - w, pt.y() - h, w * 2, h * 2);
        painter.drawEllipse(rc);
        painter.setBrush(QColor(121, 22, 3));
        int r = w < h ? w : h;
        r = r - 4;
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QRect(pt.x() - r, pt.y() - r, r * 2, r * 2));
        painter.restore();
    }
    else
    {
        painter.save();
        QRect clipRect = QRect(pt.x() - w, pt.y() - h, w * 2, h);
        painter.setClipRect(clipRect);
        QRect rc = QRect(pt.x() - w, pt.y() - h, w * 2, h * 2);

        painter.drawEllipse(rc);
        painter.restore();
    }


}

void FaceWidget::drawMouse(QPainter& painter, QPoint pt, int r, int n)
{
    painter.save();
    QRect clipRect;
    if (r != 0)
    {
        clipRect.setRect(pt.x() - m_mouseWidth, pt.y() - r, m_mouseWidth * 2, abs(r));
    }
    else
    {
        clipRect.setRect(pt.x() - m_mouseWidth, pt.y() - m_mouseWidth, m_mouseWidth * 2, m_mouseWidth * 2);
    }
    painter.setClipRect(clipRect);
    QRect rc = QRect(pt.x() - r, pt.y() - r, r * 2, r * 2);
    painter.drawEllipse(rc);


    painter.restore();

}

void FaceWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    int centerX = width() / 2;
    int centerY = height() / 2;
    QRect clipRc;
    QRect rc;
    painter.begin(this);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(216, 113, 34));
    painter.setPen(pen);
    painter.setBrush(QColor(254, 241, 31));
//    painter.drawLine(0, centerY, width(), centerY);
//    painter.drawLine(centerX, 0, centerX, height());

    painter.save();
    clipRc = QRect(centerX - m_faceOneSideWidth, centerY - m_faceUpHeight, m_faceOneSideWidth * 2, m_faceUpHeight);


    painter.setClipRect(clipRc);
    rc.setRect(centerX - m_faceOneSideWidth, centerY - m_faceUpHeight, m_faceOneSideWidth * 2, m_faceUpHeight * 2);
    painter.drawEllipse(rc);
    painter.restore();

    painter.save();
    clipRc = QRect(centerX - m_faceOneSideWidth, centerY, m_faceOneSideWidth * 2, m_faceDownHeight);
    painter.setClipRect(clipRc);
    rc.setRect(centerX - m_faceOneSideWidth, centerY - m_faceDownHeight, m_faceOneSideWidth * 2, m_faceDownHeight * 2);
    painter.drawEllipse(rc);
    painter.restore();

    //绘制眼睛

    drawEye(painter, QPoint(centerX - m_faceOneSideWidth / 2, centerY), m_eyeWidth, m_eyeHeight, m_eyeSelect);
    drawEye(painter, QPoint(centerX + m_faceOneSideWidth / 2, centerY), m_eyeWidth,  m_eyeHeight, m_eyeSelect);

    //绘制嘴
    drawMouse(painter, QPoint(centerX, centerY + m_faceDownHeight * 0.7), m_mouseHeight, 0);
    painter.end();
}

int FaceWidget::mouseWidth() const
{
    return m_mouseWidth;
}

void FaceWidget::setMouseWidth(int mouseWidth)
{
    m_mouseWidth = mouseWidth;
}

int FaceWidget::eyeWidth() const
{
    return m_eyeWidth;
}

void FaceWidget::setEyeWidth(int eyeWidth)
{
    m_eyeWidth = eyeWidth;
}
