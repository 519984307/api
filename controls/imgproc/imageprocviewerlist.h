#ifndef IMAGEPROCVIEWERLIST_H
#define IMAGEPROCVIEWERLIST_H

#include <QWidget>
#include "../base/widgethelper.h"
#include "./history/imageprochistoryobject.h"

namespace Ui
{
class ImageProcViewerList;
}
class ImageProcHistoryObject;
class ImageProcViewerList : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcViewerList(QWidget* parent = nullptr);
    ~ImageProcViewerList();
    QList<ImageProcHistoryObject*> procHistoryList;
    ImageProcHistoryObject* selObj;
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::ImageProcViewerList* ui;
    WidgetHelper* m_helper;

};

#endif // IMAGEPROCVIEWERLIST_H
