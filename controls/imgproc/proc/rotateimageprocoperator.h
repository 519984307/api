#ifndef ROTATEIMAGEPROCOPERATOR_H
#define ROTATEIMAGEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
class RotateImageProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit RotateImageProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);

signals:

};

#endif // ROTATEIMAGEPROCOPERATOR_H
