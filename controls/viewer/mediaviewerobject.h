#ifndef MEDIAVIEWEROBJECT_H
#define MEDIAVIEWEROBJECT_H

#include <QObject>
#include <QPixmap>

enum MediaType
{
    MediaText,
    MediaImage,
    MediaUrl
};

class MediaViewerObject : public QObject
{
    Q_OBJECT
public:
    explicit MediaViewerObject(QObject* parent = nullptr);

    MediaType mediaType() const;
    void setMediaType(const MediaType& mediaType);

    QPixmap mediaImage() const;
    void setMediaImage(const QPixmap& mediaImage);
    void setMediaTypeText(QString typeText);

    QString text() const;
    void setText(const QString& text);

    QString imagePath() const;
    void setImagePath(const QString& imagePath);
    void loadImage();
    void freeImage();

    int id() const;
    void setId(int id);

    QRect rect() const;
    void setRect(const QRect& rect);

    QPixmap snapImage() const;
    void setSnapImage(const QPixmap& snapImage);

    QRect snapRect() const;
    void setSnapRect(const QRect& snapRect);

    QString filePath() const;
    void setFilePath(const QString& filePath);

    QPixmap fileSnapImage() const;
    void setFileSnapImage(const QPixmap& fileSnapImage);

    QPixmap errorImage() const;
    void setErrorImage(const QPixmap& errorImage);

    bool isChecked() const;
    void setChecked(bool isChecked);

    QRect checkRect() const;
    void setCheckRect(const QRect& checkRect);

    QString remark() const;
    void setRemark(const QString& remark);

signals:
private:
    MediaType m_mediaType;
    QPixmap m_mediaImage;
    QPixmap m_snapImage;
    QPixmap m_fileSnapImage;
    QString m_text;
    QString m_imagePath;
    int m_id;
    QRect m_rect;
    QRect m_snapRect;
    QString m_filePath;
    QPixmap m_errorImage;
    bool m_isChecked;
    QRect m_checkRect;
    QString m_remark;

};

#endif // MEDIAVIEWEROBJECT_H
