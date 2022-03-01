#ifndef CLEAROUTAREAPROCOPERATOR_H
#define CLEAROUTAREAPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
class ClearOutAreaProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit ClearOutAreaProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // CLEAROUTAREAPROCOPERATOR_H
