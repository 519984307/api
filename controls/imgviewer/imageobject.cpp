#include "imageobject.h"

ImageObject::ImageObject(QObject* parent) : QObject(parent)
{
    m_hasLoad = false;
    m_pix = QPixmap();
    m_isSelected = false;

}

int ImageObject::colIndex() const
{
    return m_colIndex;
}

void ImageObject::setColIndex(int colIndex)
{
    m_colIndex = colIndex;
}

int ImageObject::top() const
{
    return m_top;
}

void ImageObject::setTop(int top)
{
    m_top = top;
}

int ImageObject::height() const
{
    return m_height;
}

void ImageObject::setHeight(int height)
{
    m_height = height;
}

int ImageObject::snapHeight() const
{
    return m_snapHeight;
}

void ImageObject::setSnapHeight(int snapHeight)
{
    m_snapHeight = snapHeight;
}

int ImageObject::snapWidth() const
{
    return m_snapWidth;
}

void ImageObject::setSnapWidth(int snapWidth)
{
    m_snapWidth = snapWidth;
}

int ImageObject::picWidth() const
{
    return m_picWidth;
}

void ImageObject::setPicWidth(int picWidth)
{
    m_picWidth = picWidth;
}

int ImageObject::picHeight() const
{
    return m_picHeight;
}

void ImageObject::setPicHeight(int picHeight)
{
    m_picHeight = picHeight;
}

QString ImageObject::path() const
{
    return m_path;
}

void ImageObject::setPath(const QString& path)
{
    m_path = path;
}

QPixmap ImageObject::pix() const
{
    return m_pix;
}

void ImageObject::setPix(const QPixmap& pix)
{
    m_pix = pix;
}

bool ImageObject::hasLoad() const
{
    return m_hasLoad;
}

void ImageObject::setHasLoad(bool hasLoad)
{
    m_hasLoad = hasLoad;
}

bool ImageObject::isSelected() const
{
    return m_isSelected;
}

void ImageObject::setIsSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

bool ImageObject::oldSelected() const
{
    return m_oldSelected;
}

void ImageObject::setOldSelected(bool oldSelected)
{
    m_oldSelected = oldSelected;
}

QRect ImageObject::rect() const
{
    return m_rect;
}

void ImageObject::setRect(const QRect& rect)
{
    m_rect = rect;
}

QString ImageObject::folderPath() const
{
    return m_folderPath;
}

void ImageObject::setFolderPath(const QString& folderPath)
{
    m_folderPath = folderPath;
}

double ImageObject::aspectRatio() const
{
    return m_aspectRatio;
}

void ImageObject::setAspectRatio(double aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

bool ImageObject::loadImage(bool isEcrypt)
{
    bool ret = false;
    if (m_hasLoad == false)
    {
        if (isEcrypt)
        {
            AesFile* file = new AesFile(this);
            file->decryptAsPixmap(m_path, m_pix);
            delete file;
        }
        else
        {
            m_pix = QPixmap(m_path);
        }

        if (m_pix.isNull())
        {
            if (isEcrypt)
            {

                QImage img = QImage(m_path);
                m_pix = QPixmap::fromImage(img.scaledToWidth(1920));
            }
            else
            {
                QImage img = QImage(m_path);
                m_pix = QPixmap::fromImage(img.scaledToWidth(1920));
            }

        }
        m_hasLoad = true;
        ret = true;
    }
    return ret;
}

void ImageObject::freeImage()
{
    if (m_hasLoad == true)
    {
        m_pix = QPixmap();
        m_snapPix = QPixmap();
        m_hasLoad = false;
    }
}

const QPixmap& ImageObject::snapPix() const
{
    return m_snapPix;
}

void ImageObject::setSnapPix(const QPixmap& newSnapPix)
{
    m_snapPix = newSnapPix;
}

QRect ImageObject::snapRect() const
{
    return m_snapRect;
}

void ImageObject::setSnapRect(const QRect& snapRect)
{
    m_snapRect = snapRect;
}

const QString& ImageObject::fileName() const
{
    return m_fileName;
}

void ImageObject::setFileName(const QString& newFileName)
{
    m_fileName = newFileName;
}
