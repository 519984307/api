#ifndef PIXMAPVIEWER_H
#define PIXMAPVIEWER_H

#include <QPainter>
#include <QPixmap>
#include <QWheelEvent>
#include <QWidget>
#include "./base/widgethelper.h"
#include <QAction>
#include <QClipboard>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QMimeData>
#include <memory>
#include <QMatrix>
namespace Ui
{
class PixmapViewer;
}

class PixmapViewer : public QWidget
{
    Q_OBJECT

public:
    explicit PixmapViewer(QWidget* parent = nullptr);
    ~PixmapViewer();
    void paintEvent(QPaintEvent* event);
    void setImage(QPixmap& image);
    void setFactor(double factor);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
    void loadFromFile(QString filePath);
    QString filePath() const;
    void setFilePath(const QString& filePath);



    bool autoFited() const;
    void setAutoFited(bool autoFited);
    void autoFit();

public slots:
    void onMenuItemTrigger();
private:
    Ui::PixmapViewer* ui;
    QPixmap m_image;
    QPixmap m_tempPix;
    double m_factor;
    QPoint m_mousedownPoint;
    QPoint m_startPoint;
    bool m_mousedownFlag;
    WidgetHelper* m_helper;
    QString m_filePath;
    bool m_autoFited;
    QMimeData* m_data;
    void addMenus();
};

#endif // PIXMAPVIEWER_H
