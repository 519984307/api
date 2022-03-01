#ifndef FNCLOCKWIDGET_H
#define FNCLOCKWIDGET_H

#include <QWidget>
#include "../base/widgethelper.h"
#include <QPainter>
#include <math.h>
#include <qmath.h>
#include "../../draw/drawobject.h"
#include "fnclockwidgetpointer.h"
#include <QTime>
#include <QTimer>

namespace Ui
{
class FnClockWidget;
}

class FnClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FnClockWidget(QWidget* parent = nullptr);
    ~FnClockWidget();
    int hour() const;
    void setHour(int hour);

    int minute() const;
    void setMinute(int minute);

    int second() const;
    void setSecond(int second);

    FnClockWidgetPointer* hourPointer() const;
    void setHourPointer(FnClockWidgetPointer* hourPointer);

    FnClockWidgetPointer* minutePointer() const;
    void setMinutePointer(FnClockWidgetPointer* minutePointer);

    FnClockWidgetPointer* secondPointer() const;
    void setSecondPointer(FnClockWidgetPointer* secondPointer);

    bool getAlwaysShowCurrentTime() const;
    void setAlwaysShowCurrentTime(bool value);
    QPixmap getBackGround() const;
    void setBackGround(const QPixmap& backGround);

public slots:
    void onTimerTimeOut();
protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::FnClockWidget* ui;
    WidgetHelper* m_helper;
    DrawObject* m_drawObj;
    FnClockWidgetPointer* m_hourPointer;
    FnClockWidgetPointer* m_minutePointer;
    FnClockWidgetPointer* m_secondPointer;
    QTime m_clockTime;
    bool m_alwaysShowCurrentTime;
    QTimer* m_timer;
    QPixmap m_backGround;

};

#endif // FNCLOCKWIDGET_H
