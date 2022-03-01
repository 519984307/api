#include "imagezoomandgray.h"

ImageZoomAndGray::ImageZoomAndGray(QObject* parent) : QObject(parent)
{
    m_zoomWidth = 40;
    m_zoomHeight = 40;

}

int ImageZoomAndGray::zoomWidth() const
{
    return m_zoomWidth;
}

void ImageZoomAndGray::setZoomWidth(int zoomWidth)
{
    m_zoomWidth = zoomWidth;
}

int ImageZoomAndGray::zoomHeight() const
{
    return m_zoomHeight;
}

void ImageZoomAndGray::setZoomHeight(int zoomHeight)
{
    m_zoomHeight = zoomHeight;
}

QString ImageZoomAndGray::exportFolder() const
{
    return m_exportFolder;
}

void ImageZoomAndGray::setExportFolder(const QString& exportFolder)
{
    m_exportFolder = exportFolder;

}

void ImageZoomAndGray::startProc()
{
    int i = 1;
    for (QString path : imageFileNames)
    {
        QPixmap pix(path);
        pix = pix.scaled(m_zoomWidth, m_zoomHeight);
        QImage img = pix.toImage();
        img = toGray(img);
        img.save(m_exportFolder + QString("%1.jpg").arg(i));
        i++;
    }
    QApplication::processEvents();

}

void ImageZoomAndGray::openFolder(QString path)
{
    QDir dir(path);
    QFileInfoList fileList = dir.entryInfoList();
    for (QFileInfo info : fileList)
    {
        if (info.suffix() == "jpg")
        {
            imageFileNames << info.absoluteFilePath();
        }


    }


}
QImage ImageZoomAndGray::toGray(QImage image)
{
    int height = image.height();
    int width = image.width();
    QImage ret(width, height, QImage::Format_Indexed8);
    ret.setColorCount(256);
    for (int i = 0; i < 256; i++)
    {
        ret.setColor(i, qRgb(i, i, i));
    }
    switch (image.format())
    {
    case QImage::Format_Indexed8:
        for (int i = 0; i < height; i ++)
        {
            const uchar* pSrc = (uchar*)image.constScanLine(i);
            uchar* pDest = (uchar*)ret.scanLine(i);
            memcpy(pDest, pSrc, width);
        }
        break;
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
        for (int i = 0; i < height; i ++)
        {
            const QRgb* pSrc = (QRgb*)image.constScanLine(i);
            uchar* pDest = (uchar*)ret.scanLine(i);

            for (int j = 0; j < width; j ++)
            {
                pDest[j] = qGray(pSrc[j]);
            }
        }
        break;
    }
    return ret;
}

