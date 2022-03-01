#ifndef FNCALENDER_H
#define FNCALENDER_H

#include <QWidget>
#include <QDate>
#include <QPainter>
#include <QDebug>

#include "fncalenderbase.h"
namespace Ui
{
class FnCalender;
}


class FnCalender : public QWidget
{
    Q_OBJECT

public:
    explicit FnCalender(QWidget* parent = nullptr);
    ~FnCalender();
    void initData();

    QDate date() const;
    void setDate(const QDate& date);
    void changeDate();
    bool isShowLunar() const;
    void setIsShowLunar(bool isShowLunar);

signals:
    void drawExtraInfo(QPainter& painter, FnCalenderData& data);
    void cellClick(FnCalenderData& data);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private slots:
    void on_btnPreMonth_clicked();

    void on_btnNextMonth_clicked();

    void on_cbbYear_currentIndexChanged(int index);

    void on_cbbMonth_currentIndexChanged(int index);

private:
    Ui::FnCalender* ui;
    QDate m_date;
    bool m_hasInit;
    FnCalenderData m_dateDatas[42];
    bool m_isShowLunar;
};

#endif // FNCALENDER_H
