#ifndef IMAGECELLVIEWER_H
#define IMAGECELLVIEWER_H

#include <QWidget>
#include "imageobject.h"
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include "../base/widgethelper.h"
#include <QWheelEvent>
#include <QAction>
#include <QMessageBox>
#include <QMimeData>
#include <QClipboard>
#include <QDesktopServices>
namespace Ui
{
class ImageCellViewer;
}

class ImageCellViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCellViewer(QWidget* parent = nullptr);
    ~ImageCellViewer();

    const QList<ImageObject*>& items() const;
    void setItems(const QList<ImageObject*>& newItems);
    void loadFromFolder(QString path);
    void insertFile(int index, QString fileName);
    ImageObject* selectObject() const;
    void setSelectObject(ImageObject* newSelectObject);
    void addMenus();
public slots:
    void onMenuActionTriggered();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::ImageCellViewer* ui;
    QList<ImageObject*> m_items;
    WidgetHelper* m_helper;
    ImageObject* m_selectObject;
    QMimeData* m_mimeData;
    QSet<QString> m_paths;
};

#endif // IMAGECELLVIEWER_H
