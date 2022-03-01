#include "copyroiprocoperator.h"

CopyRoiProcOperator::CopyRoiProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "区域复制";

}

void CopyRoiProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));

}
