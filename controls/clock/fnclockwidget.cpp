#include "fnclockwidget.h"
#include "ui_fnclockwidget.h"

FnClockWidget::FnClockWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnClockWidget)
{
    ui->setupUi(this);
    m_backGround = QPixmap();
    m_drawObj = new DrawObject(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_clockTime = QTime::currentTime();
    m_hourPointer = new FnClockWidgetPointer(this);
    m_hourPointer->setValue(m_clockTime.hour());
    m_hourPointer->setPointerType(tpHour);


    m_minutePointer = new FnClockWidgetPointer(this);
    m_minutePointer->setPointerType(tpMinute);
    m_minutePointer->setValue(m_clockTime.minute());


    m_secondPointer = new FnClockWidgetPointer(this);
    m_secondPointer->setPointerType(tpSecond);
    m_secondPointer->setValue(m_clockTime.second());
    m_secondPointer->setColor(Qt::red);
    m_secondPointer->setWidth(1);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FnClockWidget::onTimerTimeOut);
    m_timer->start(100);
}

FnClockWidget::~FnClockWidget()
{
    delete ui;
}

void FnClockWidget::paintEvent(QPaintEvent* event)
{
    QPoint centerPt = m_helper->centerPos();
    int r0 = m_helper->radius() - 64;
    int r1 = r0 - 72;

    int r3 = r0 * 0.5;
    int r2 = r3 * 0.7;
    int r4 = r0 * 0.8;
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.drawEllipse(centerPt, r0, r0);

    if (!m_backGround.isNull())
    {
        painter.save();
        QPainterPath path;
        path.addEllipse(centerPt, r0, r0);
        painter.setClipPath(path);
        QRect backgroundRc(centerPt.x() - r0, centerPt.y() - r0, r0 * 2, r0 * 2);
        painter.drawPixmap(backgroundRc, m_backGround, m_backGround.rect());
        painter.restore();
    }

    for (int i = 0; i < 12; i++)
    {


        int x = centerPt.x() + r1 * cos(m_drawObj->angleToRadian(i * 30 - 60));
        int y = centerPt.y() + r1 * sin(m_drawObj->angleToRadian(i * 30 - 60));
        painter.save();
        QMatrix matrix;
        matrix.translate(x, y);
        painter.setMatrix(matrix);
        QRect numRc(- 12, - 12, 24, 24);
        QFont font = painter.font();
        font.setPixelSize(24);
        painter.setFont(font);
        painter.drawText(numRc, Qt::AlignCenter, QString("%1").arg(i + 1));
        painter.restore();

        //绘制时针


        m_hourPointer->drawPointLine(painter, centerPt, r2, m_clockTime);


        //绘制分针

        m_minutePointer->drawPointLine(painter, centerPt, r3, m_clockTime);


        m_secondPointer->drawPointLine(painter, centerPt, r4, m_clockTime);




    }
//    painter.setBrush(Qt::black);
//    painter.drawEllipse(centerPt, 3, 3);
    painter.end();


}

QPixmap FnClockWidget::getBackGround() const
{
    return m_backGround;
}

void FnClockWidget::setBackGround(const QPixmap& backGround)
{
    int w = backGround.width() < backGround.height() ? backGround.width() : backGround.height();
    m_backGround = backGround.copy((backGround.width() - w) / 2, (backGround.height() - w) / 2, w, w);
}

bool FnClockWidget::getAlwaysShowCurrentTime() const
{
    return m_alwaysShowCurrentTime;
}

void FnClockWidget::setAlwaysShowCurrentTime(bool value)
{
    m_alwaysShowCurrentTime = value;
    update();
}

void FnClockWidget::onTimerTimeOut()
{
    if (m_alwaysShowCurrentTime)
    {
        m_clockTime = QTime::currentTime();
        update();

    }
}

FnClockWidgetPointer* FnClockWidget::secondPointer() const
{
    return m_secondPointer;
}

void FnClockWidget::setSecondPointer(FnClockWidgetPointer* secondPointer)
{
    m_secondPointer = secondPointer;
}

FnClockWidgetPointer* FnClockWidget::minutePointer() const
{
    return m_minutePointer;
}

void FnClockWidget::setMinutePointer(FnClockWidgetPointer* minutePointer)
{
    m_minutePointer = minutePointer;
}

FnClockWidgetPointer* FnClockWidget::hourPointer() const
{
    return m_hourPointer;
}

void FnClockWidget::setHourPointer(FnClockWidgetPointer* hourPointer)
{
    m_hourPointer = hourPointer;
}


