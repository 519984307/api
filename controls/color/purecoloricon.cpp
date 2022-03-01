#include "purecoloricon.h"
#include "ui_purecoloricon.h"

PureColorIcon::PureColorIcon(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PureColorIcon)
{
    ui->setupUi(this);
}

PureColorIcon::~PureColorIcon()
{
    delete ui;
}

void PureColorIcon::paintEvent(QPaintEvent* event)
{
    QColor color = QColor(255 - m_r, 255 - m_g, 255 - m_b);
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(m_r, m_g, m_b));
    painter.setPen(color);
    QRect rc;
    rc.setRect(8, 0, width() - 8, 16);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, m_name);
    rc.setRect(8, 16, width() - 8, 16);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter,
        QString("rgb(%1,%2,%3)").arg(m_r).arg(m_g).arg(m_b));
    rc.setRect(8, 32, width() - 8, 16);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter,
        htmlColor());
    painter.end();
}

void PureColorIcon::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit onDoubleClick();
}

QListWidgetItem* PureColorIcon::getItem() const
{
    return m_item;
}

void PureColorIcon::setItem(QListWidgetItem* item)
{
    m_item = item;
}

QString PureColorIcon::name() const
{
    return m_name;
}

QString PureColorIcon::intToHex(int i)
{
    QString ret = QString::number(i, 16);
    if (ret.length() == 1) {
        ret = "0" + ret;
    }
    return ret.toUpper();
}

QString PureColorIcon::htmlColor()
{
    return QString("#%1%2%3").arg(intToHex(m_r)).arg(intToHex(m_g)).arg(intToHex(m_b));
}

PureColorIcon* PureColorIcon::getNew(QWidget* parent)
{
    PureColorIcon* icon = new PureColorIcon(parent);
    icon->setR(m_r);
    icon->setG(m_g);
    icon->setB(m_b);
    icon->setName(m_name);
    icon->setId(m_id);
    return icon;
}

void PureColorIcon::setName(QString name)
{
    m_name = name;
    update();
}

int PureColorIcon::id() const
{
    return m_id;
}

void PureColorIcon::setId(int id)
{
    m_id = id;
    update();
}

int PureColorIcon::a() const
{
    return m_a;
}

void PureColorIcon::setA(int a)
{
    m_a = a;
    update();
}

int PureColorIcon::b() const
{
    return m_b;
}

void PureColorIcon::setB(int b)
{
    m_b = b;
    update();
}

int PureColorIcon::g() const
{
    return m_g;
}

void PureColorIcon::setG(int g)
{
    m_g = g;
    update();
}

int PureColorIcon::r() const
{
    return m_r;
}

void PureColorIcon::setR(int r)
{
    m_r = r;
}
