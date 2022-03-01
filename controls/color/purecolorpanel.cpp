#include "purecolorpanel.h"
#include "ui_purecolorpanel.h"
int PureColorPanel::lastId = -1;
PureColorPanel::PureColorPanel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PureColorPanel)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

PureColorPanel::~PureColorPanel()
{
    delete ui;
}

int PureColorPanel::r() const
{
    return m_r;
}

void PureColorPanel::setR(int r)
{
    m_r = r;
}

int PureColorPanel::g() const
{
    return m_g;
}

void PureColorPanel::setG(int g)
{
    m_g = g;
}

int PureColorPanel::b() const
{
    return m_b;
}

void PureColorPanel::setB(int b)
{
    m_b = b;
}

int PureColorPanel::a() const
{
    return m_a;
}

void PureColorPanel::setA(int a)
{
    m_a = a;
}

QString PureColorPanel::name() const
{
    return m_name;
}

void PureColorPanel::setName(const QString& name)
{
    m_name = name;
}

void PureColorPanel::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QPoint pt = mapFromGlobal(cursor().pos());
    painter.begin(this);
    if (rect().contains(pt)) {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::white);
        painter.drawRect(rect());
    }
    QRect rc;
    QString rgbInfo;
    rc.setRect(1, 1, width() - 2, 32);
    painter.fillRect(rc, QColor(m_r, m_g, m_b, m_a));
    rc.setRect(1, 33, width() - 2, 24);
    painter.setPen(Qt::white);
    painter.drawText(rc, Qt::AlignCenter, m_name);

    rc.setRect(8, 57, width() - 16, 18);
    painter.setPen(Qt::white);
    rgbInfo = QString("RGB:%1,%2,%3").arg(m_r).arg(m_g).arg(m_b);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, rgbInfo);

    rc.setRect(8, 75, width() - 16, 18);
    painter.setPen(Qt::white);
    rgbInfo = htmlColor();
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, rgbInfo.toUpper());
    painter.end();
}

void PureColorPanel::focusOutEvent(QFocusEvent* event)
{
    update();
}

void PureColorPanel::mousePressEvent(QMouseEvent* event)
{
    for (int i = actions().count() - 1; i >= 0; i--) {
        QAction* act = actions().at(i);
        removeAction(act);
    }
    QStringList menuNames;
    menuNames << QString("复制为QColor(%1,%2,%3)").arg(m_r).arg(m_g).arg(m_b);
    menuNames << QString("复制为rgb(%1,%2,%3)").arg(m_r).arg(m_g).arg(m_b);
    menuNames << QString("复制为HTML:%1").arg(htmlColor());
    menuNames << "获取相关颜色";
    menuNames << "修改";
    menuNames << "删除";
    for (int i = 0; i < menuNames.count(); i++) {
        QAction* act = new QAction(this);
        connect(act, &QAction::triggered, this, &PureColorPanel::triggered);
        act->setText(menuNames[i]);
        addAction(act);
    }
    emit onClick();
}

QListWidgetItem* PureColorPanel::item() const
{
    return m_item;
}

void PureColorPanel::setItem(QListWidgetItem* item)
{
    m_item = item;
}

QString PureColorPanel::htmlColor()
{
    return QString("#%1%2%3").arg(intToHex(m_r)).arg(intToHex(m_g)).arg(intToHex(m_b));
}

int PureColorPanel::id() const
{
    return m_id;
}

void PureColorPanel::setId(int id)
{
    m_id = id;
}

QString PureColorPanel::intToHex(int i)
{
    QString ret = QString::number(i, 16);
    if (ret.length() == 1) {
        ret = "0" + ret;
    }
    return ret.toUpper();
}

void PureColorPanel::triggered()
{
    QAction* action = static_cast<QAction*>(sender());
    emit onMenuClick(this, action);
}
