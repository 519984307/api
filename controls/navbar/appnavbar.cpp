#include "appnavbar.h"
#include "ui_appnavbar.h"

AppNavBar::AppNavBar(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::AppNavBar)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_drawObj = new DrawObject(this);
}

AppNavBar::~AppNavBar()
{
    delete ui;
}

const QString& AppNavBar::caption() const
{
    return m_caption;
}

void AppNavBar::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
    update();
}

AppNavBarOperateInfo* AppNavBar::addOperateInfo(QString caption)
{

    AppNavBarOperateInfo* info = new AppNavBarOperateInfo(this);
    info->setCaption(caption);
    m_operateInfos << info;
    update();
    m_caption = caption;
    return  info;
}

AppNavBarOperateInfo* AppNavBar::currentOperateInfo()
{
    if (m_operateInfos.count() == 0)
    {
        return nullptr;
    }
    else
    {
        return m_operateInfos.last();
    }
}

void AppNavBar::goBack()
{
    if (m_operateInfos.count() > 1)
    {
        AppNavBarOperateInfo* info = m_operateInfos.pop();
        delete info;
        info = m_operateInfos.last();
        m_caption = info->caption();
        emit backButtonClick(info);
        update();
    }
}

void AppNavBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QRect clientRc = m_helper->clientRect();
    m_backButtonRect = QRect(16, 8, height() - 16, height() - 16);
    m_addButtonRect = QRect(width() - height(), 8, height() - 16, height() - 16);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QFont font = painter.font();
    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(clientRc, Qt::AlignCenter, m_caption);

    m_drawObj->drawBackButton(painter, m_backButtonRect, QColor(97, 97, 97), 2, 4);
    m_drawObj->drawAddButton(painter, m_addButtonRect, QColor(97, 97, 97), 2, 8);

    painter.end();
}

void AppNavBar::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event)
    QPoint curPt = m_helper->cursorPos();
    if (m_backButtonRect.contains(curPt))
    {
        goBack();

    }
    else if (m_addButtonRect.contains(curPt))
    {
        emit addButtonClick();
    }
}
