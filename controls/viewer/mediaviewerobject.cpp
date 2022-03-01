#include "mediaviewerobject.h"

MediaViewerObject::MediaViewerObject(QObject* parent) : QObject(parent)
{
    m_fileSnapImage = QPixmap();
    m_errorImage = QPixmap();
    m_isChecked = false;

}

MediaType MediaViewerObject::mediaType() const
{
    return m_mediaType;
}

void MediaViewerObject::setMediaType(const MediaType& mediaType)
{
    m_mediaType = mediaType;
}

QPixmap MediaViewerObject::mediaImage() const
{
    return m_mediaImage;
}

void MediaViewerObject::setMediaImage(const QPixmap& mediaImage)
{
    m_mediaImage = mediaImage;
}

void MediaViewerObject::setMediaTypeText(QString typeText)
{
    if (typeText == "text")
    {
        setMediaType(MediaText);
    }
    else if (typeText == "image")
    {
        setMediaType(MediaImage);
    }
    else if (typeText == "url")
    {
        setMediaType(MediaUrl);
    }
}

QString MediaViewerObject::text() const
{
    return m_text;
}

void MediaViewerObject::setText(const QString& text)
{
    m_text = text;
}

QString MediaViewerObject::imagePath() const
{
    return m_imagePath;
}

void MediaViewerObject::setImagePath(const QString& imagePath)
{
    m_imagePath = imagePath;

}

void MediaViewerObject::loadImage()
{
    if (!m_mediaImage.isNull())
    {
        return;
    }
    m_mediaImage = QPixmap(m_imagePath);
    if (m_mediaImage.isNull())
    {
        m_mediaImage = m_errorImage;
    }

    m_snapImage = m_mediaImage.scaledToWidth(432, Qt::SmoothTransformation);
    m_snapRect = m_snapImage.rect();
}

void MediaViewerObject::freeImage()
{
    m_mediaImage = QPixmap();
    m_snapImage = QPixmap();

}

int MediaViewerObject::id() const
{
    return m_id;
}

void MediaViewerObject::setId(int id)
{
    m_id = id;
}

QRect MediaViewerObject::rect() const
{
    return m_rect;
}

void MediaViewerObject::setRect(const QRect& rect)
{
    m_rect = rect;
}

QPixmap MediaViewerObject::snapImage() const
{
    return m_snapImage;
}

void MediaViewerObject::setSnapImage(const QPixmap& snapImage)
{
    m_snapImage = snapImage;
}

QRect MediaViewerObject::snapRect() const
{
    return m_snapRect;
}

void MediaViewerObject::setSnapRect(const QRect& snapRect)
{
    m_snapRect = snapRect;
}

QString MediaViewerObject::filePath() const
{
    return m_filePath;
}

void MediaViewerObject::setFilePath(const QString& filePath)
{
    m_filePath = filePath;
}

QPixmap MediaViewerObject::fileSnapImage() const
{
    return m_fileSnapImage;
}

void MediaViewerObject::setFileSnapImage(const QPixmap& fileSnapImage)
{
    m_fileSnapImage = fileSnapImage;
}

QPixmap MediaViewerObject::errorImage() const
{
    return m_errorImage;
}

void MediaViewerObject::setErrorImage(const QPixmap& errorImage)
{
    m_errorImage = errorImage;
}

bool MediaViewerObject::isChecked() const
{
    return m_isChecked;
}

void MediaViewerObject::setChecked(bool isChecked)
{
    m_isChecked = isChecked;
}

QRect MediaViewerObject::checkRect() const
{
    return m_checkRect;
}

void MediaViewerObject::setCheckRect(const QRect& checkRect)
{
    m_checkRect = checkRect;
}

QString MediaViewerObject::remark() const
{
    return m_remark;
}

void MediaViewerObject::setRemark(const QString &remark)
{
    m_remark = remark;
}
