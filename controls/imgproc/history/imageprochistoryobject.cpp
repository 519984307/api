#include "imageprochistoryobject.h"

ImageProcHistoryObject::ImageProcHistoryObject(QObject* parent) : QObject(parent)
{

}

const Mat& ImageProcHistoryObject::mat() const
{
    return m_mat;
}

void ImageProcHistoryObject::setMat(const Mat& newMat)
{
    m_mat = newMat;
    QImage img = QImage((const uchar*)(m_mat.data), m_mat.cols, m_mat.rows,
                        m_mat.cols * m_mat.channels(), QImage::Format_RGB888);
    pix = QPixmap::fromImage(img);
    showPix = pix.scaledToHeight(128, Qt::SmoothTransformation);
}

const QRect& ImageProcHistoryObject::rect() const
{
    return m_rect;
}

void ImageProcHistoryObject::setRect(const QRect& newRect)
{
    m_rect = newRect;
}
