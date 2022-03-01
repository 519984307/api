#include "autocutborderprocoperator.h"

AutoCutBorderProcOperator::AutoCutBorderProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "自动切边";
}

void AutoCutBorderProcOperator::findROI(Mat& src, Mat& dest)
{

    Mat gray;
    cvtColor(src, gray, COLOR_RGB2GRAY);      //将原图转化为灰度图
    Mat canny_output;
    Canny(gray, canny_output, threshold_value, threshold_value * 2, 3, false);                // canny边缘检测

    vector<vector<Point>> contours;
    vector<Vec4i> hireachy;
    findContours(canny_output, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));    // 调用API，找到轮廓

    // 筛选contours中的轮廓，我们需要最大的那个轮廓
    int min_width = src.cols * 0.75;        // 矩形的最小宽度
    int min_height = src.rows * 0.75;       // 矩形的最小高度
    RNG rng(12345);                            //定义一个随机数产生器，用来产生不同颜色的矩形框
    Mat drawImage = Mat::zeros(src.size(), CV_8UC3);
    Rect bbox;
    for (auto t = 0; t < contours.size(); ++t)       // 遍历每一个轮廓
    {
        RotatedRect minRect = minAreaRect(contours[t]);        // 找到每一个轮廓的最小外包旋转矩形，RotatedRect里面包含了中心坐标、尺寸以及旋转角度等信息
        float degree = abs(minRect.angle);                    // 最小外包旋转矩形的旋转角度
        if (minRect.size.width > min_width && minRect.size.height > min_height && minRect.size.width < (src.cols - 5))   //筛选最小外包旋转矩形
        {
            printf("current angle : %f\n", degree);
            Mat vertices;       // 定义一个4行2列的单通道float类型的Mat，用来存储旋转矩形的四个顶点
            boxPoints(minRect, vertices);    // 计算旋转矩形的四个顶点坐标
            bbox = boundingRect(vertices);   //找到输入点集的最小外包直立矩形，返回Rect类型
            cout << "最小外包矩形：" << bbox << endl;
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));   //产生随机颜色
            for (int i = 0; i < 4; i++)             // 遍历每个旋转矩形的四个顶点坐标
            {
                // 在相邻的顶点之间绘制直线
                Mat p1 = vertices.row(i); // 使用成员函数row(i)和col(j)得到矩阵的第i行或者第j列，返回值仍然是一个单通道的Mat类型
                int j = (i + 1) % 4;
                Mat p2 = vertices.row(j);
                Point p1_point = Point(p1.at<float>(0, 0), p1.at<float>(0, 1)); //将Mat类型的顶点坐标转换为Point类型
                Point p2_point = Point(p2.at<float>(0, 0), p2.at<float>(0, 1));
                line(drawImage, p1_point, p2_point, color, 2, 8, 0);    // 根据得到的四个顶点，通过连接四个顶点，将最小旋转矩形绘制出来
            }
        }
    }


    if (bbox.width > 0 && bbox.height > 0)
    {
        Mat roiImg = src(bbox);        //从原图中截取兴趣区域


        dest = roiImg.clone();
    }
    else
    {
        dest = src.clone();
    }

    return;


}



void AutoCutBorderProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{




    findROI(src, dest);




}
