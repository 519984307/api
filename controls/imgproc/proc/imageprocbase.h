#ifndef IMAGEPROCBASE_H
#define IMAGEPROCBASE_H
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <QString>
#include <QObject>
#include <QColor>
#include <QDebug>
#include <vector>

using namespace cv;
using namespace std;
enum class ImageProcOperation
{
    IpoDrag,
    IPoDrawRect,
    IPoDrawLine,
    IPoPickColor,
    IPoDrawDot,
    IPoNone
};
enum class ImageShowState
{
    IsFitWidth,
    IsFitHeight,
    IsFit,
    IsShowOriginal,
    IsNone
};

struct ImagePoint
{
    int x;
    int y;
    int count;
    bool isHead;
    ImagePoint* headPoint;
    ImagePoint* prePoint;
    ImagePoint* nextPoint;
    ImagePoint* firstPoint;
    ImagePoint* tempPoint;
};

class ImageShortCut
{
public:
    QString Caption;
    QString KeyInfo;
    Qt::KeyboardModifiers mod;
    int key;
};
void RGB2LAB(int R, int G, int B, float& l, float& a, float& b);
void RGB2HSL(int R, int G, int B, float& H, float& S, float& L);
float max3v(float r, float g, float b);
float min3v(float r, float g, float b);
///创建Gmma表
void createLut(QList<unsigned char>& lut, float fGamma);
int QColorToInt(const QColor& color);
QColor IntToQColor(const int& intColor);
void HSL2RGB(float H, float S, float L, int& R, int& G, int& B);
double Hue2RGB(double v1, double v2, double vH);
uchar getLevelColor(uchar u);
uchar getLevelColors(uchar* colors);
double getGrayValue(Mat& imgData);
double getVarianceValue(Mat& imgData);
///将文件存储为300Dpi
bool setResolution(QString path, int iResolution);
void saveMatToFile(Mat& imgData, QString allfilepath);
bool loadMatFromFile(Mat& imgData, QString allfilepath);
double getAngle(double x1, double y1, double x2, double y2);
bool hasRedColor(Mat imgData);
uchar get16Color(uchar u);
void removeStains(Mat& imgData, int x, int y, int w, int h, int stainWidth);
inline bool isHdBackColor(int r, int g, int b);
void getPickColor(Mat& mat, int x, int y, int& r, int& g, int& b);
#endif // IMAGEVIEWCORE_H
