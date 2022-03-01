#include "logowidget.h"
#include "ui_logowidget.h"

LogoWidget::LogoWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LogoWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

LogoWidget::~LogoWidget()
{
    delete ui;
}

QString LogoWidget::filePath() const
{
    return m_filePath;
}

void LogoWidget::setFilePath(const QString& filePath)
{
    m_filePath = filePath;
    qDebug() << filePath;
    update();
}

void LogoWidget::paintEvent(QPaintEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    Q_UNUSED(event)
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.save();
    QPainterPath path;


    path.addEllipse(6, 6, width() - 12, height() - 12);


    painter.setClipPath(path);
    if (path.contains(pt))
    {
        QPen pen;
        pen.setColor(QColor(173, 216, 230));
        pen.setWidth(2);
        painter.setPen(pen);


    }
    else
    {
        painter.setPen(Qt::NoPen);

    }
    QPixmap pix(m_filePath);
    pix = pix.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QRect rc = QRect(0, 0, width(), height());
    painter.drawPixmap(rc, pix);

    painter.drawPath(path);
    painter.restore();
    painter.end();

}

void LogoWidget::focusInEvent(QFocusEvent* event)
{
    update();
}

void LogoWidget::focusOutEvent(QFocusEvent* event)
{
    update();
}

void LogoWidget::mouseMoveEvent(QMouseEvent* event)
{
    update();

}
