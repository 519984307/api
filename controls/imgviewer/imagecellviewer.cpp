#include "imagecellviewer.h"
#include "ui_imagecellviewer.h"

ImageCellViewer::ImageCellViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImageCellViewer)
{
    ui->setupUi(this);
    m_selectObject = nullptr;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setMaxTop(16);
    m_helper->setItemsTop(16);
    setMouseTracking(true);
    addMenus();
    m_mimeData = nullptr;
}

ImageCellViewer::~ImageCellViewer()
{
    delete ui;
}

const QList<ImageObject*>& ImageCellViewer::items() const
{
    return m_items;
}

void ImageCellViewer::setItems(const QList<ImageObject*>& newItems)
{
    m_items = newItems;
}

void ImageCellViewer::loadFromFolder(QString path)
{

    m_paths << path;
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Files);
    for (const QFileInfo& info : qAsConst(fileInfos))
    {
        ImageObject* item = new ImageObject(this);
        item->setPath(info.absoluteFilePath());
        m_items << item;
    }
    update();

}

void ImageCellViewer::insertFile(int index, QString fileName)
{
    ImageObject* item = new ImageObject(this);
    item->setPath(fileName);
    m_items.insert(index, item);
    update();
}

void ImageCellViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QPoint pt = m_helper->cursorPos();
    QRect clientRc = m_helper->clientRect();
    painter.begin(this);
    painter.fillRect(clientRc, QBrush(Qt::white));
    int t = m_helper->itemsTop();
    int l = 16;
    for (int i = 0; i < m_items.count(); i++)
    {
        ImageObject* item = m_items.at(i);
        QRect rc(l, t, 256, 256);
        item->setRect(rc);
        if (item->pix().isNull())
        {
            QPixmap pix(item->path());
            int w = pix.width() < pix.height() ? pix.width() : pix.height();
            pix = pix.copy(pix.rect().center().x() - w / 2,
                           pix.rect().center().y() - w / 2, w, w);
            item->setPix(pix);

        }
        painter.drawPixmap(rc, item->pix(), item->pix().rect());
        if (item->isSelected())
        {
            painter.setPen(QColor(97, 97, 97));
        }
        else if (item->rect().contains(pt))
        {
            painter.setPen(QColor(203, 203, 203));
        }
        else
        {
            painter.setPen(QColor(197, 197, 197));
        }

        painter.drawRect(rc);



        l += 272;

        if ((l + 256) > width())
        {
            l = 16;
            t += 272;
        }

    }
    painter.end();

}

void ImageCellViewer::mousePressEvent(QMouseEvent* event)
{
    m_selectObject = nullptr;
    QPoint pt = m_helper->cursorPos();
    for (ImageObject* item : qAsConst(m_items))
    {
        bool bSel = item->rect().contains(pt);
        if (bSel)
        {
            m_selectObject = item;
        }
        item->setIsSelected(bSel);
    }
    update();
}

void ImageCellViewer::mouseReleaseEvent(QMouseEvent* event)
{

}

void ImageCellViewer::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void ImageCellViewer::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void ImageCellViewer::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    int t = m_helper->itemsTop();
    t += y;
    m_helper->setItemsTop(t);

}

ImageObject* ImageCellViewer::selectObject() const
{
    return m_selectObject;
}

void ImageCellViewer::setSelectObject(ImageObject* newSelectObject)
{
    m_selectObject = newSelectObject;
}

void ImageCellViewer::addMenus()
{
    QStringList menus;
    menus << "打开" << "复制" << "删除" << "打开所在文件夹" << "刷新";
    for (int i = 0; i < menus.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menus[i]);
        connect(act, &QAction::triggered, this, &ImageCellViewer::onMenuActionTriggered);
        addAction(act);
    }

}

void ImageCellViewer::onMenuActionTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "删除")
    {
        if (m_selectObject == nullptr)
        {
            return;
        }
        if (QMessageBox::question(this, "提示", "删除选中项吗?") == QMessageBox::No)
        {
            return;
        }
        QFile::remove(m_selectObject->path());
        m_items.removeOne(m_selectObject);
        m_selectObject = nullptr;
        update();
    }
    else if (act->text() == "复制")
    {
        if (m_selectObject == nullptr)
        {
            return;
        }
        QUrl url = QUrl::fromLocalFile(m_selectObject->path());
        QList<QUrl> urls;
        urls << url;
        if (m_mimeData != nullptr)
        {
            delete m_mimeData;
        }
        m_mimeData = new QMimeData();
        m_mimeData->setUrls(urls);
        qApp->clipboard()->setMimeData(m_mimeData);

    }
    else if (act->text() == "打开")
    {
        if (m_selectObject == nullptr)
        {
            return;
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_selectObject->path()));

    }
    else if (act->text() == "打开所在文件夹")
    {
        if (m_selectObject == nullptr)
        {
            return;
        }
        QString path = m_selectObject->path();
        QFileInfo info(path);
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absolutePath()));
    }
    else if (act->text() == "刷新")
    {
        m_selectObject = nullptr;
        qDeleteAll(m_items);
        m_items.clear();
        for (const QString& path : m_paths)
        {
            loadFromFolder(path);
        }
    }
}

















