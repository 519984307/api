#include "imagecut.h"

ImageCut::ImageCut(QObject* parent) : QObject(parent)
{

}

QString ImageCut::srcPath() const
{
    return m_srcPath;
}

void ImageCut::setSrcPath(const QString& srcPath)
{
    m_srcPath = srcPath;
}

QString ImageCut::getExportFolder() const
{
    return m_exportFolder;
}

void ImageCut::setExportFolder(const QString& value)
{
    m_exportFolder = value;
}

void ImageCut::cutByNumbers(int hor, int ver)
{
    QPixmap pix = QPixmap(m_srcPath);
    int n = 1;
    int w = pix.width() / hor;
    int h = pix.height() / ver;
    QFileInfo info(m_srcPath);
    QString suffix = info.suffix();
    for (int j = 0; j < ver; j++)
    {
        for (int i = 0; i < hor; i++)
        {
            QPixmap subPix = pix.copy(i * w, j * h, w, h);
            subPix.save(m_exportFolder + QString("%1." + suffix).arg(n));
            n++;
        }
    }

}
