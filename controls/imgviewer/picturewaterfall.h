#ifndef PICTUREWATERFALL_H
#define PICTUREWATERFALL_H

#include <QWidget>
#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QWheelEvent>
#include <thread>
#include <QAction>
#include <QDesktopServices>
#include <QMimeData>
#include <QClipboard>
#include <QDateTime>
#include "imageobject.h"
#include "parentimageviewer.h"

using namespace std;


namespace Ui
{
class PictureWaterFall;
}


class PictureWaterFall : public ParentImageViewer
{
    Q_OBJECT

public:
    explicit PictureWaterFall(QWidget* parent = nullptr);
    ~PictureWaterFall();



    ImageViewStyle getViewStyle() const;
    void setViewStyle(const ImageViewStyle& viewStyle);
    void deslectAll(bool isUpdate = false);
public slots:
    void onMenuTigger();
protected:
    void paintEvent(QPaintEvent* event);



    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::PictureWaterFall* ui;


    bool m_mousedownFlag;
    QPoint m_mousedownPoint;

    int getMinIndex(int* cols, int n);
    void recalCellIndexes();
    bool valueInWindow(int value);
    int getCellWidth();
    ImageViewStyle m_viewStyle;
    void getSelectedFolderPath(QStringList& folderPahts);
    void getSelectedPath(QStringList& paths);



};

#endif // PICTUREWATERFALL_H
