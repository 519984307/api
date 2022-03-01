#include "fncalender.h"
#include "ui_fncalender.h"

FnCalender::FnCalender(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnCalender)
{
    ui->setupUi(this);
    setMouseTracking(true);
    initData();
    m_isShowLunar = true;
}

FnCalender::~FnCalender()
{
    delete ui;
}

void FnCalender::initData()
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

QDate FnCalender::date() const
{
    return m_date;
}

void FnCalender::setDate(const QDate& date)
{
    m_date = date;
}

void FnCalender::changeDate()
{
    if (!m_hasInit)
    {
        return;
    }
    int y = ui->cbbYear->currentData(Qt::UserRole).toInt();
    int m = ui->cbbMonth->currentData(Qt::UserRole).toInt();
    m_date = QDate::fromString(QString("%1-%2-1").arg(y).arg(m), "yyyy-M-d");
    update();
}

void FnCalender::paintEvent(QPaintEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());
    QString weekNames[] = {"一", "二", "三", "四", "五", "六", "日"};
    int w = width() / 7;
    int h = (height() - 96) / 6;
    painter.setPen(Qt::black);
    for (int i = 0; i < 7; i++)
    {
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(i * w, 48, i * w, height());
    }

    painter.setPen(QColor(197, 197, 197));
    painter.drawLine(0, 48, width(), 48);
    for (int i = 0; i < 6; i++)
    {
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(0, i * h + 96, width(), i * h + 96);
    }
    painter.setPen(Qt::black);
    for (int i = 0; i < 7; i++)
    {
        QRect weekNameRc = QRect(i * w, 48, w, 48);
        painter.drawText(weekNameRc, Qt::AlignCenter, weekNames[i]);
    }
    QDate firstDay = m_date.addDays(-m_date.day() + 1);
    int n = firstDay.dayOfWeek() - 1;
    qDebug() << n;
    int days = m_date.daysInMonth();
    int j = 0;
    int k = n;
    for (int i = 0; i < k; i++)
    {
        m_dateDatas[i].rc = QRect(i * w, j * h + 96, w, h);
        m_dateDatas[i].isNull = true;
        m_dateDatas[i].line = 0;
        emit drawExtraInfo(painter, m_dateDatas[i]);

    }
    for (int i = 1; i <= days; i++)
    {
        QDate selDate, curDate;
        curDate = QDate::currentDate();
        selDate = QDate::fromString(QString("%1-%2-%3").arg(m_date.year()).arg(m_date.month()).arg(i), "yyyy-M-d");
        QRect dayRc = QRect(n * w, j * h + 96, w, h);
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
        QRect textRc = QRect(dayRc.left(), dayRc.top() + 4, dayRc.width(), 24);
        painter.drawText(textRc, Qt::AlignCenter, QString("%1").arg(i));
        QRect lunarTextRc = QRect(dayRc.left(), dayRc.top() + 28, dayRc.width(), 24);
        painter.drawText(lunarTextRc, Qt::AlignCenter, lunarDay);

        m_dateDatas[k].line = j;
        m_dateDatas[k].rc = dayRc;
        m_dateDatas[k].date = selDate;
        m_dateDatas[k].year = m_date.year();
        m_dateDatas[k].month = m_date.month();
        m_dateDatas[k].day = i;
        m_dateDatas[k].lunarDate = lunarDate;
        m_dateDatas[k].lunarDay = lunarDay;
        n++;
        if (n == 7)
        {
            j++;
            n = 0;
        }
        emit drawExtraInfo(painter, m_dateDatas[k]);
        k++;

    }
    while (k < 42)
    {
        QRect dayRc = QRect(n * w, j * h + 96, w, h);
        m_dateDatas[k].line = j;
        m_dateDatas[k].isNull = true;
        m_dateDatas[k].rc = dayRc;

        n++;
        if (n == 7)
        {
            j++;
            n = 0;
        }
        emit drawExtraInfo(painter, m_dateDatas[k]);
        k++;
    }

    painter.end();
}

void FnCalender::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void FnCalender::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = this->cursor().pos();
    pt = mapFromGlobal(pt);
    for (int i = 0; i < 42; i++)
    {
        FnCalenderData data = m_dateDatas[i];
        if (data.rc.contains(pt))
        {
            emit cellClick(data);
        }

    }
}

void FnCalender::on_btnPreMonth_clicked()
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

void FnCalender::on_btnNextMonth_clicked()
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

void FnCalender::on_cbbYear_currentIndexChanged(int index)
{
    changeDate();
}

void FnCalender::on_cbbMonth_currentIndexChanged(int index)
{
    changeDate();
}

bool FnCalender::isShowLunar() const
{
    return m_isShowLunar;
}

void FnCalender::setIsShowLunar(bool isShowLunar)
{
    m_isShowLunar = isShowLunar;
}
