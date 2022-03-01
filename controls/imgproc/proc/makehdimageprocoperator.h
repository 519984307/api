#ifndef MAKEHDIMAGEPROCOPERATOR_H
#define MAKEHDIMAGEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
#include "imageprocbase.h"

class MakeHdImageProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit MakeHdImageProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // MAKEHDIMAGEPROCOPERATOR_H
