#include "pixmapviewer.h"
#include "ui_pixmapviewer.h"
#include <QProcess>
PixmapViewer::PixmapViewer(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PixmapViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_autoFited = true;
    m_data = nullptr;
    addMenus();
}

PixmapViewer::~PixmapViewer()
{
    if (m_data != nullptr)
    {
        delete m_data;
    }
    delete ui;
}

void PixmapViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(97, 97, 97));
    if (!m_tempPix.isNull())
    {
        QRect rc;
        rc.setRect(m_startPoint.x(), m_startPoint.y(), m_tempPix.width(), m_tempPix.height());
        painter.drawPixmap(rc, m_tempPix, m_tempPix.rect());
    }
    painter.end();
}

void PixmapViewer::setImage(QPixmap& image)
{
    m_image = image;
    if (m_autoFited)
    {
        autoFit();

    }
    else
    {
        m_tempPix = m_image;
        m_startPoint = QPoint(1, 1);
        setFactor(1);
    }

    m_mousedownFlag = false;
}

void PixmapViewer::setFactor(double factor)
{
    QPoint curPos = m_helper->cursorPos();
    double wf = curPos.x() - m_startPoint.x();
    wf = wf / m_tempPix.width();

    double hf = curPos.y() - m_startPoint.y();
    hf = hf / m_tempPix.height();


    m_factor = factor;
    if (m_factor == 1)
    {
        m_tempPix = m_image;
    }
    else
    {
        m_tempPix = m_image.scaled(m_image.width() * m_factor, m_image.height() * factor,
                                   Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    }

    m_startPoint = QPoint(curPos.x() - m_tempPix.width() * wf,
                          curPos.y() - m_tempPix.height() * hf);
    update();
}

void PixmapViewer::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0)
    {
        setFactor(m_factor * 1.1);
    }
    else
    {
        setFactor(m_factor * 0.9);
    }
}

void PixmapViewer::mousePressEvent(QMouseEvent* event)
{
    m_mousedownFlag = true;
    m_mousedownPoint = mapFromGlobal(cursor().pos());
    update();
}

void PixmapViewer::mouseReleaseEvent(QMouseEvent* event)
{
    m_mousedownFlag = false;
    update();
}

void PixmapViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (m_mousedownFlag)
    {
        QPoint pt = mapFromGlobal(cursor().pos());
        int x = pt.x() - m_mousedownPoint.x();
        int y = pt.y() - m_mousedownPoint.y();
        m_startPoint.setX(m_startPoint.x() + x);
        m_startPoint.setY(m_startPoint.y() + y);
        m_mousedownPoint = pt;
        update();
    }
}

void PixmapViewer::resizeEvent(QResizeEvent* event)
{
    if (m_autoFited)
    {
        autoFit();
    }
}

void PixmapViewer::loadFromFile(QString filePath)
{
    m_filePath = filePath;
    setFilePath(m_filePath);
    QPixmap pix = QPixmap(m_filePath);
    setImage(pix);
}

void PixmapViewer::onMenuItemTrigger()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "复制图像到剪贴板")
    {
        qApp->clipboard()->setPixmap(m_image);
    }
    else if (act->text() == "复制文件")
    {
        // QMimeData* data = new QMimeData();
        if (m_data != nullptr)
        {
            delete m_data;
        }
        m_data = new QMimeData();
        QList<QUrl> urls;
        QUrl url = QUrl::fromLocalFile(m_filePath);
        urls << url;
        m_data->setUrls(urls);
        qApp->clipboard()->setMimeData(m_data);

    }
    else if (act->text() == "复制文件路径")
    {
        QString tempPath = m_filePath.replace("/", "\\");
        qApp->clipboard()->setText(tempPath);

    }
    else if (act->text() == "自动调整大小")
    {
        autoFit();
    }
    else if (act->text() == "在画图工具中打开")
    {
        QProcess::execute("mspaint.exe \"" + m_filePath + "\"");

    }
    else if (act->text() == "打开文件位置")
    {
        QFileInfo info(m_filePath);
        QString folderPath = info.path();
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
    }
    else if (act->text() == "向右旋转90°")
    {
        QMatrix marix;
        marix.rotate(90);
        m_image = m_image.transformed(marix);
        autoFit();
    }
    else if (act->text() == "向左旋转90°")
    {
        QMatrix marix;
        marix.rotate(-90);
        m_image = m_image.transformed(marix);
        autoFit();
    }
    else if (act->text() == "水平镜像")
    {
        QImage img = m_image.toImage().mirrored(true, false);
        m_image = QPixmap::fromImage(img);
        autoFit();
    }
}

bool PixmapViewer::autoFited() const
{
    return m_autoFited;
}

void PixmapViewer::setAutoFited(bool autoFited)
{
    m_autoFited = autoFited;
}

void PixmapViewer::autoFit()
{
    int w = width();
    int h = height();
    double f1 = w;
    f1 = f1 / h;

    double f2 = m_image.width();
    f2 = f2 / m_image.height();

    //等高
    if (f1 > f2)
    {
        m_tempPix = m_image.scaledToHeight(h, Qt::SmoothTransformation);

    }
    else
    {
        m_tempPix = m_image.scaledToWidth(w, Qt::SmoothTransformation);
    }
    m_startPoint = QPoint((w - m_tempPix.width()) / 2, (h - m_tempPix.height()) / 2);
    m_factor = m_tempPix.width();
    m_factor = m_factor / m_image.width();
    update();
}



QString PixmapViewer::filePath() const
{
    return m_filePath;
}

void PixmapViewer::setFilePath(const QString& filePath)
{
    m_filePath = filePath;
}

void PixmapViewer::addMenus()
{
    QStringList menuNames;
    menuNames << "复制图像到剪贴板"
              << "复制文件"
              << "复制文件路径"
              << "-"
              << "自动调整大小"
              << "-"
              << "在画图工具中打开"
              << "打开文件位置"
              << "-"
              << "向右旋转90°"
              << "向左旋转90°"
              << "水平镜像";
    for (int i = 0; i < menuNames.count(); i++)
    {

        QAction* act = new QAction(this);
        if (menuNames[i] == "-")
        {
            act->setSeparator(true);
        }
        else
        {
            act->setText(menuNames[i]);
            connect(act, &QAction::triggered, this, &PixmapViewer::onMenuItemTrigger);
        }
        QImage img;
        addAction(act);
    }

}
