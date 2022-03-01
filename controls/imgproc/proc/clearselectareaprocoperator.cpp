#include "clearselectareaprocoperator.h"

ClearSelectAreaProcOperator::ClearSelectAreaProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "清除所选区域";

}

void ClearSelectAreaProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    if (info.selLeft < 0)
    {
        info.selLeft = 0;
    }
    if (info.selTop < 0)
    {
        info.selTop = 0;
    }
    if (info.selLeft > src.cols)
    {
        return;
    }
    if (info.selTop > src.rows)
    {
        return;
    }
    if ((info.selLeft + info.selWidth) > src.cols)
    {
        info.selWidth = src.cols - info.selLeft;
    }

    if ((info.selTop + info.selHeight) > src.rows)
    {
        info.selHeight = src.rows - info.selTop;
    }
    if (info.selWidth <= 0)
    {
        return;
    }
    if (info.selHeight <= 0)
    {
        return;
    }

    Mat destMat = Mat(info.selHeight, info.selWidth, CV_8UC3, Scalar(info.colorR, info.colorG, info.colorB));
    Mat srcRoi = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    destMat.copyTo(srcRoi);
    dest = src.clone();
    qDebug() << info.selLeft << info.selTop << info.selWidth << info.selHeight;

}
