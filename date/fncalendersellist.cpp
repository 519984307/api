#include "fncalendersellist.h"
#include "ui_fncalendersellist.h"

FnCalenderSelList::FnCalenderSelList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnCalenderSelList)
{
    ui->setupUi(this);
    setMouseTracking(true);
    initData();
    m_isShowLunar = true;
    m_rowHeight = 96;
    m_itemTop = 1;
    m_mousedownFlag = false;
}

FnCalenderSelList::~FnCalenderSelList()
{
    delete ui;
}

void FnCalenderSelList::initData()
{
    m_hasInit = false;
    m_date = QDate::currentDate();

    m_hasInit = true;


}

QDate FnCalenderSelList::date() const
{
    return m_date;
}

void FnCalenderSelList::setDate(const QDate& date)
{
    m_date = date;
}

void FnCalenderSelList::changeDate()
{
    if (!m_hasInit)
    {
        return;
    }
    m_itemTop = 48;

    update();
}

void FnCalenderSelList::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());
    QString weekNames[] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};





    int days = m_dateDatas.count();
    m_days = days;
    int k = 0;
    for (int i = 0; i < days; i++)
    {
        FnCalenderData data = m_dateDatas.at(i);
        QDate selDate, curDate;
        curDate = QDate::currentDate();
        selDate = QDate::fromString(QString("%1-%2-%3").arg(data.year).arg(data.month).arg(data.day), "yyyy-M-d");
        int w = selDate.dayOfWeek();

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
        QString lunarDate =  GetLunarStringX(data.year, data.month, data.day, ly, lm, ld);
        QString lunarDay = getLunarDay(data.year, data.month, data.day);
        QRect textRc = QRect(dayRc.left() + 24, dayRc.top() + 4, dayRc.width(), 24);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, selDate.toString("yyyy-MM-dd") +
                         "      " + lunarDate + "        " + weekNames[w - 1]);


        data.line = k;
        data.rc = dayRc;
        data.date = selDate;

        data.lunarDate = lunarDate;
        data.lunarDay = lunarDay;
        emit drawExtraInfo(painter, data);
        m_dateDatas.replace(i, data);
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

void FnCalenderSelList::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    if (m_mousedownFlag)
    {
        int y = pt.y() - m_mousedownPoint.y();
        m_itemTop += y;
        m_mousedownPoint = pt;
        if (m_itemTop > 1)
        {
            m_itemTop = 1;
        }
        if (m_itemTop < -(m_days * m_rowHeight - height() + 64))
        {
            m_itemTop = -(m_days * m_rowHeight - height() + 64);
        }
        qDebug() << m_itemTop;
    }
    update();
}

void FnCalenderSelList::mousePressEvent(QMouseEvent* event)
{

    Q_UNUSED(event);
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    m_mousedownPoint = pt;
    m_mousedownFlag = true;
    for (int i = 0; i < m_dateDatas.count(); i++)
    {
        FnCalenderData data = m_dateDatas[i];
        if (data.rc.contains(pt))
        {
            emit cellClick(data);
        }

    }
}

void FnCalenderSelList::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    m_mousedownFlag = false;
    update();

}







int FnCalenderSelList::days() const
{
    return m_days;
}

void FnCalenderSelList::setDays(int days)
{
    m_days = days;
}

void FnCalenderSelList::addData(FnCalenderData& data)
{
    FnCalenderData newData = data;
    m_dateDatas.append(newData);
    update();
}

void FnCalenderSelList::clearData()
{
    m_dateDatas.clear();
    update();
}

int FnCalenderSelList::itemTop() const
{
    return m_itemTop;
}

void FnCalenderSelList::setItemTop(int itemTop)
{
    m_itemTop = itemTop;
}

int FnCalenderSelList::rowHeight() const
{
    return m_rowHeight;
}

void FnCalenderSelList::setRowHeight(int rowHeight)
{
    m_rowHeight = rowHeight;
}

bool FnCalenderSelList::isShowLunar() const
{
    return m_isShowLunar;
}

void FnCalenderSelList::setIsShowLunar(bool isShowLunar)
{
    m_isShowLunar = isShowLunar;
}
