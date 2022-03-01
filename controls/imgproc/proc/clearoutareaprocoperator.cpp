#include "clearoutareaprocoperator.h"

ClearOutAreaProcOperator::ClearOutAreaProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "清除外边框";

}

void ClearOutAreaProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
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

    Mat destMat = Mat(src.rows, src.cols, CV_8UC3, Scalar(info.colorR, info.colorG, info.colorB));
    Mat tmp = destMat(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    Mat srcRoi = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    srcRoi.copyTo(tmp);
    dest = destMat;
    qDebug() << info.selLeft << info.selTop << info.selWidth << info.selHeight;
}
