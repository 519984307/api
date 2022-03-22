#include "pickredcolorprocoperator.h"

PickRedColorProcOperator::PickRedColorProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "取红色";


}

void PickRedColorProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    Mat hsv = dest.clone();
    cvtColor(src, hsv, COLOR_RGB2HSV);
    cv::Mat lower_red_hue_range;
    cv::Mat upper_red_hue_range;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
    cv::inRange(hsv, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);
    cv::Mat mask;
    cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, mask);

    cv::Mat ret;
    src.copyTo(ret, mask);
    dest = ret(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));

}
