#include "autoremovestainprocoperator.h"

AutoRemoveStainProcOperator::AutoRemoveStainProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "自动去污";

}

void AutoRemoveStainProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{

    removeStains(src, 0, 0, src.cols, src.rows, 3);
    dest = src;



}
