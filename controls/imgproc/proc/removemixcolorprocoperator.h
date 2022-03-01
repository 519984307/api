#ifndef REMOVEMIXCOLORPROCOPERATOR_H
#define REMOVEMIXCOLORPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
class RemoveMixColorProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit RemoveMixColorProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // REMOVEMIXCOLORPROCOPERATOR_H
