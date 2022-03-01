#include "horpicturewaterfall.h"
#include "ui_horpicturewaterfall.h"

HorPictureWaterFall::HorPictureWaterFall(QWidget* parent) :
    ParentImageViewer(parent),
    ui(new Ui::HorPictureWaterFall)
{
    ui->setupUi(this);
    m_columnCount = 5;
    m_needCalImageHeight = true;
    setMouseTracking(true);
}

HorPictureWaterFall::~HorPictureWaterFall()
{
    delete ui;
}

int HorPictureWaterFall::getPictruesHeight(int k, int n)
{
    if (m_needCalImageHeight == false)
    {
        ImageObject* cell = images.at(k);
        return cell->snapHeight();
    }
    double sum = 0.0f;
    int tempHeight = 0;
    for (int i = k; i < k + n; i++)
    {

        ImageObject* cell = images.at(i);
        sum += cell->aspectRatio();




    }
    int showWidth = width() - (n + 1) * 12;
    for (int i = k; i < k + n; i++)
    {
        ImageObject* cell = images.at(i);
        double w = showWidth;
        w = w * (cell->aspectRatio() / sum);
        cell->setSnapWidth(w);
        double h = cell->snapWidth();
        h = h / cell->aspectRatio();
        cell->setSnapHeight(h);

        tempHeight = cell->snapHeight();


    }


    return tempHeight;
}

void HorPictureWaterFall::paintEvent(QPaintEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    QRect clientRect(0, -height() * 0.5, width(), height() * 2);

    QPainter painter;
    painter.begin(this);
    painter.fillRect(m_helper->clientRect(), QBrush(m_backGroundColor));
    int allNum = images.count();
    int i = 0;
    int tempHeight = 0;
    int t = m_helper->itemsTop();

    while (allNum > 0)
    {
        int n = allNum >= m_columnCount ? m_columnCount : allNum;
        if (n == 0)
        {
            break;
        }
        tempHeight = getPictruesHeight(i, n);

        int l = 12;
        for (int j = i; j < i + n; j++)
        {
            ImageObject* cell = images.at(j);

            QRect imgRc = QRect(l, t, cell->snapWidth(), cell->snapHeight());

            if (clientRect.contains(imgRc))
            {

                cell->loadImage();
                QRect pixRc = cell->pix().rect();
                if ((pixRc.width() < imgRc.width()) && (pixRc.width() < imgRc.width()))
                {
                    QRect drawRc(imgRc.center().x() - pixRc.width() / 2,
                                 imgRc.center().y() - pixRc.height() / 2,
                                 pixRc.width(), pixRc.height());
                    painter.drawPixmap(drawRc, cell->pix(), pixRc);
                }
                else
                {
                    painter.drawPixmap(imgRc, cell->pix(), pixRc);
                }


            }
            else
            {
                cell->freeImage();
            }
            cell->setRect(imgRc);










            l += cell->snapWidth() + 12;

        }
        t += tempHeight + 12;
        i += n;
        allNum -= n;


    }

    painter.end();
    m_needCalImageHeight = false;


}

void HorPictureWaterFall::resizeEvent(QResizeEvent* event)
{
    m_needCalImageHeight = true;
    ParentImageViewer::resizeEvent(event);

}

void HorPictureWaterFall::mouseMoveEvent(QMouseEvent* event)
{
    update();

}


