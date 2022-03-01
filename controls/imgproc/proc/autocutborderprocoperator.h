#ifndef AUTOCUTBORDERPROCOPERATOR_H
#define AUTOCUTBORDERPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class AutoCutBorderProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit AutoCutBorderProcOperator(QObject* parent = nullptr);
    void findROI(Mat& src, Mat& dest);           //声明函数，用于找到兴趣区域

    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:
private:
    int threshold_value = 100;      // 定义阈值，全局变量
    int max_level = 255;          // 定义最大阈值，全局变量

};

#endif // AUTOCUTBORDERPROCOPERATOR_H
