#include "removemixcolorprocoperator.h"

RemoveMixColorProcOperator::RemoveMixColorProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "去杂色";

}

void RemoveMixColorProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
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


    Mat roi = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    qDebug() << info.pickColorR << info.pickColorG << info.pickColorB;

    for (int j = 0; j < roi.rows; j++)
    {
        uchar* data = roi.ptr<uchar>(j);
        for (int i = 0; i < roi.cols; i++)
        {
            if ((abs(info.pickColorR - data[ i * 3]) <= info.colorRange) &&
                (abs(info.pickColorG - data[ i * 3 + 1]) <= info.colorRange) &&
                (abs(info.pickColorB - data[ i * 3 + 2]) <= info.colorRange))

            {
                data[ i * 3] = 255;
                data[ i * 3 + 1] = 255;
                data[i * 3 + 2] = 255;
            }
        }
    }

    dest = src;

}
