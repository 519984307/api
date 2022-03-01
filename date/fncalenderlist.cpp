#include "fncalenderlist.h"
#include "ui_fncalenderlist.h"

FnCalenderList::FnCalenderList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnCalenderList)
{
    ui->setupUi(this);
    setMouseTracking(true);
    initData();
    m_isShowLunar = true;
    m_rowHeight = 96;
    m_itemTop = 48;
    m_mousedownFlag = false;
}

FnCalenderList::~FnCalenderList()
{
    delete ui;
}

void FnCalenderList::initData()
{
    m_hasInit = false;
    m_date = QDate::currentDate();
    for (int i = 1900; i <= 2100; i++)
    {
        ui->cbbYear->addItem(QString("%1年").arg(i), i);

    }
    ui->cbbYear->setCurrentIndex(m_date.year() - 1900);
    for (int i = 1; i <= 12; i++)
    {
        ui->cbbMonth->addItem(QString("%1月").arg(i), i);
    }
    ui->cbbMonth->setCurrentIndex(m_date.month() - 1);
    m_hasInit = true;


}

QDate FnCalenderList::date() const
{
    return m_date;
}

void FnCalenderList::setDate(const QDate& date)
{
    m_date = date;
}

void FnCalenderList::changeDate()
{
    if (!m_hasInit)
    {
        return;
    }
    m_itemTop = 48;
    int y = ui->cbbYear->currentData(Qt::UserRole).toInt();
    int m = ui->cbbMonth->currentData(Qt::UserRole).toInt();
    m_date = QDate::fromString(QString("%1-%2-1").arg(y).arg(m), "yyyy-M-d");
    update();
}

void FnCalenderList::paintEvent(QPaintEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());
    QString weekNames[] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
    int w = width() / 7;
    int h = (height() - 96) / 6;

    QDate firstDay = m_date.addDays(-m_date.day() + 1);
    int n = firstDay.dayOfWeek() - 1;

    int days = m_date.daysInMonth();
    m_days = days;
    int k = 0;
    for (int i = 1; i <= days; i++)
    {
        QDate selDate, curDate;
        curDate = QDate::currentDate();
        selDate = QDate::fromString(QString("%1-%2-%3").arg(m_date.year()).arg(m_date.month()).arg(i), "yyyy-M-d");
        int ww = selDate.dayOfWeek();
        QRect dayRc = QRect(0, (i - 1) * m_rowHeight + m_itemTop, width(), m_rowHeight);
        if (dayRc.contains(pt))
        {
            painter.setBrush(QColor(203, 203, 204));

            painter.setPen(Qt::NoPen);
            painter.drawRect(dayRc);
            if (selDate == curDate)
            {
                painter.setPen(Qt::red);
            }
            else
            {
                painter.setPen(Qt::black);
            }

        }
        else
        {
            if (selDate == curDate)
            {
                painter.setPen(Qt::red);
            }
            else
            {
                painter.setPen(Qt::black);
            }
            painter.setBrush(Qt::white);
        }
        int ly, lm, ld;
        QString lunarDate =  GetLunarStringX(m_date.year(), m_date.month(), i, ly, lm, ld);
        QString lunarDay = getLunarDay(m_date.year(), m_date.month(), i);
        QRect textRc = QRect(dayRc.left() + 24, dayRc.top() + 4, dayRc.width(), 24);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, selDate.toString("yyyy-MM-dd") +
                         "      " + lunarDate + "        " + weekNames[ww - 1]);


        m_dateDatas[k].line = k;
        m_dateDatas[k].rc = dayRc;
        m_dateDatas[k].date = selDate;
        m_dateDatas[k].year = m_date.year();
        m_dateDatas[k].month = m_date.month();
        m_dateDatas[k].day = i;
        m_dateDatas[k].lunarDate = lunarDate;
        m_dateDatas[k].lunarDay = lunarDay;
        emit drawExtraInfo(painter, m_dateDatas[k]);
        painter.setPen(QColor(203, 203, 203));
        if (k == 0)
        {
            painter.drawLine(0, dayRc.top(), width(), dayRc.top());
        }
        painter.drawLine(0, dayRc.bottom(), width(), dayRc.bottom());
        k++;

    }


    painter.end();
}

void FnCalenderList::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    if (m_mousedownFlag)
    {
        int y = pt.y() - m_mousedownPoint.y();
        m_itemTop += y;
        m_mousedownPoint = pt;
        if (m_itemTop > 48)
        {
            m_itemTop = 48;
        }
        if (m_itemTop < -(m_days * m_rowHeight - height() + 64))
        {
            m_itemTop = -(m_days * m_rowHeight - height() + 64);
        }
        qDebug() << m_itemTop;
    }
    update();
}

void FnCalenderList::mousePressEvent(QMouseEvent* event)
{

    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    m_mousedownPoint = pt;
    m_mousedownFlag = true;
    for (int i = 0; i < 42; i++)
    {
        FnCalenderData data = m_dateDatas[i];
        if (data.rc.contains(pt))
        {
            emit cellClick(data);
        }

    }
}

void FnCalenderList::mouseReleaseEvent(QMouseEvent* event)
{
    m_mousedownFlag = false;
    update();

}

void FnCalenderList::on_btnPreMonth_clicked()
{
    if (ui->cbbMonth->currentIndex() - 1 >= 0)
    {
        ui->cbbMonth->setCurrentIndex(ui->cbbMonth->currentIndex() - 1);
    }
    else
    {
        ui->cbbYear->setCurrentIndex(ui->cbbYear->currentIndex() - 1);
        ui->cbbMonth->setCurrentIndex(11);

    }
    changeDate();
}

void FnCalenderList::on_btnNextMonth_clicked()
{
    if (ui->cbbMonth->currentIndex() + 1 <= 11)
    {
        ui->cbbMonth->setCurrentIndex(ui->cbbMonth->currentIndex() + 1);
    }
    else
    {
        ui->cbbYear->setCurrentIndex(ui->cbbYear->currentIndex() + 1);
        ui->cbbMonth->setCurrentIndex(0);

    }
    changeDate();
}

void FnCalenderList::on_cbbYear_currentIndexChanged(int index)
{
    changeDate();
}

void FnCalenderList::on_cbbMonth_currentIndexChanged(int index)
{
    changeDate();
}

int FnCalenderList::days() const
{
    return m_days;
}

void FnCalenderList::setDays(int days)
{
    m_days = days;
}

int FnCalenderList::itemTop() const
{
    return m_itemTop;
}

void FnCalenderList::setItemTop(int itemTop)
{
    m_itemTop = itemTop;
}

int FnCalenderList::rowHeight() const
{
    return m_rowHeight;
}

void FnCalenderList::setRowHeight(int rowHeight)
{
    m_rowHeight = rowHeight;
}

bool FnCalenderList::isShowLunar() const
{
    return m_isShowLunar;
}

void FnCalenderList::setIsShowLunar(bool isShowLunar)
{
    m_isShowLunar = isShowLunar;
}
