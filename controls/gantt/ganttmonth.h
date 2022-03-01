#ifndef GANTTMONTH_H
#define GANTTMONTH_H

#include <QObject>
#include <QRect>

class GanttMonth : public QObject
{
    Q_OBJECT
public:
    explicit GanttMonth(QObject* parent = nullptr);

    void setYear(int newYear);

    void setMonth(int newMonth);

    int days() const;
    void setDays(int newDays);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    int year() const;

    int month() const;

signals:
private:
    int m_year;
    int m_month;
    int m_days;
    QRect m_rect;

};

#endif // GANTTMONTH_H
