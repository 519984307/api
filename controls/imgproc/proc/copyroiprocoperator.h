#ifndef COPYROIPROCOPERATOR_H
#define COPYROIPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class CopyRoiProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit CopyRoiProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // COPYROIPROCOPERATOR_H
