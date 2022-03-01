#include "picturewaterfall.h"
#include "ui_picturewaterfall.h"

PictureWaterFall::PictureWaterFall(QWidget* parent) :
    ParentImageViewer(parent),
    ui(new Ui::PictureWaterFall)
{
    ui->setupUi(this);
    m_columnCount = 3;
    m_helper->setItemsTop(16);
    setMouseTracking(true);
    m_mousedownFlag = false;
    QStringList menuNames;
    menuNames << "打开文件" << "打开文件位置" << "复制剪贴板图像为文件" << "复制文件" << "复制文件路径";
    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menuNames[i]);
        connect(act, &QAction::triggered, this, &PictureWaterFall::onMenuTigger);
        addAction(act);
    }

}

PictureWaterFall::~PictureWaterFall()
{
    delete ui;
}





void PictureWaterFall::paintEvent(QPaintEvent* event)
{


    QPoint pt = m_helper->cursorPos();
    QRect clientRect(0, -height() * 4, width(), height() * 8);

    QPainter painter;
    painter.begin(this);

    int* bottoms = new int[m_columnCount];
    for (int i = 0; i < m_columnCount; i++)
    {
        bottoms[i] = 6;
    }


    QRect windowRc = rect();

    painter.fillRect(windowRc, QBrush(QColor(30, 30, 30)));

    int cellWidth = getCellWidth();

    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        int l = (cell->colIndex() + 1) * 6 + cell->colIndex() * cellWidth;
        int colIndex = cell->colIndex();
        QRect rc;
        if (m_viewStyle == vsFitWidthAndHeight)
        {
            rc = QRect(l, bottoms[colIndex] + m_helper->itemsTop(), cellWidth, cellWidth);
        }
        else
        {
            double h = (cellWidth - 12) / cell->aspectRatio();
            cell->setSnapHeight(h);
            cell->setSnapWidth(cellWidth - 12);
            rc = QRect(l, bottoms[colIndex] + m_helper->itemsTop(), cellWidth, h + 12);

        }
        cell->setRect(rc);



        if (clientRect.contains(rc))
        {
            bool ret = cell->loadImage(m_isEncryptionMode);
            if (ret)
            {
                QPixmap pix = cell->pix().copy();
                if (m_viewStyle == vsFitWidthAndHeight)
                {
                    pix = pix.scaled(cellWidth - 12, cellWidth - 12);

                }
                else
                {
                    if (pix.width() > (cellWidth - 12))
                    {
                        pix = pix.scaled(cell->snapWidth(), cell->snapHeight());

                    }

                }
                cell->setSnapPix(pix);

            }




            if (cell->isSelected() == true)
            {
                painter.setPen(QColor(0, 127, 212));

            }
            else
            {
                painter.setPen(Qt::NoPen);
            }

            painter.drawRect(rc);
            QRect pixRc;
            if (m_viewStyle == vsFitWidthAndHeight)
            {
                pixRc = QRect(rc.center().x() - cell->snapPix().width() / 2, rc.center().y() - cell->snapPix().height() / 2, cell->snapPix().width(), cell->snapPix().height());
            }
            else
            {
                pixRc = QRect(l + 6, bottoms[colIndex] + m_helper->itemsTop() + 6, cell->snapWidth(), cell->snapHeight());
            }


            painter.drawPixmap(pixRc, cell->snapPix(), cell->snapPix().rect());



        }
        else
        {
            cell->freeImage();
        }






        bottoms[colIndex] += cell->snapHeight() + 18;





    }

    painter.end();
    delete [] bottoms;




}





void PictureWaterFall::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        return;
    }
    bool isControl = QApplication::keyboardModifiers() == Qt::ControlModifier;
    m_mousedownFlag = true;
    if (isControl == false)
    {
        deslectAll();
    }

    m_mousedownPoint = mapFromGlobal(this->cursor().pos());
    QPoint pt = mapFromGlobal(this->cursor().pos());
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        if (cell->rect().contains(pt))
        {
            if (isControl == false)
            {
                cell->setIsSelected(true);

            }
            else
            {

                cell->setIsSelected(!cell->isSelected());
            }


            cell->setOldSelected(cell->isSelected());

        }

    }
    update();

}

void PictureWaterFall::mouseReleaseEvent(QMouseEvent* event)
{
    m_mousedownFlag = false;

}

void PictureWaterFall::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void PictureWaterFall::mouseMoveEvent(QMouseEvent* event)
{
    if (m_mousedownFlag == true)
    {
        QPoint pt = mapFromGlobal(this->cursor().pos());
        int y = pt.y() - m_mousedownPoint.y();
        int topValue = m_helper->itemsTop();
        topValue += y;
        m_helper->setItemsTop(topValue);
        m_mousedownPoint = pt;
        update();

    }
}

void PictureWaterFall::recalCellIndexes()
{
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        cell->setColIndex(i % m_columnCount);
        cell->setHasLoad(false);

    }

}

bool PictureWaterFall::valueInWindow(int value)
{
    bool ret = false;
    if ((value >= -height())
        && (value <= height() * 1.5))
    {
        ret = true;
    }

    return ret;

}

int PictureWaterFall::getCellWidth()
{
    return (width() - (m_columnCount + 1) * 6) / m_columnCount;
}

void PictureWaterFall::getSelectedFolderPath(QStringList& folderPahts)
{
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        if (cell->isSelected())
        {
            if (!folderPahts.contains(cell->folderPath()))
            {
                folderPahts << cell->folderPath();
            }
        }
    }

}

void PictureWaterFall::getSelectedPath(QStringList& paths)
{
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        if (cell->isSelected())
        {
            if (!paths.contains(cell->path()))
            {
                paths << cell->path();
            }
        }
    }
}



ImageViewStyle PictureWaterFall::getViewStyle() const
{
    return m_viewStyle;
}

void PictureWaterFall::setViewStyle(const ImageViewStyle& viewStyle)
{
    m_viewStyle = viewStyle;
    update();
}

void PictureWaterFall::deslectAll(bool isUpdate)
{
    for (int i = 0; i < images.count(); i++)
    {
        ImageObject* cell = images.at(i);
        cell->setIsSelected(false);
        cell->setIsSelected(false);


    }
    if (isUpdate)
    {
        update();
    }


}

void PictureWaterFall::onMenuTigger()
{
    QAction* act = static_cast<QAction*>(sender());
    QString text = act->text();
    if (text == "打开文件位置")
    {
        QStringList folderPaths;
        getSelectedFolderPath(folderPaths);
        for (int i = 0; i < folderPaths.count(); i++)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(folderPaths[i]));
        }

    }
    else if (text == "打开文件")
    {
        QStringList paths;
        getSelectedPath(paths);
        for (int i = 0; i < paths.count(); i++)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(paths[i]));
        }

    }
    else if (text == "复制文件")
    {
        QStringList paths;
        getSelectedPath(paths);
        QMimeData* data = new QMimeData();
        QList<QUrl> urls;
        for (int i = 0; i < paths.count(); i++)
        {
            urls.append(QUrl::fromLocalFile(paths[i]));
        }
        data->setUrls(urls);
        qApp->clipboard()->setMimeData(data);

    }
    else if (text == "复制文件路径")
    {
        QStringList paths;
        getSelectedPath(paths);

        qApp->clipboard()->setText(paths.join("\r\n"));

    }
    else if (text == "复制剪贴板图像为文件")
    {
        if (!qApp->clipboard()->pixmap().isNull())
        {
            QPixmap pix = qApp->clipboard()->pixmap();
            QDateTime d = QDateTime::currentDateTime();
            QString path = m_currentFolderPath + "/" + d.toString("yyyyMMddhhmms") + ".jpg";
            pix.save(path, "jpg");
            appendFile(path);
        }
    }


}



