#include "fnshellviewer.h"
#include "ui_fnshellviewer.h"

FnShellViewer::FnShellViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnShellViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsLeft(0);
    setMouseTracking(true);
}

FnShellViewer::~FnShellViewer()
{
    delete ui;
}

const QString& FnShellViewer::rootPath() const
{
    return m_rootPath;
}

void FnShellViewer::setRootPath(const QString& newRootPath)
{
    m_rootPath = newRootPath;
    qDeleteAll(m_folders);
    m_folders.clear();
    addFolderRect(m_rootPath);
    m_helper->setItemsLeft(0);




    update();
}

void FnShellViewer::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);

    QRect clientRc = m_helper->clientRect();
    painter.setClipRect(clientRc);
    painter.fillRect(clientRc, QBrush(Qt::white));
    int l = m_helper->itemsLeft();
    int n = 0;
    for (FnShellFolderRect* folderRc : qAsConst(m_folders))
    {
        int t = folderRc->itemsTop();
        FnShellItem* selItem = folderRc->selectedItem();
        for (FnShellItem* item : qAsConst(folderRc->items))
        {
            QRect rc(l, t, folderRc->width(), 32);
            item->setRect(rc);
            if (selItem == item)
            {
                painter.fillRect(rc, QColor(204, 232, 255));
            }
            else if (rc.contains(curPt))
            {

                painter.fillRect(rc, QColor(229, 243, 255));
            }
            QRect iconRc(l + 16, t + 4, 24, 24);
            painter.drawPixmap(iconRc, item->icon(), item->icon().rect());
            painter.setPen(Qt::black);
            QRect textRc(l + 60, t, folderRc->width() - 96, 32);
            painter.drawText(textRc, Qt::AlignVCenter | Qt::AlignLeft, item->name());

            t += 32;
        }


        folderRc->setRect(QRect(l, 0, folderRc->width(), height()));
        l += folderRc->width();
        n += folderRc->width();
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l, height());
        l += 1;
        n += 1;
    }
    n += 16;
    m_allFoldersWidth = n;
    if (n > width())
    {


        painter.fillRect(0, height() - 16, width(), 16, QBrush(QColor(240, 240, 240)));

        if (m_horScrollVisble == false)
        {
            m_factor = width();
            m_factor = m_factor / n;

            int w1 = width() * m_factor;
            m_horScrollRect = QRect(0, height() - 16, w1, 16);
            m_horScrollVisble = true;
        }

        painter.fillRect(m_horScrollRect, QBrush(QColor(133, 133, 133)));
    }
    else
    {
        m_helper->setItemsLeft(0);
        m_horScrollVisble = false;
    }
    painter.end();
}

void FnShellViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint curPt = m_helper->cursorPos();
        if (m_horScrollRect.contains(curPt))
        {
            int x = curPt.x() - m_helper->mouseMovePoint().x() ;
            int l = m_horScrollRect.left() + x;
            if (l < 0)
            {
                l = 0;
            }
            if ((l + m_horScrollRect.width()) > width())
            {
                l = width() - m_horScrollRect.width();
            }
            m_horScrollRect = QRect(l,
                                    m_horScrollRect.top(), m_horScrollRect.width(), m_horScrollRect.height());
            m_helper->setMouseMovePoint(curPt);
            double w = m_horScrollRect.left();
            w = w / m_factor;

            m_helper->setItemsLeft(-static_cast<int>(w));
        }
    }

    update();
}

void FnShellViewer::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();

}

void FnShellViewer::mouseDoubleClickEvent(QMouseEvent* event)
{
    FnShellItem* selItem = getSelectItem();
    if (selItem == nullptr)
    {
        return;
    }
    QString path = selItem->path();
    int lv = selItem->folderRect()->level();
    if (selItem->isDir())
    {

        for (int i = m_folders.count() - 1; i >= 0; i--)
        {
            FnShellFolderRect* rc = m_folders.at(i);
            if (rc->level() > lv)
            {

                m_folders.removeAt(i);
                delete  rc;


            }

        }

        addFolderRect(path);
        update();
    }
}

void FnShellViewer::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    QPoint curPt = m_helper->cursorPos();
    for (FnShellFolderRect* folderRc : qAsConst(m_folders))
    {
        if (folderRc->rect().contains(curPt))
        {
            int t = folderRc->itemsTop() + y;
            if (t > 16)
            {
                t = 16;
            }
            folderRc->setItemsTop(t);
        }
    }
    update();



}

void FnShellViewer::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();
}

void FnShellViewer::resizeEvent(QResizeEvent* event)
{
    m_horScrollVisble = false;
    update();
}

WidgetHelper* FnShellViewer::helper() const
{
    return m_helper;
}

void FnShellViewer::setHelper(WidgetHelper* newHelper)
{
    m_helper = newHelper;
}

void FnShellViewer::addFolderRect(QString path)
{
    QDir dir(path);
    FnShellFolderRect* folderRc = new FnShellFolderRect(this);
    folderRc->setLevel(m_folders.count());
    m_folders << folderRc;
    QFileInfoList files = dir.entryInfoList();
    for (QFileInfo fileInfo : qAsConst(files))
    {
        if ((fileInfo.fileName() == ".") || (fileInfo.fileName() == ".."))
        {
            continue;
        }
        folderRc->append(fileInfo);

    }
    calHorScroll();



}

FnShellItem* FnShellViewer::getSelectItem()
{
    QPoint curPt = m_helper->cursorPos();
    for (FnShellFolderRect* folderRc : qAsConst(m_folders))
    {


        for (FnShellItem* item : qAsConst(folderRc->items))
        {
            QRect rc = item->rect();
            if (rc.contains(curPt))
            {
                folderRc->setSelectedItem(item);
                return item;

            }

        }

    }
    return nullptr;
}

void FnShellViewer::calHorScroll()
{

    int n = 0;
    for (FnShellFolderRect* folderRc : qAsConst(m_folders))
    {





        n += folderRc->width();

        n += 1;
    }
    n += 16;
    m_allFoldersWidth = n;
    if (n > width())
    {





        m_factor = width();
        m_factor = m_factor / n;

        int w1 = width() * m_factor;
        m_horScrollRect = QRect(width() - w1, height() - 16, w1, 16);

    }
    double w = m_horScrollRect.left();
    w = w / m_factor;

    m_helper->setItemsLeft(-static_cast<int>(w));


}
