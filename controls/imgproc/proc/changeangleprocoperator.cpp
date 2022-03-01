#include "changeangleprocoperator.h"

ChangeAngleProcOperator::ChangeAngleProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "纠偏";
}

void ChangeAngleProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    double angle = info.Angle;
    if (angle < 0)
    {
        if (angle >= -90)
        {
            angle = -angle;
        }
        else
        {
            angle = -(angle + 180);
        }

    }
    else
    {
        if (angle <= 90)
        {
            angle =  - angle;
        }
        if (angle > 90)
        {
            angle = 180 - angle;
        }

    }

    qDebug() << angle;


    qDebug() << "纠偏" << angle;


    //// 旋转90度
    cv::Mat dst;
    cv::Point center(src.cols / 2, src.rows / 2); //旋转中心

    double scale = 1.0;  //缩放系数
    double tempAngle = abs(angle);
    int newWidth = src.cols * cos(tempAngle * (CV_PI / 180)) + src.rows * sin(tempAngle * (CV_PI / 180)) + 100;
    int newHeight = src.rows * cos(tempAngle * (CV_PI / 180)) + src.cols * sin(tempAngle * (CV_PI / 180)) + 100;
    qDebug() << newWidth << newHeight << src.cols << src.rows;
    copyMakeBorder(src, dest, (newHeight - src.rows) / 2,
                   (newHeight - src.rows) / 2, (newWidth - src.cols) / 2, (newWidth - src.cols) / 2,
                   BORDER_CONSTANT, Scalar(255, 255, 255));
    src = dest.clone();
    cv::Mat rotMat = getRotationMatrix2D(center, -angle, scale);
    cv::Size destSz(newWidth, newHeight);
    warpAffine(src, dest, rotMat, destSz, INTER_LINEAR,
               BORDER_CONSTANT, Scalar(255, 255, 255));





}
