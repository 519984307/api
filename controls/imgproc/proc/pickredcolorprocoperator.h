#ifndef PICKREDCOLORPROCOPERATOR_H
#define PICKREDCOLORPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class PickRedColorProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit PickRedColorProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // PICKREDCOLORPROCOPERATOR_H
