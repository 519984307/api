#ifndef AUTOCHANGEANGLEPROCOPERATOR_H
#define AUTOCHANGEANGLEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
#define ERROR 1234
class AutoChangeAngleProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit AutoChangeAngleProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
    void rotateImgDataByCenter(Mat& src, Mat& dest, int angle);
    double getImageAngle(Mat& mat);
    double getAngleFromAngles(QMap<int, int>& angles);
signals:

};

#endif // AUTOCHANGEANGLEPROCOPERATOR_H
