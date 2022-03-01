#ifndef FNCALENDERLIST_H
#define FNCALENDERLIST_H

#include <QWidget>
#include <QDate>
#include <QPainter>
#include <QDebug>
#include "lunar.h"
#include "fncalenderbase.h"
namespace Ui
{
class FnCalenderList;
}


class FnCalenderList : public QWidget
{
    Q_OBJECT

public:
    explicit FnCalenderList(QWidget* parent = nullptr);
    ~FnCalenderList();
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

signals:
    void drawExtraInfo(QPainter& painter, FnCalenderData& data);
    void cellClick(FnCalenderData& data);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void on_btnPreMonth_clicked();

    void on_btnNextMonth_clicked();

    void on_cbbYear_currentIndexChanged(int index);

    void on_cbbMonth_currentIndexChanged(int index);

private:
    Ui::FnCalenderList* ui;
    QDate m_date;
    bool m_hasInit;
    FnCalenderData m_dateDatas[42];
    bool m_isShowLunar;
    int m_rowHeight;
    int m_itemTop;
    QPoint m_mousedownPoint;
    bool m_mousedownFlag;
    int m_days;
};

#endif // FNCALENDER_H
