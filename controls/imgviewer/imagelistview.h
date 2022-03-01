#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QWidget>
#include "parentimageviewer.h"

namespace Ui
{
class ImageListView;
}

class ImageListView : public ParentImageViewer
{
    Q_OBJECT

public:
    explicit ImageListView(QWidget* parent = nullptr);
    ~ImageListView();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::ImageListView* ui;
};

#endif // IMAGELISTVIEW_H
