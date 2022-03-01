#include "imagelistview.h"
#include "ui_imagelistview.h"

ImageListView::ImageListView(QWidget* parent) :
    ParentImageViewer(parent),
    ui(new Ui::ImageListView)
{
    ui->setupUi(this);
    m_helper->setItemsTop(16);
    m_helper->setMaxTop(16);
}

ImageListView::~ImageListView()
{
    delete ui;
}

void ImageListView::paintEvent(QPaintEvent* event)
{

    QPainter painter;
    painter.begin(this);
    QRect clientRect = m_helper->clientRect();
    painter.fillRect(clientRect, QColor(113, 113, 113));
    int t = m_helper->itemsTop();
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        if (!cell->hasLoad())
        {
            cell->loadImage();
            QPixmap snapPix = cell->pix().scaledToWidth(width() - 32);
            cell->setSnapPix(snapPix);
        }
        QRect rc(16, t, width() - 32, cell->snapPix().height());
        cell->setRect(rc);
        painter.drawPixmap(rc, cell->snapPix(), cell->snapPix().rect());

        QRect textRc(16, t + rc.height(), width() - 32, 24);
        painter.setPen(Qt::white);
        painter.drawText(textRc, Qt::AlignCenter, cell->fileName());

        t += rc.height() + 40;
    }

    painter.end();
}

void ImageListView::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        if (cell->rect().contains(curPt))
        {
            emit clickImageObject(cell);
            break;
        }
    }

}
