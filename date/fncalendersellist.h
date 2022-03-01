#ifndef FNCALENDERSELLIST_H
#define FNCALENDERSELLIST_H

#include <QWidget>
#include <QDate>
#include <QPainter>
#include <QDebug>
#include "lunar.h"
#include "fncalenderbase.h"
namespace Ui
{
class FnCalenderSelList;
}


class FnCalenderSelList : public QWidget
{
    Q_OBJECT

public:
    explicit FnCalenderSelList(QWidget* parent = nullptr);
    ~FnCalenderSelList();
    void initData();

    QDate date() const;
    void setDate(const QDate& date);
    void changeDate();
    bool isShowLunar() const;
    void setIsShowLunar(bool isShowLunar);

    int rowHeight() const;
    void setRowHeight(int rowHeight);

    int itemTop() const;
    void setItemTop(int itemTop);

    int days() const;
    void setDays(int days);
    QList<FnCalenderData> m_dateDatas;
    void addData(FnCalenderData& data);
    void clearData();
signals:
    void drawExtraInfo(QPainter& painter, FnCalenderData& data);
    void cellClick(FnCalenderData& data);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:


private:
    Ui::FnCalenderSelList* ui;
    QDate m_date;
    bool m_hasInit;

    bool m_isShowLunar;
    int m_rowHeight;
    int m_itemTop;
    QPoint m_mousedownPoint;
    bool m_mousedownFlag;
    int m_days;
};

#endif // FNCALENDER_H
