#include "cutimageborderprocoperator.h"

CutImageBorderProcOperator::CutImageBorderProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "切边";
}

void CutImageBorderProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
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

    Mat tmp = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    tmp.copyTo(dest);
    qDebug() << info.selLeft << info.selTop << info.selWidth << info.selHeight;
}
