#include "rotateimageprocoperator.h"

RotateImageProcOperator::RotateImageProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "旋转";

}

void RotateImageProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    int code = info.code;
    if (code == 90)
    {
        cv::rotate(src, dest, ROTATE_90_CLOCKWISE);

    }
    else
    {
        if (code == -90)
        {
            cv::rotate(src, dest, ROTATE_90_COUNTERCLOCKWISE);
        }
        else if (code == 180)
        {
            cv::rotate(src, dest, ROTATE_180);
        }
    }

}
