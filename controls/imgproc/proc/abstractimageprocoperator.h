#ifndef ABSTRACTIMAGEPROCOPERATOR_H
#define ABSTRACTIMAGEPROCOPERATOR_H

#include <QObject>
#include <QRect>
#include "../api/opencv/include/opencv2/opencv.hpp"
#include "imageprocbase.h"
#include <QDebug>
using namespace cv;
struct ImageProcInfo
{
    QRect rc;
    int code;
    int imgLeft;
    int imgTop;
    double factor;
    QPoint m_startViewPoint;
    QPoint m_endViewPoint;
    int selLeft;
    int selTop;
    int selWidth;
    int selHeight;
    double gammaValue = 2;
    bool autoThresholdValue = true;
    int thresholdValue = 128;
    double Angle;
    QPoint startPoint;
    QPoint endPoint;
    int colorR = 255;
    int colorG = 255;
    int colorB = 255;
    int pickColorR = 255;
    int pickColorG = 255;
    int pickColorB = 255;
    int colorRange = 10;
    int pointX;
    int pointY;

};

class AbstractImageProcOperator : public QObject
{
    Q_OBJECT
public:
    explicit AbstractImageProcOperator(QObject* parent = nullptr);
    const QString& name() const;
    void setName(const QString& newName);
    virtual void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
protected:
    QString m_name;


signals:

};

#endif // ABSTRACTIMAGEPROCOPERATOR_H
