#include "makehdimageprocoperator.h"

MakeHdImageProcOperator::MakeHdImageProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "高清优化";

}

void MakeHdImageProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src.clone();
    bool f = hasRedColor(src);
    int n = getGrayValue(dest);
    double v = getVarianceValue(dest);
    if ((n >= 240) && (f == false) && (v < 1000))
    {
        uchar colors[256];
        getLevelColors(colors);
        for (int j = 0; j < dest.rows; j++)
        {
            uchar* data = dest.ptr<uchar>(j);
            for (int i = 0; i < dest.cols; i++)
            {
                data[i * 3] = colors[data[i * 3]];
                data[i * 3 + 1] = colors[data[i * 3 + 1]];
                data[i * 3 + 2] = colors[data[i * 3 + 2]];
            }
        }
    }
    Mat tempData;
    cvtColor(dest, tempData, COLOR_RGB2GRAY);
    if ((n > 240) && (v < 300))
    {
        threshold(tempData, tempData, 240, 255, THRESH_BINARY);
    }
    else if ((n > 240) && (v < 1000))
    {
        threshold(tempData, tempData, info.thresholdValue, 255, THRESH_BINARY);
    }
    else if (info.autoThresholdValue)
    {
        threshold(tempData, tempData, info.thresholdValue, 255, THRESH_BINARY | THRESH_OTSU);

    }
    else
    {
        threshold(tempData, tempData, info.thresholdValue, 255, THRESH_BINARY);
    }

    bitwise_not(tempData, tempData);
    floodFill(tempData, Point(3, 3), Scalar(0, 0, 0), 0, Scalar(0, 0, 0), Scalar(0, 0, 0));
    bitwise_not(tempData, tempData);

    QList<unsigned char> lut;
    createLut(lut, info.gammaValue);
    for (int j = 0; j < tempData.rows; j++)
    {
        uchar* data = dest.ptr<uchar>(j);
        uchar* data2 = tempData.ptr<uchar>(j);

        for (int i = 0; i < tempData.cols; i++)
        {
            if (data2[i] == 255)
            {
                data[i * 3] = 254;
                data[i * 3 + 1] = 247;
                data[i * 3 + 2] = 197;
            }
            else
            {
                int r = data[i * 3];
                int g = data[i * 3 + 1];
                int b = data[i * 3 + 2];
                data[i * 3] = lut.at(r);
                data[i * 3 + 1] = lut.at(g);
                data[i * 3 + 2] = lut.at(b);
                r = data[i * 3];
                g = data[i * 3 + 1];
                b = data[i * 3 + 2];
                float h;
                float s;
                float l;
                if ((abs(r - b) <= 20) && (abs(r - g) <= 20) && (abs(b - g) <= 20) && (r < 128) && (g < 128) && (b < 128))
                {
                    RGB2HSL(r, g, b, h, s, l);
                    l = l * 0.1;
                    HSL2RGB(h, s, l, r, g, b);

                    data[i * 3] = r;
                    data[i * 3 + 1] = g;
                    data[i * 3 + 2] = b;
                }
            }
        }
    }
    Mat d1;
    cvtColor(dest, d1, COLOR_RGB2BGR);
    imwrite(QString("d:\\aaa.jpg").toLocal8Bit().data(), d1);
}

