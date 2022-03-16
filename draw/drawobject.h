#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QObject>
#include <QPainter>
#include <math.h>
#include <QtMath>
#include <QDebug>
enum DrawObjectRectStyle
{
    DrawLeft,
    DrawRight,
    DrawNone
};

class DrawObject : public QObject
{
    Q_OBJECT
public:
    explicit DrawObject(QObject* parent = nullptr);
    void reSetPoints(QPoint& pt1, QPoint& pt2);
    int pointsXDistance(QPoint& pt1, QPoint& pt2);
    int pointsYDistance(QPoint& pt1, QPoint& pt2);
    int distance(QPoint pt1, QPoint pt2);
    double distanced(QPoint pt1, QPoint pt2);
    void drawRect(QPainter& painter, QPoint& pt1, QPoint& pt2);
    void drawRect(QPainter& painter, QRectF rect, bool drawLeft, bool drawTop, bool drawRight, bool drawBottom);
    void drawRect(QPainter& painter, int startX, int startY, QRect rc);
    void drawRect(QPainter& painter, int startX, int startY, QPoint center, int width, int height);
    void drawPixmap(QPainter& painter, int startX, int startY, QRect rc, QPixmap& pix);
    void drawPixmap(QPainter& painter, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawPixmap(QPainter& painter, double angle, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2);
    void drawLines(QPainter& painter, QVector<QPoint>& points);

    bool pointInLine(QPoint pt1, QPoint pt2, QPoint pt);
    void drawStraightLine(QPainter& painter, QPoint& pt1, QPoint pt2);
    QPoint getStraightLineEndPoint(QPoint& pt1, QPoint pt2);
    QPoint getTwoPointsCenter(QPoint& pt1, QPoint pt2);

    bool rectContainsPoint(int startX, int startY, QRect& rc, QPoint& pt);
    bool pointInLine(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt);
    bool pointInLined(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt);
    int rectAreaSize(QRect& rect);
    void resetRect(QRect& rc, QPoint center, int width, int height);
    double radianToAngle(double d);
    double angleToRadian(double d);
    QRect getRect(QPoint pt1, QPoint pt2);
    double getLineRadian(QPoint pt1, QPoint pt2);
    double getLineAngle(QPoint pt1, QPoint pt2);

    //绘制原点坐标系
    void drawOriginCross(QPainter& painter, QPoint& centerPoint, QRect& clientRect);


    ///绘制从左向右黄金螺旋线
    void drawLeftGoldSpiral(QPainter& painter, QPoint startPt, int width);

    ///绘制正方形
    void drawSquare(QPainter& painter, QPoint startPoint, int w);

    ///绘制关闭按钮
    void drawCloseButton(QPainter& painter, QRect rc, QColor color, int margin = 4);

    ///绘制关闭按钮
    void drawBackButton(QPainter& painter, QRect rc, QColor color, int penWidth = 1, int margin = 0);

    ///绘制关闭按钮
    void drawAddButton(QPainter& painter, QRect rc, QColor color, int penWidth = 1, int margin = 8);

    ///绘制圆形按钮
    void drawRoundRect(QPainter& painter, QRect rc, QColor color, DrawObjectRectStyle drawStyle);

signals:

private:



};

#endif // DRAWOBJECT_H
