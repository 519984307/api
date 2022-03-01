#ifndef CLEARSELECTAREAPROCOPERATOR_H
#define CLEARSELECTAREAPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class ClearSelectAreaProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit ClearSelectAreaProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // CLEARSELECTAREAPROCOPERATOR_H
