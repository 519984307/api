#ifndef IMAGEPROCHISTORYOBJECT_H
#define IMAGEPROCHISTORYOBJECT_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include <QPixmap>
using namespace cv;

class ImageProcHistoryObject : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcHistoryObject(QObject* parent = nullptr);

    QPixmap pix;
    QPixmap showPix;
    const Mat& mat() const;
    void setMat(const Mat& newMat);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

signals:
private:
    Mat m_mat;
    QRect m_rect;
};

#endif // IMAGEPROCHISTORYOBJECT_H
