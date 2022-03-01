#include "fntitlebar.h"
#include "ui_fntitlebar.h"

FnTitleBar::FnTitleBar(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnTitleBar)
{
    ui->setupUi(this);
    m_titleBarStyle = fsVsCode;
    m_parentWindow = nullptr;
    m_mousedownFlag = false;
    ui->btnClose->setMinimumSize(QSize(52, 29));
    ui->btnClose->setMaximumSize(QSize(52, 29));
    ui->btnMax->setMinimumSize(QSize(52, 29));
    ui->btnMax->setMaximumSize(QSize(52, 29));
    ui->btnMin->setMinimumSize(QSize(52, 29));
    ui->btnMin->setMaximumSize(QSize(52, 29));
    m_isNormal = true;
    ui->wgtMenu->setMouseTracking(true);
    m_menuBar = new QMenuBar(ui->wgtMenu);
    m_menuBar->setMouseTracking(true);
    m_menuBar->setStyleSheet(R"(
      QMenuBar::item:selected { background: rgb(80,80,80); }
    )");
    QHBoxLayout* lay = new QHBoxLayout();
    ui->wgtMenu->setLayout(lay);
    lay->addWidget(m_menuBar);
    lay->setContentsMargins(0, 0, 0, 0);

    setMouseTracking(true);
    m_isMaxButtonEnabled = true;



}

FnTitleBar::~FnTitleBar()
{
    delete ui;
}

FnTitleBarStyle FnTitleBar::titleBarStyle() const
{
    return m_titleBarStyle;
}

void FnTitleBar::setTitleBarStyle(const FnTitleBarStyle& titleBarStye)
{
    m_titleBarStyle = titleBarStye;
}

QPixmap FnTitleBar::icon() const
{
    return m_icon;
}

void FnTitleBar::setIcon(const QPixmap& icon)
{
    m_icon = icon;
    update();
}

void FnTitleBar::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect rc(0, 0, width(), height());
    painter.fillRect(rc, QBrush(QColor(60, 60, 60)));
    QRect iconRc = QRect(6, 6, 16, 16);
    painter.drawPixmap(iconRc, m_icon, m_icon.rect());


    painter.end();
}

void FnTitleBar::mousePressEvent(QMouseEvent* event)
{
    m_mousedownFlag = true;
    m_mouseDownPoint = mapFromGlobal(this->cursor().pos());

}

void FnTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
    m_mousedownFlag = false;

}

void FnTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit ui->btnMax->clicked();


}

void FnTitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (m_mousedownFlag)
    {
        QPoint pt = mapFromGlobal(this->cursor().pos());
        int x = pt.x() - m_mouseDownPoint.x();
        int y = pt.y() - m_mouseDownPoint.y();
        if (m_parentWindow != nullptr)
        {
            m_parentWindow->move(m_parentWindow->x() + x, m_parentWindow->y() + y);
        }



    }

}

void FnTitleBar::setCloseIcon(const QPixmap& closeIcon)
{
    m_closeIcon = closeIcon;
    ui->btnClose->setIcon(m_closeIcon);
}

QPixmap FnTitleBar::restoreIcon() const
{
    return m_restoreIcon;
}

void FnTitleBar::setRestoreIcon(const QPixmap& restoreIcon)
{
    m_restoreIcon = restoreIcon;
}

QPixmap FnTitleBar::closeIcon() const
{
    return m_closeIcon;
}

QPixmap FnTitleBar::maxIcon() const
{
    return m_maxIcon;
}

void FnTitleBar::setMaxIcon(const QPixmap& maxIcon)
{
    m_maxIcon = maxIcon;
    ui->btnMax->setIcon(m_maxIcon);

}

QPixmap FnTitleBar::minIcon() const
{
    return m_minIcon;
}

void FnTitleBar::setMinIcon(const QPixmap& minIcon)
{
    m_minIcon = minIcon;
    ui->btnMin->setIcon(m_minIcon);
}

QMainWindow* FnTitleBar::parentWindow() const
{
    return m_parentWindow;
}

void FnTitleBar::setParentWindow(QMainWindow* parentWindow)
{
    m_parentWindow = parentWindow;
}

void FnTitleBar::on_btnMax_clicked()
{
    if (!m_isMaxButtonEnabled)
    {
        return;
    }

    if (m_isNormal)
    {
        m_parentWindow->showMaximized();
        ui->btnMax->setIcon(m_restoreIcon);
    }
    else
    {
        m_parentWindow->showNormal();
        ui->btnMax->setIcon(m_maxIcon);
    }
    m_isNormal = !m_isNormal;
}

void FnTitleBar::on_btnMin_clicked()
{
    m_parentWindow->showMinimized();
}

void FnTitleBar::on_btnClose_clicked()
{
    m_parentWindow->close();
}

const QString& FnTitleBar::caption() const
{
    return m_caption;
}

void FnTitleBar::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
    ui->lblTitle->setText(m_caption);
}

bool FnTitleBar::isMaxButtonEnabled() const
{
    return m_isMaxButtonEnabled;
}

void FnTitleBar::setIsMaxButtonEnabled(bool newIsMaxButtonEnabled)
{
    m_isMaxButtonEnabled = newIsMaxButtonEnabled;
}

QMenuBar* FnTitleBar::menuBar() const
{
    return m_menuBar;
}

void FnTitleBar::setMenuBar(QMenuBar* menuBar)
{
    m_menuBar = menuBar;
}
