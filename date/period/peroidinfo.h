#ifndef PEROIDINFO_H
#define PEROIDINFO_H

#include <QObject>
#include <QDateTime>

class PeroidInfo : public QObject
{
    Q_OBJECT
public:
    explicit PeroidInfo(QObject* parent = nullptr);

    int startYear() const;
    void setStartYear(int newStartYear);

    int startMonth() const;
    void setStartMonth(int newStartMonth);

    int startDay() const;
    void setStartDay(int newStartDay);

    int startHour() const;
    void setStartHour(int newStartHour);

    int startMinute() const;
    void setStartMinute(int newStartMinute);

    int endYear() const;
    void setEndYear(int newEndYear);

    int endMonth() const;
    void setEndMonth(int newEndMonth);

    int endDay() const;
    void setEndDay(int newEndDay);

    int endHour() const;
    void setEndHour(int newEndHour);

    int endMinute() const;
    void setEndMinute(int newEndMinute);

    QString info() const;
    void setInfo(QString newInfo);

    bool timeInRange(int hour, int minute);
    static bool timeInRange(int hour, int minute, int hour1, int minute1, int hour2, int minute2);
    bool timeInRange();
    void setRangeInfo(QTime startTime, QTime endTime, QString info);
    QTime startTime();
    QTime endTime();
signals:
private:
    int m_startYear;
    int m_startMonth;
    int m_startDay;
    int m_startHour;
    int m_startMinute;
    int m_endYear;
    int m_endMonth;
    int m_endDay;
    int m_endHour;
    int m_endMinute;
    QString m_info;

};

#endif // PEROIDINFO_H
