#include "capturewindow.h"
#include "ui_capturewindow.h"

CaptureWindow::CaptureWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CaptureWindow)
{
    ui->setupUi(this);
    takeCentralWidget();
    setMouseTracking(true);
    setAttribute(Qt::WA_DeleteOnClose);
    m_mousedownPoint = QPoint(0, 0);
    m_mousedownFlag = false;
    api = new tesseract::TessBaseAPI();
    api->Init(nullptr, "chi_sim");
}

CaptureWindow::~CaptureWindow()
{
    api->End();
    delete api;
    delete ui;
}

void CaptureWindow::paintEvent(QPaintEvent* event)
{
    QPoint pt = cursor().pos();
    QScreen* screen = qApp->screenAt(pt);
    qreal n = screen->devicePixelRatio();
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(rect(), m_pix, m_pix.rect());
    painter.fillRect(rect(), QColor(0, 0, 0, 80));
    if (m_mousedownFlag == true)
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::NoBrush);
        getSelectRect();
        m_pixRc.setRect(m_selectRc.left() * n, m_selectRc.top() * n, m_selectRc.width() * n, m_selectRc.height() * n);
        painter.drawPixmap(m_selectRc, m_pix, m_pixRc);
        painter.drawRect(m_selectRc);
    }
    else
    {
        painter.setPen(Qt::red);
        painter.drawLine(0, pt.y(), width(), pt.y());
        painter.drawLine(pt.x(), 0, pt.x(), height());
    }
    painter.end();
}

void CaptureWindow::mousePressEvent(QMouseEvent* event)
{
    m_mousedownFlag = true;
    m_mousedownPoint = mapFromGlobal(cursor().pos());
}

void CaptureWindow::mouseReleaseEvent(QMouseEvent* event)
{
    QMenu* menu = new QMenu(this);
    QStringList menuNames;
    if (event->button() == Qt::RightButton)
    {
        menuNames << "退出";
    }
    else
    {
        menuNames << "截图";
        menuNames << "复制OCR文本到剪贴板";
        menuNames << "追加OCR文本到剪贴板";
        menuNames << "取消";
        menuNames << "退出";
    }
    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(menu);
        act->setText(menuNames[i]);
        connect(act, &QAction::triggered, this, &CaptureWindow::onMenuTriggered);
        menu->addAction(act);
    }
    QPoint pt = cursor().pos();
    menu->exec(pt);
    delete menu;

    m_mousedownFlag = false;
    update();
}

void CaptureWindow::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void CaptureWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}

QPixmap CaptureWindow::pix() const
{
    return m_pix;
}

void CaptureWindow::setPix(const QPixmap& pix)
{
    m_pix = pix;
    update();
}

void CaptureWindow::getSelectRect()
{
    QPoint pt = mapFromGlobal(cursor().pos());

    int x = m_mousedownPoint.x() < pt.x() ? m_mousedownPoint.x() : pt.x();
    int y = m_mousedownPoint.y() < pt.y() ? m_mousedownPoint.y() : pt.y();
    int w = abs(m_mousedownPoint.x() - pt.x());
    int h = abs(m_mousedownPoint.y() - pt.y());
    m_selectRc.setRect(x, y, w, h);
}

void CaptureWindow::onMenuTriggered(bool checked)
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "退出")
    {
        close();
    }
    else if (act->text() == "截图")
    {
        QPixmap clipPix = m_pix.copy(m_pixRc);
        qApp->clipboard()->setPixmap(clipPix);
        close();
    }
    else if (act->text() == "复制OCR文本到剪贴板")
    {


        QPixmap clipPix = m_pix.copy(m_pixRc);
        QString txt = getOcrText(api, clipPix);
        qApp->clipboard()->setText(txt);



    }
    else if (act->text() == "追加OCR文本到剪贴板")
    {
        QString txt = qApp->clipboard()->text();

        QPixmap clipPix = m_pix.copy(m_pixRc);
        txt = txt + "\n" + getOcrText(api, clipPix);
        qApp->clipboard()->setText(txt);

    }
}

void startShootScreen(bool hideWindow)
{
    QWidget* activeWindow = qApp->activeWindow();
    if (hideWindow)
    {
        activeWindow->hide();
    }

    QElapsedTimer t;
    t.start();
    while (t.elapsed() < 500)
    {
        QApplication::processEvents();
    }
    QPoint pt = activeWindow->cursor().pos();
    QScreen* screen = QApplication::screenAt(pt);
    QPixmap pix = screen->grabWindow(0);
    qApp->clipboard()->setPixmap(pix);
    while (t.elapsed() < 500)
    {
        QApplication::processEvents();
    }
    CaptureWindow* captureWindow = new CaptureWindow(nullptr);
    if (hideWindow)
    {
        activeWindow->show();
    }

    captureWindow->showFullScreen();
    captureWindow->setPix(pix);
}
