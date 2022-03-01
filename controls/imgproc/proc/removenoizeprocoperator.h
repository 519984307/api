#ifndef REMOVENOIZEPROCOPERATOR_H
#define REMOVENOIZEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class RemoveNoizeProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit RemoveNoizeProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // REMOVENOIZEPROCOPERATOR_H
