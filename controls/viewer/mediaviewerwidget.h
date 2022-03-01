#ifndef MEDIAVIEWERWIDGET_H
#define MEDIAVIEWERWIDGET_H

#include <QWidget>
#include "mediaviewerobject.h"
#include "../base/widgethelper.h"
#include <QRect>
#include <QPainter>
#include <QWheelEvent>
#include <QFileIconProvider>
#include <QAction>

namespace Ui
{
class MediaViewerWidget;
}

class MediaViewerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaViewerWidget(QWidget* parent = nullptr);
    ~MediaViewerWidget();
    QList<MediaViewerObject*> m_mediaObjects;
    void addMediaObject(MediaViewerObject* media);
    void insertMediaObject(MediaViewerObject* media, int index);
    QRect rect() const;
    void setRect(const QRect& rect);
    ///清空数据
    void clearMediaObjects();
    void addMenuNames(QStringList& menuNames);
    MediaViewerObject* getSelectedMedia();
    void removeMedia(MediaViewerObject* media);
    void removeMedia(int id);
    QPixmap errorImage() const;
    void setErrorImage(const QPixmap& errorImage);
    void checkAll();
    void getCheckedMedias(QList<MediaViewerObject*>& medias);
    ///反向勾选
    void reverseCheck();
    void reverseList();

    bool isLight() const;
    void setLight(bool isLight);

signals:
    void onMouseDoubleClick(MediaViewerObject* media);
    void menuItemClick(QAction* action, MediaViewerObject* media);

public slots:
    void onMenuItemClick();
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::MediaViewerWidget* ui;
    WidgetHelper* m_helper;
    QRect m_rect;
    MediaViewerObject* m_selectMedia;
    QPixmap m_errorImage;
    bool m_isLight;

};

#endif // MEDIAVIEWERWIDGET_H
