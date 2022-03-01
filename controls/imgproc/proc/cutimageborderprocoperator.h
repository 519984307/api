#ifndef CUTIMAGEBORDERPROCOPERATOR_H
#define CUTIMAGEBORDERPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
#include <QDebug>

class CutImageBorderProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit CutImageBorderProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // CUTIMAGEBORDERPROCOPERATOR_H
