#ifndef GANTTTASK_H
#define GANTTTASK_H

#include <QObject>
#include <QMap>
#include <QDate>
#include <QRect>
#include <QColor>

class GanttTask : public QObject
{
    Q_OBJECT
public:
    explicit GanttTask(QObject* parent = nullptr);
    void setValue(QString key, QString value);
    QString value(QString key);
    const QDate& startDate() const;
    void setStartDate(const QDate& newStartDate);

    const QDate& endDate() const;
    void setEndDate(const QDate& newEndDate);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    const QRect& spanRect() const;
    void setSpanRect(const QRect& newSpanRect);

    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);

    const QString& showInfo() const;
    void setShowInfo(const QString& newShowInfo);

signals:
private:
    QMap<QString, QString> m_taskValues;
    QDate m_startDate;
    QDate m_endDate;
    QRect m_rect;
    QRect m_spanRect;
    QColor m_backgroundColor;
    QString m_showInfo;

};

#endif // GANTTTASK_H
