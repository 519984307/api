#ifndef CHANGEANGLEPROCOPERATOR_H
#define CHANGEANGLEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class ChangeAngleProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit ChangeAngleProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);

signals:

};

#endif // CHANGEANGLEPROCOPERATOR_H
