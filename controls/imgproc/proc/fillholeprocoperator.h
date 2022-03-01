#ifndef FILLHOLEPROCOPERATOR_H
#define FILLHOLEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class FillHoleProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit FillHoleProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
    void fillHole(Mat& mat, int x, int y);
    void setColor(Mat& mat, int x, int y, int r, int g, int b);
    void getColor(Mat& mat, int x, int y, int& r, int& g, int& b);
signals:

};

#endif // FILLHOLEPROCOPERATOR_H
