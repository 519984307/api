#ifndef GANTTDAY_H
#define GANTTDAY_H

#include <QObject>
#include <QRect>

class GanttDay : public QObject
{
    Q_OBJECT
public:
    explicit GanttDay(QObject* parent = nullptr);

    int year() const;
    void setYear(int newYear);

    int month() const;
    void setMonth(int newMonth);

    int day() const;
    void setDay(int newDay);

    const QRect& rect() const;
    void setRect(const QRect& newRect);


    int weekDay() const;
    void setWeekDay(int newWeekDay);

signals:
private:
    int m_year;
    int m_month;
    int m_day;
    QRect m_rect;
    int m_weekDay;

};

#endif // GANTTDAY_H
