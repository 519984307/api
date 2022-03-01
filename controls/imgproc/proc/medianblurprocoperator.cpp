#include "medianblurprocoperator.h"

MedianBlurProcOperator::MedianBlurProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "中值滤波";

}

void MedianBlurProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    medianBlur(src, dest, 3);

}
