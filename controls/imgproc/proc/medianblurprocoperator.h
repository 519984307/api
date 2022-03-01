#ifndef MEDIANBLURPROCOPERATOR_H
#define MEDIANBLURPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
class MedianBlurProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit MedianBlurProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // MEDIANBLURPROCOPERATOR_H
