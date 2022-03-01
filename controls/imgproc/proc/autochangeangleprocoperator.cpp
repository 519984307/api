#include "autochangeangleprocoperator.h"

AutoChangeAngleProcOperator::AutoChangeAngleProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "自动纠偏";

}

void AutoChangeAngleProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    if (src.empty())
        return;
    int angle = getImageAngle(src);
    rotateImgDataByCenter(src, dest, angle);

}
double AutoChangeAngleProcOperator::getImageAngle(Mat& mat)
{
    Mat src = mat.clone();
    Mat gray, canny;
    cvtColor(src, gray, COLOR_RGB2GRAY);
    threshold(gray, gray, 0, 256, THRESH_BINARY | THRESH_OTSU);
    Canny(gray, canny, 0, 1);

    vector<Vec4i> lines;
    HoughLinesP(canny, lines, 1, CV_PI / 180, 20, 20, 600);
    QMap<int, int> angles;
    for (int i = 0; i <= 360; i++)
    {
        angles.insert(i, 0);
    }
    for (int i = 0; i < lines.size(); i++)
    {
        Vec4i I = lines[i];
        int angle = getAngle(I[0], I[1], I[2], I[3]);

        int n = angles[angle];
        n++;
        angles[angle] = n;
    }
    return getAngleFromAngles(angles);
}
double AutoChangeAngleProcOperator::getAngleFromAngles(QMap<int, int>& angles)
{
    int n = 0;
    int num = -1;
    QMapIterator<int, int> i(angles);
    while (i.hasNext())
    {
        i.next();
        int m = i.value();
        if (m > num)
        {
            n = i.key();
            num = m;
        }
    }
    return n;
}

void AutoChangeAngleProcOperator::rotateImgDataByCenter(Mat& src, Mat& dest, int angle)
{
    Mat destData;
    double tempAngle = angle;
    if (tempAngle > 180)
    {
        tempAngle = abs(tempAngle - 360);
    }
    int newWidth = src.cols * cos(tempAngle * (CV_PI / 180)) + src.rows * sin(tempAngle * (CV_PI / 180)) + 100;
    int newHeight = src.rows * cos(tempAngle * (CV_PI / 180)) + src.cols * sin(tempAngle * (CV_PI / 180)) + 100;
    copyMakeBorder(src, destData, (newHeight - src.rows) / 2,
                   (newHeight - src.rows) / 2, (newWidth - src.cols) / 2, (newWidth - src.cols) / 2,
                   BORDER_CONSTANT, Scalar(255, 255, 255));
    dest = destData.clone();

    cv::Size srcSz = dest.size();
    cv::Size destSz(srcSz.width, srcSz.height);
    int px = dest.cols / 2;
    int py = dest.rows / 2;
    cv::Point2f center(px, py);
    cv::Mat rotMat = cv::getRotationMatrix2D(center, -angle, 1.0);

    cv::warpAffine(dest, dest, rotMat, destSz, INTER_LINEAR,
                   BORDER_CONSTANT, Scalar(255, 255, 255));


}
