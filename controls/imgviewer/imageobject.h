#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QObject>
#include <QWidget>
#include "../api/aes/aesfile.h"
enum ImageViewStyle
{
    vsFitWidth,
    vsFitWidthAndHeight
};
class ImageObject : public QObject
{
    Q_OBJECT
public:
    explicit ImageObject(QObject* parent = nullptr);

    int colIndex() const;
    void setColIndex(int colIndex);

    int top() const;
    void setTop(int top);

    int height() const;
    void setHeight(int height);

    int snapHeight() const;
    void setSnapHeight(int snapHeight);

    int snapWidth() const;
    void setSnapWidth(int snapWidth);

    int picWidth() const;
    void setPicWidth(int picWidth);

    int picHeight() const;
    void setPicHeight(int picHeight);

    QString path() const;
    void setPath(const QString& path);

    QPixmap pix() const;
    void setPix(const QPixmap& pix);

    bool hasLoad() const;
    void setHasLoad(bool hasLoad);

    bool isSelected() const;
    void setIsSelected(bool isSelected);

    bool oldSelected() const;
    void setOldSelected(bool oldSelected);

    QRect rect() const;
    void setRect(const QRect& rect);

    QString folderPath() const;
    void setFolderPath(const QString& folderPath);

    double aspectRatio() const;
    void setAspectRatio(double aspectRatio);

    bool loadImage(bool isEcrypt = false);
    void freeImage();

    const QPixmap& snapPix() const;
    void setSnapPix(const QPixmap& newSnapPix);

    QRect snapRect() const;
    void setSnapRect(const QRect& snapRect);

    const QString& fileName() const;
    void setFileName(const QString& newFileName);

signals:
private:
    int m_colIndex;
    int m_top;
    int m_height;
    int m_snapHeight;
    int m_snapWidth;
    int m_picWidth;
    int m_picHeight;
    QString m_path;
    QPixmap m_pix;
    QPixmap m_snapPix;
    bool m_hasLoad = false;
    bool m_isSelected = false;
    bool m_oldSelected = false;
    QRect m_rect;
    QString m_folderPath;
    double m_aspectRatio = 0.0f;
    QRect m_snapRect;
    QString m_fileName;

};

#endif // IMAGEOBJECT_H
