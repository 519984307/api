#ifndef AUTOREMOVESTAINPROCOPERATOR_H
#define AUTOREMOVESTAINPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"


class AutoRemoveStainProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit AutoRemoveStainProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // AUTOREMOVESTAINPROCOPERATOR_H
