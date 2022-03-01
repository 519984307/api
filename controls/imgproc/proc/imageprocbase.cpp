#include "imageprocbase.h"
#include <QDir>
#include <stdio.h>
#include <string.h>

void RGB2LAB(int R, int G, int B, float& l, float& a, float& b)
{
    l = 0.412453f * R + 0.357580f * G + 0.180423f * B;
    a = 0.212671f * R + 0.715160f * G + 0.072169f * B;
    b = 0.019334f * R + 0.119193f * G + 0.950227f * B;
}
void RGB2HSL(int R, int G, int B, float& H, float& S, float& L)
{

    // normalizes red-green-blue values
    float r = R / 255.f;
    float g = G / 255.f;
    float b = B / 255.f;
    float maxVal = max3v(r, g, b);
    float minVal = min3v(r, g, b);
    float h = 0, s = 0, l = 0;
    ///////////////////////////// hue////////////////
    if (qFuzzyCompare(maxVal, minVal))
    {
        h = 0; // undefined
    }
    else if (qFuzzyCompare(maxVal, r) && g >= b)
    {
        h = 60.0f * (g - b) / (maxVal - minVal);
    }
    else if (qFuzzyCompare(maxVal, r) && g < b)
    {
        h = 60.0f * (g - b) / (maxVal - minVal) + 360.0f;
    }
    else if (qFuzzyCompare(maxVal, g))
    {
        h = 60.0f * (b - r) / (maxVal - minVal) + 120.0f;
    }
    else if (qFuzzyCompare(maxVal, b))
    {
        h = 60.0f * (r - g) / (maxVal - minVal) + 240.0f;
    }

    ////////////////////// luminance //////////////////
    l = (maxVal + minVal) / 2.0f;

    ///////////////////////// saturation ////////////////
    if (l == 0 || maxVal == minVal)
    {
        s = 0;
    }
    else if (0 < l && l <= 0.5f)
    {
        s = (maxVal - minVal) / (maxVal + minVal);
    }
    else if (l > 0.5f)
    {
        s = (maxVal - minVal) / (2 - (maxVal + minVal)); //(maxVal-minVal > 0)?
    }
    float hue = (h > 360) ? 360 : ((h < 0) ? 0 : h);
    float saturation = ((s > 1) ? 1 : ((s < 0) ? 0 : s)) * 100;
    float luminance = ((l > 1) ? 1 : ((l < 0) ? 0 : l)) * 100;

    H = 240 * hue / 360.f;
    S = 240 * saturation / 100.f;
    L = 240 * luminance / 100.f;
}
float max3v(float r, float g, float b)
{
    float m;
    if (r > g)
    {
        m = r;
    }
    else
    {
        m = g;
    }
    if (b > m)
    {
        m = b;
    }
    return m;
}

float min3v(float r, float g, float b)
{
    float m;
    if (r < g)
    {
        m = r;

    }
    else
    {
        m = g;
    }
    if (b < m)
    {
        m = b;
    }
    return m;
}
void createLut(QList<unsigned char>& lut, float fGamma)

{

    if (fGamma == 0)
    {
        for (int i = 0; i < 256; i++)

        {

            unsigned char n = i;
            lut.append(n);
        }
    }
    else
    {
        for (int i = 0; i < 256; i++)

        {

            unsigned char n = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
            lut.append(n);
        }
    }
}
int QColorToInt(const QColor& color)
{
    //将Color 从QColor 转换成 int<br />
    return (int)(((unsigned int)color.blue() << 16) | (unsigned short)(((unsigned short)color.green() << 8) | color.red()));
}
QColor IntToQColor(const int& intColor)
{
    //将Color 从int 转换成 QColor<br />
    int red = intColor & 255;
    int green = intColor >> 8 & 255;
    int blue = intColor >> 16 & 255;
    return QColor(red, green, blue);
}
void HSL2RGB(float H, float S, float L, int& R, int& G, int& B)
{

    H = H / 240;
    S = S / 240;
    L = L / 240;
    double var_1, var_2;
    if (qFuzzyCompare(S, 0)) //HSL values = 0 ÷ 1
    {
        R = L * 255.0; //RGB results = 0 ÷ 255
        G = L * 255.0;
        B = L * 255.0;
    }
    else
    {
        if (L < 0.5)
            var_2 = L * (1 + S);
        else
            var_2 = (L + S) - (S * L);

        var_1 = 2.0 * L - var_2;

        R = 255.0 * Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
        G = 255.0 * Hue2RGB(var_1, var_2, H);
        B = 255.0 * Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
    }
}
double Hue2RGB(double v1, double v2, double vH)
{
    if (vH < 0)
        vH += 1;
    if (vH > 1)
        vH -= 1;
    if (6.0 * vH < 1)
        return v1 + (v2 - v1) * 6.0 * vH;
    if (2.0 * vH < 1)
        return v2;
    if (3.0 * vH < 2)
        return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
    return (v1);
}
uchar getLevelColor(uchar u)
{

    double d = u;
    d = d / 255;
    d = pow(d, 1 / 0.2) * 255;
    u = static_cast<uchar>(d);
    if ((u - '0') < 0)
    {
        u = 0;
    }
    else if ((u - '0') > 255)
    {
        u = 255;
    }

    return u;
}

uchar getLevelColors(uchar* colors)
{
    for (int i = 0; i < 256; i++)
    {
        colors[i] = getLevelColor(i);
    }
    return colors[0];
}
double getGrayValue(Mat& imgData)
{
    double n = 0;
    int m = 0;
    for (int j = 0; j < imgData.rows; j++)
    {
        uchar* data = imgData.ptr<uchar>(j);
        for (int i = 0; i < imgData.cols; i++)
        {
            n = n + 0.11 * data[i * 3] + 0.59 * data[i * 3 + 1] + 0.3 * data[i * 3 + 2];
            m = m + 1;
        }
    }
    if (m != 0)
    {
        n = n / m;
    }
    return n;
}
double getVarianceValue(Mat& imgData)
{
    double d = getGrayValue(imgData);
    double n = 0;
    int m = 0;
    for (int j = 0; j < imgData.rows; j++)
    {
        uchar* data = imgData.ptr<uchar>(j);
        for (int i = 0; i < imgData.cols; i++)
        {
            double v = 0.11 * data[i * 3] + 0.59 * data[i * 3 + 1] + 0.3 * data[i * 3 + 2];
            n = n + (v - d) * (v - d);
            m = m + 1;
        }
    }
    if (m != 0)
    {
        n = n / m;
    }
    return n;
}
bool setResolution(QString path, int iResolution)
{
    FILE* pFile;
    size_t lSize;
    char* buffer;
    size_t result;
    char* pPath = path.toLocal8Bit().data();
    pFile = fopen(pPath, "rb+");
    if (pFile == nullptr)
    {
        //        fclose(pFile);
        return false;
    }
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);
    buffer = (char*)malloc(sizeof(char) * lSize);
    if (buffer == nullptr)
    {
        free(buffer);
        fclose(pFile);
        return false;
    }
    result = fread(buffer, 1, lSize, pFile);
    qDebug() << result << endl;
    char* pResolution = (char*)&iResolution; // - iResolution为要设置的分辨率的数值，如72dpi
    // - 设置JPG图片的分辨率
    buffer[0x0D] = 1; // - 设置使用图片密度单位
    // - 水平密度，水平分辨率
    buffer[0x0E] = pResolution[1];
    buffer[0x0F] = pResolution[0];
    // - 垂直密度，垂直分辨率
    buffer[0x10] = pResolution[1];
    buffer[0x11] = pResolution[0];

    // - 将文件指针移动回到文件开头
    fseek(pFile, 0, SEEK_SET);
    // - 将数据写入文件，覆盖原始的数据，让修改生效
    fwrite(buffer, 1, lSize, pFile);

    fclose(pFile);
    free(buffer);
    return true;
}

void saveMatToFile(Mat& imgData, QString allfilepath)
{
//    if (allfilepath == "")
//        return;
//    QFileInfo fileInfo(allfilepath);
//    if (!fileInfo.exists())
//    {
//        QDir dir;
//        dir.mkpath(fileInfo.path());
//    }
//    Mat mat;
//    if (imgData.empty())
//        return;
//    cvtColor(imgData, mat, COLOR_RGB2BGR);
//    imwrite(allfilepath.toLocal8Bit().data(), mat);
//    setResolution(allfilepath, 300);
//    imwrite(QString("d:/a.jpg").toLocal8Bit().data(), mat);
//#ifdef QT_USE_UMSP_CryptCore
//    if (!QArchScanGlobal::umspCryptCore->u_encryptFileSelf(allfilepath, HXAESkey1 + HXAESkey3 + HXAESkey2))
//    {
//        return;
//    }
//#endif
//#ifdef QT_USE_AES
//    HasngAES::EncodeFile_ecb128(HXAESkey1 + HXAESkey3 + HXAESkey2, allfilepath, allfilepath);
//#endif
//    FilesControl::CopyFileToCache(allfilepath);
}
bool loadMatFromFile(Mat& imgData, QString allfilepath)
{
    QFile srcFile(allfilepath);
    if (!srcFile.exists())
    {
        return false;
    }

#ifdef QT_USE_UMSP_CryptCore
    //临时解密用完删除
    QString timestamp = QArchScanGlobal::DataBase.CreateGuid();
    QString lunaesAllFilePath = qApp->applicationDirPath() + "/scantmp/unaes" + timestamp + ".jpg";
    QDir dir(qApp->applicationDirPath() + "/scantmp");
    if (!dir.exists())
    {
        if (!dir.mkpath(qApp->applicationDirPath() + "/scantmp"))
            return false;
    }
    if (!QArchScanGlobal::umspCryptCore->u_decryptFile(allfilepath, lunaesAllFilePath, HXAESkey1 + HXAESkey3 + HXAESkey2))
    {
        return false;
    }
    imgData = imread(lunaesAllFilePath.toLocal8Bit().data(), IMREAD_COLOR);
    //    QFile file(lunaesAllFilePath);
    //    if (file.exists()) {
    //        file.remove();
    //    }

#endif
#ifdef QT_USE_AES
    //临时解密用完删除
    QString timestamp = QArchScanGlobal::DataBase.CreateGuid();
    QString lunaesAllFilePath = qApp->applicationDirPath() + "/scantmp/unaes" + timestamp + ".jpg";
    QDir dir(qApp->applicationDirPath() + "/scantmp");
    if (!dir.exists())
    {
        if (!dir.mkpath(qApp->applicationDirPath() + "/scantmp"))
            return false;
    }
    if (!HasngAES::DecodeFile_ecb128(HXAESkey1 + HXAESkey3 + HXAESkey2, allfilepath, lunaesAllFilePath))
    {
        return false;
    }
    imgData = imread(lunaesAllFilePath.toLocal8Bit().data(), IMREAD_COLOR);
    QFile file(lunaesAllFilePath);
    if (file.exists())
    {
        file.remove();
    }
#endif
#ifdef QT_USE_NO_EncDec
    imgData = imread(allfilepath.toLocal8Bit().data(), IMREAD_COLOR);
#endif
    if (imgData.empty())
        return false;
    cvtColor(imgData, imgData, COLOR_BGR2RGB);
    return true;
}
double getAngle(double x1, double y1, double x2, double y2)
{
    double x = fabs(x2 - x1);
    double y = fabs(y2 - y1);
    double r = sqrt(x * x + y * y);
    double angle = asin(y / r) * (180 / CV_PI);
    if (y2 < y1)
    {
        if (x2 < x1)
        {
            angle = 180 - angle;
        }
    }
    else if (y2 > y1)
    {
        if (x2 < x1)
        {
            angle = 180 + angle;
        }
        else
        {
            angle = 360 - angle;
        }
    }
    return angle;
}
bool hasRedColor(Mat imgData)
{
    Mat ret = imgData.clone();
    int n = 0;
    for (int j = 0; j < ret.rows; j++)
    {
        uchar* data = ret.ptr<uchar>(j);
        for (int i = 0; i < ret.cols; i++)
        {
            uchar r = get16Color(data[i * 3]);
            uchar g = get16Color(data[i * 3 + 1]);
            uchar b = get16Color(data[i * 3 + 2]);
            if ((r > ((g + b) / 2)) && (g < ((r + b) / 2)) && (b < ((r + g) / 2)) && (r > 128))
            {
                n = n + 1;
            }
        }
    }
    return n > 0;
}
uchar get16Color(uchar u)
{
    if (u <= 32)
    {
        u = 0;
    }
    else if ((u > 32) && (u <= 96))
    {
        u = 64;
    }
    else if ((u > 96) && (u <= 160))
    {
        u = 128;
    }
    else if ((u > 160) && (u <= 224))
    {
        u = 192;
    }

    else
    {
        u = 255;
    }
    return u;
}
void removeStains(Mat& imgData, int x, int y, int w, int h, int stainWidth)
{

    // Declares a vector of vectors for store the contours
    Mat originalimage;

    // Loads the original image
    Rect rc;
    rc.x = x;
    rc.y = y;
    rc.width = w;
    rc.height = h;
    originalimage = imgData(rc);
    Mat image = Mat(originalimage.rows, originalimage.cols, CV_8UC1);
    for (int j = 0; j < image.rows; j++)
    {
        uchar* src = originalimage.ptr<uchar>(j);
        uchar* dest = image.ptr<uchar>(j);
        for (int i = 0; i < image.cols; i++)
        {
            if (isHdBackColor(src[i * 3], src[i * 3 + 1], src[i * 3 + 2]))
            {
                dest[i] = 255;
            }
            else
            {
                dest[i] = 0;
            }
        }
    }

    // Finds contours
    vector<vector<Point>> v;
    vector<Vec4i> hierarchy;
    Rect rect;
    findContours(image, v, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
    for (int i = 0; i < int(hierarchy.size()); i++)
    {
        rect = boundingRect(v.at(size_t(i)));

        // 画最小的圆，贴着黑色
        if ((rect.width <= stainWidth) && (rect.height <= stainWidth))
        {
            if ((rect.width > 0) && (rect.height > 0)
                && (rect.x >= 0) && (rect.y >= 0)
                && ((rect.x + rect.width) < originalimage.cols)
                && ((rect.y + rect.height) < originalimage.rows) && (rect.empty() == false))
            {

                Mat tmp = originalimage(rect);

                for (int n = 0; n < tmp.rows; n++)
                {
                    uchar* data = tmp.ptr<uchar>(n);
                    for (int m = 0; m < tmp.cols; m++)
                    {

                        data[m * 3] = 254;
                        data[m * 3 + 1] = 247;
                        data[m * 3 + 2] = 197;
                    }
                }
            }
        }
    }




}
inline bool isHdBackColor(int r, int g, int b)
{
    int r0 = abs(r - 254);
    int g0 = abs(g - 247);
    int b0 = abs(b - 197);
    if ((r0 <= 10) && (g0 <= 10) && (b0 <= 10))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getPickColor(Mat& mat, int x, int y, int& r, int& g, int& b)
{
    uchar* data = mat.ptr<uchar>(y);
    r = data[x * 3];
    g = data[x * 3 + 1];
    b = data[x * 3 + 2 ];
}
