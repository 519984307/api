#include "coloredit.h"
#include "ui_coloredit.h"

ColorEdit::ColorEdit(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ColorEdit)
{
    ui->setupUi(this);
    m_a = 255;
    m_r = 255;
    m_g = 255;
    m_b = 255;
}

ColorEdit::~ColorEdit()
{
    delete ui;
}

int ColorEdit::r() const
{
    return m_r;
}

void ColorEdit::setR(int r)
{
    m_r = r;
    update();
}

int ColorEdit::g() const
{
    return m_g;
}
void ColorEdit::setG(int g)
{
    m_g = g;
    update();
}

int ColorEdit::b() const
{
    return m_b;
}

void ColorEdit::setB(int b)
{
    m_b = b;
    update();
}

void ColorEdit::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(m_r, m_g, m_b, m_a));
    painter.setPen(QColor(255 - m_r, 255 - m_g, 255 - m_b));
    QString s = QString("RGBA(%1,%2,%3,%4)").arg(m_r).arg(m_g).arg(m_b).arg(m_a);
    QRect rc;
    rc.setRect(16, 0, width() - 16, height());
    painter.drawText(rc, Qt::AlignCenter, s);
    painter.end();
}

void ColorEdit::mousePressEvent(QMouseEvent* event)
{
    QColor color = QColorDialog::getColor();
    color.getRgb(&m_r, &m_g, &m_b, &m_a);
    update();
}

int ColorEdit::a() const
{
    return m_a;
}

void ColorEdit::setA(int a)
{
    m_a = a;
    update();
}
