#include "imageprocviewerlist.h"
#include "ui_imageprocviewerlist.h"

ImageProcViewerList::ImageProcViewerList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImageProcViewerList)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    selObj = nullptr;
}

ImageProcViewerList::~ImageProcViewerList()
{
    delete ui;
}

void ImageProcViewerList::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(QColor(113, 113, 113)));
    int t = m_helper->itemsTop();
    for (int i = 0; i < procHistoryList.count(); i++)
    {
        ImageProcHistoryObject* obj = procHistoryList.at(i);
        obj->setRect(QRect(16, t, 128, obj->showPix.height()));
        if (selObj == obj)
        {
            QRect selRect(14, t - 2, width() - 30, 132);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(Qt::white);
            painter.drawRect(selRect);
        }
        painter.drawPixmap(obj->rect(), obj->showPix, obj->showPix.rect());
        t = t + 128 + 16;

    }

    painter.end();


}

void ImageProcViewerList::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < procHistoryList.count(); i++)
    {
        ImageProcHistoryObject* obj = procHistoryList.at(i);
        if (obj->rect().contains(curPt))
        {
            selObj = obj;
            break;
        }
    }
    update();

}

void ImageProcViewerList::mouseReleaseEvent(QMouseEvent* event)
{

}

void ImageProcViewerList::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void ImageProcViewerList::mouseMoveEvent(QMouseEvent* event)
{

}
