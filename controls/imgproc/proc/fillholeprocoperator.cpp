#include "fillholeprocoperator.h"

FillHoleProcOperator::FillHoleProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "去孔洞";

}

void FillHoleProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    fillHole(src, info.pointX, info.pointY);
    dest = src;

}
void FillHoleProcOperator::fillHole(Mat& mat, int x, int y)
{
    int r;
    int g;
    int b;
    getColor(mat, x, y, r, g, b);
    if ((r + g + b) / 3 < 100)
    {
        setColor(mat, x, y, 254, 247, 197);
    }
    else
    {
        return;
    }
    if (x - 1 >= 0)
    {
        fillHole(mat, x - 1, y);
    }

    if ((x - 1 >= 0) && (y - 1 >= 0))
    {
        fillHole(mat, x - 1, y - 1);
    }

    if (y - 1 >= 0)
    {
        fillHole(mat, x, y - 1);
    }

    if ((x + 1 < (mat.cols)) && (y - 1 >= 0))
    {
        fillHole(mat, x + 1, y - 1);
    }
    if (x + 1 < (mat.cols))
    {
        fillHole(mat, x + 1, y);
    }
    if (y + 1 < (mat.rows))
    {
        fillHole(mat, x, y + 1);
    }
}
void FillHoleProcOperator::setColor(Mat& mat, int x, int y, int r, int g, int b)
{
    uchar* data = mat.ptr<uchar>(y);
    data[x * 3] = static_cast<uchar>(r);
    data[x * 3 + 1] = static_cast<uchar>(g);
    data[x * 3 + 2] = static_cast<uchar>(b);
}
void FillHoleProcOperator::getColor(Mat& mat, int x, int y, int& r, int& g, int& b)
{
    uchar* data = mat.ptr<uchar>(y);
    r = data[x * 3];
    g = data[x * 3 + 1];
    b = data[x * 3 + 2];
}
