#include "ganttchart.h"
#include "ui_ganttchart.h"


GanttChart::GanttChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GanttChart)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsLeft(0);
    m_helper->setItemsTop(0);
    m_dayWidth = 32;
    setMouseTracking(true);
}

GanttChart::~GanttChart()
{
    delete ui;
}

int GanttChart::minYear() const
{
    return m_minYear;
}

void GanttChart::setMinYear(int newMinYear)
{
    m_minYear = newMinYear;
}

int GanttChart::maxYear() const
{
    return m_maxYear;
}

void GanttChart::setMaxYear(int newMaxYear)
{
    m_maxYear = newMaxYear;
}

void GanttChart::applyRange()
{
    qDeleteAll(m_months);
    m_months.clear();

    qDeleteAll(m_days);
    m_days.clear();

    int y = m_minYear;
    int m = 1;
    for (int i = 0; i < (m_maxYear - m_minYear) * 12; i++)
    {
        QDate d1;
        d1.setDate(y, m, 1);
        QDate d2 = d1.addMonths(1).addDays(-1);
        int n = d1.daysTo(d2) + 1;
        GanttMonth* month = new GanttMonth(this);
        month->setYear(y);
        month->setMonth(m);
        month->setDays(n);
        m_months << month;
        for (int j = 1; j <= n; j++)
        {
            GanttDay* day = new GanttDay(this);
            day->setYear(y);
            day->setMonth(m);
            day->setDay(j);
            QDate curDate;
            curDate.setDate(y, m, j);
            day->setWeekDay(curDate.dayOfWeek());
            QString dayName = curDate.toString("yyyy-MM-dd");
            m_dayInfos[dayName] = day;
            m_days << day;
        }



        m++;
        if (m > 12)
        {
            m = 1;
            y++;
        }
    }
    update();

}

void GanttChart::paintEvent(QPaintEvent* event)
{
    QDate today = QDate::currentDate();
    QRect clientRc = m_helper->clientRect();

    QPoint curPt = m_helper->cursorPos();
    QString weekNames[] {"一", "二", "三", "四", "五", "六", "日"};
    QPainter painter;
    painter.begin(this);
    painter.fillRect(clientRc, QBrush(Qt::white));
    int w = 0;
    for (int i = 0; i < m_columns.count(); i++)
    {
        GanttColumn* column = m_columns.at(i);
        QRect rc(w, 0, column->width(), 80);
        painter.setBrush(QBrush(QColor(241, 241, 241)));
        painter.setPen(QColor(195, 195, 195));
        painter.drawRect(rc);
        column->setRect(rc);
        painter.setPen(QColor(0, 0, 0));
        painter.drawText(rc, Qt::AlignCenter, column->caption());
        w += column->width();
    }
    m_columnsWidth = w;

    //绘制右侧表头
    painter.save();
    painter.setClipRect(QRect(m_columnsWidth, 0, width() - m_columnsWidth, 80));

    int l = m_helper->itemsLeft() + w;
    for (int i = 0; i < m_months.count(); i++)
    {
        GanttMonth* month = m_months.at(i);
        painter.setBrush(QBrush(QColor(241, 241, 241)));
        painter.setPen(QColor(195, 195, 195));
        QRect rc(l, 0, month->days() * m_dayWidth, 32);
        painter.drawRect(rc);
        month->setRect(rc);
        painter.setPen(QColor(0, 0, 0));
        painter.drawText(rc, Qt::AlignCenter, QString("%1年%2月").arg(month->year()).arg(month->month()));
        l += month->days() * m_dayWidth;

    }
    l = m_helper->itemsLeft() + w;
    for (int i = 0; i < m_days.count(); i++)
    {
        GanttDay* day = m_days.at(i);
        painter.setBrush(QBrush(QColor(241, 241, 241)));
        painter.setPen(QColor(195, 195, 195));
        QRect rc(l, 32,  m_dayWidth, 48);
        painter.drawRect(rc);
        day->setRect(rc);
        QRect dayRc(l, 32,  m_dayWidth, 24);
        painter.setPen(QColor(0, 0, 0));
        painter.drawText(dayRc, Qt::AlignCenter, QString("%1日").arg(day->day()));

        QRect weekRc(l, 56,  m_dayWidth, 24);
        painter.drawText(weekRc, Qt::AlignCenter, QString("%1").arg(weekNames[day->weekDay() - 1]));

        l +=  m_dayWidth;

    }
    painter.restore();

    painter.save();
    painter.setClipRect(QRect(0, 80,  m_columnsWidth, height() - 80));
    int t = m_helper->itemsTop() + 80;
    for (int i = 0; i < m_tasks.count(); i++)
    {
        GanttTask* task = m_tasks.at(i);
        QStringList infos;
        int cw = 0;
        for (int j = 0; j < m_columns.count(); j++)
        {
            GanttColumn* column = m_columns.at(j);
            painter.setBrush(QBrush(QColor(241, 241, 241)));
            painter.setPen(QColor(195, 195, 195));
            QRect rc(cw, t, column->width(), 32);
            painter.drawRect(rc);
            QString value = task->value(column->caption());
            painter.setPen(QColor(0, 0, 0));
            painter.drawText(rc, Qt::AlignCenter, value);
            infos << value;
            cw += column->width();
        }
        int allDays = task->startDate().daysTo(task->endDate()) + 1;
        int day;
        if (today < task->startDate())
        {
            day = 0;
        }
        else if (today > task->endDate())
        {
            day = allDays;
        }
        else
        {
            day = task->startDate().daysTo(today) + 1;
        }

        infos << QString("共计%1天").arg(allDays);
        infos << QString("进度%1/%2").arg(day).arg(allDays);
        double d = (double)day;
        d = d / allDays;
        d = d * 100;
        qDebug() << d;
        infos << QString("百分比 %1").arg(d) + "%";
        task->setShowInfo(infos.join("    |    ").trimmed());
        t += 32;
    }
    painter.restore();

    //绘制进度
    painter.save();
    painter.setClipRect(QRect(m_columnsWidth, 80, width() - m_columnsWidth, height() - 80));
    t = m_helper->itemsTop() + 80;
    for (int i = 0; i < m_tasks.count(); i++)
    {
        GanttTask* task = m_tasks.at(i);
        QRect taskRc(0, t, width(), 24);
        task->setRect(taskRc);
        if (m_selectedTasks.indexOf(task) >= 0)
        {
            QRect spanBkRect(m_columnsWidth, t, width() - m_columnsWidth, 32);
            painter.fillRect(spanBkRect, QBrush(QColor(242, 242, 242)));
        }

        GanttDay* d1 = m_dayInfos[task->startDate().toString("yyyy-MM-dd")];
        if (d1 == nullptr)
        {
            d1 = m_dayInfos[QString("%1-01-01").arg(m_minYear)];
        }
        GanttDay* d2 = m_dayInfos[task->endDate().toString("yyyy-MM-dd")];
        if (d2 == nullptr)
        {

            d2 = m_dayInfos[QString("%1-12-31").arg(m_maxYear)];

        }
        int rcLeft = d1->rect().left();
        int rcRight = d2->rect().right();
        if ((d1 != nullptr)  && (d2 != nullptr))
        {
            QRect spanRect(rcLeft, t + 4, rcRight - rcLeft + 1, 24);
            painter.fillRect(spanRect, QBrush(task->backgroundColor()));
            task->setSpanRect(spanRect);
            QFontMetrics fm = painter.fontMetrics();
            int fw = fm.width(task->showInfo());
            if (fw < spanRect.width())
            {
                painter.setPen(Qt::white);
                QRect textRc(spanRect.left() + 6, spanRect.top(), spanRect.width() - 12, spanRect.height());
                painter.drawText(textRc, task->showInfo(), Qt::AlignLeft | Qt::AlignVCenter);
            }
            else
            {
                painter.setPen(Qt::black);

                QRect textRc(spanRect.right() + 12, spanRect.top(), fw + 12, spanRect.height());
                QRect textBkRc(spanRect.right() + 6, spanRect.top(), fw + 12, spanRect.height());
                painter.fillRect(textBkRc, QBrush(QColor(250, 250, 250)));
                painter.drawText(textRc, task->showInfo(), Qt::AlignLeft | Qt::AlignVCenter);
            }

        }


        t += 32;
    }


    painter.restore();
    painter.end();

}

void GanttChart::addColumn(QString caption, int columnWidth)
{
    GanttColumn* column = new GanttColumn(this);
    column->setCaption(caption);
    column->setWidth(columnWidth);
    m_columns << column;
    update();

}

void GanttChart::addTask(GanttTask* task)
{
    m_tasks << task;
    update();
}

void GanttChart::onMenuActionTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "修改时间段")
    {
        if (m_selectedTasks.count() == 0)
        {
            return;
        }
        GanttTask* task = m_selectedTasks.at(0);
        EditGanttDateSpanDialog* dlg = new EditGanttDateSpanDialog();
        dlg->setTask(task);
        dlg->exec();
        delete dlg;
        update();
    }
    else if (act->text() == "修改颜色")
    {
        if (m_selectedTasks.count() == 0)
        {
            return;
        }
        GanttTask* task = m_selectedTasks.at(0);
        QColor color = QColorDialog::getColor(task->backgroundColor());
        task->setBackgroundColor(color);
        update();
    }
}

void GanttChart::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();
    QPoint curPt = m_helper->cursorPos();
    m_selectedTasks.clear();
    for (int i = 0; i < m_tasks.count(); i++)
    {
        GanttTask* task = m_tasks.at(i);
        if (task->rect().contains(curPt))
        {
            m_selectedTasks << task;
        }
    }
    QStringList menuNames;
    if (event->buttons() == Qt::RightButton)
    {
        menuNames << "修改时间段" << "修改颜色";
        QMenu* menu = new QMenu(this);
        for (int i = 0; i < menuNames.count(); i++)
        {
            QAction* act = new QAction(this);
            connect(act, &QAction::triggered, this, &GanttChart::onMenuActionTriggered);
            act->setText(menuNames[i]);
            menu->addAction(act);
        }
        menu->exec(cursor().pos());

        delete menu;
        m_helper->startMouseUp();
    }



    update();

}

void GanttChart::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();

}

void GanttChart::mouseDoubleClickEvent(QMouseEvent* event)
{



}

void GanttChart::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint curPt = m_helper->cursorPos();
        if (curPt.x() > m_columnsWidth)
        {

            int d = curPt.x() - m_helper->mouseMovePoint().x();
            int l = m_helper->itemsLeft() + d;
            if (l > 0)
            {
                l = 0;
            }
            m_helper->setItemsLeft(l);

            d = curPt.y() - m_helper->mouseMovePoint().y();
            int t = m_helper->itemsTop() + d;
            if (t > 0)
            {
                t = 0;
            }
            m_helper->setItemsTop(t);

            m_helper->setMouseMovePoint(curPt);
        }
        else
        {
            int d = curPt.y() - m_helper->mouseMovePoint().y();
            int t = m_helper->itemsTop() + d;
            if (t > 0)
            {
                t = 0;
            }
            m_helper->setItemsTop(t);
            m_helper->setMouseMovePoint(curPt);
        }
    }
    update();
}
