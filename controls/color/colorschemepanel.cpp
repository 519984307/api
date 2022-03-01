#include "colorschemepanel.h"
#include "ui_colorschemepanel.h"

ColorSchemePanel::ColorSchemePanel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ColorSchemePanel)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QStringList menuNames;
    menuNames << "删除";
    for (int i = 0; i < menuNames.count(); i++) {
        QAction* act = new QAction(this);
        act->setText(menuNames[i]);
        addAction(act);
    }
}

ColorSchemePanel::~ColorSchemePanel()
{
    delete ui;
    qDeleteAll(m_colors);
}

int ColorSchemePanel::id() const
{
    return m_id;
}

void ColorSchemePanel::setId(int id)
{
    m_id = id;
}

QString& ColorSchemePanel::name()
{
    return m_name;
}

void ColorSchemePanel::setName(QString name)
{
    m_name = name;
}

void ColorSchemePanel::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);
    QRect rc;
    rc.setRect(8, 0, width() - 8, 16);
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, m_name);
    int l = 0;
    for (int i = 0; i < m_colors.count(); i++) {
        ColorObject* obj = m_colors.at(i);
        rc.setRect(l, 20, 96, height() - 20);
        painter.fillRect(rc, obj->color());
        painter.setPen(obj->antiColor());
        rc.setRect(l + 8, 20, width() - 8, 16);
        painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, obj->name());
        rc.setRect(l + 8, 36, width() - 8, 16);
        painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, obj->rgbColor());
        rc.setRect(l + 8, 52, width() - 8, 16);
        painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, obj->htmlColor());

        l = l + 96;
    }
    painter.end();
}

void ColorSchemePanel::clearColors()
{
    qDeleteAll(m_colors);
    m_colors.clear();
}

QList<ColorObject*> ColorSchemePanel::colors() const
{
    return m_colors;
}

void ColorSchemePanel::setColors(const QList<ColorObject*>& colors)
{
    m_colors = colors;
}

void ColorSchemePanel::addColor(int id, QString name, int r, int g, int b)
{
    ColorObject* obj = new ColorObject(this);
    obj->setId(id);
    obj->setName(name);
    obj->setR(r);
    obj->setG(g);
    obj->setB(b);

    m_colors << obj;
    update();
}

void ColorSchemePanel::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit onDoubleClick();
}
