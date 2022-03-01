#ifndef PARENTIMAGEVIEWER_H
#define PARENTIMAGEVIEWER_H

#include <QWidget>
#include <QFileInfo>
#include <QDir>
#include <QWheelEvent>
#include <QApplication>
#include <QDebug>
#include <QImageReader>
#include "imageobject.h"
#include "../base/widgethelper.h"
#include <QTimer>
#include <QAction>
#include <QBuffer>
#include "../../aes/aesfile.h"
using namespace std;


class ParentImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ParentImageViewer(QWidget* parent = nullptr);
    QList<ImageObject*> images;
    void appendFile(QString filePath);
    virtual void recalCellIndexes();
    int columnCount() const;
    void setColumnCount(int columnCount);
    void loadPictureFromFolder(QString path);
    void appendPictureFromFolder(QString path);
    int maxImgSize() const;
    void setMaxImgSize(int maxImgSize);

    QColor backGroundColor() const;
    void setBackGroundColor(const QColor& backGroundColor);
    void getScaledPixmap(QPixmap& pix, QString path);

    bool isEncryptionMode() const;
    void setIsEncryptionMode(bool newIsEncryptionMode);

    bool isShowPopuMenu() const;
    void setIsShowPopuMenu(bool newIsShowPopuMenu);
signals:
    void clickImageObject(ImageObject* cell);
protected:
    WidgetHelper* m_helper;
    int m_columnCount;
    int m_maxImgSize;
    QString m_currentFolderPath;
    QColor m_backGroundColor;
    void resizeEvent(QResizeEvent* event);
    void wheelEvent(QWheelEvent* event);
    void reLoadPictures();
    void loadImageToMemory();
    bool m_isEncryptionMode;
    bool m_isShowPopuMenu;



};

#endif // PARENTPICTRUEWATERFALL_H
