#ifndef IMAGEFILEREMOVEWINDOW_H
#define IMAGEFILEREMOVEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include "../file/fileseacher.h"
#include <QImageReader>
#include <QImageIOHandler>
#include <QMessageBox>
struct RemovedImageFile
{
    QString pathName;
    int width;
    int height;
};

namespace Ui
{
class ImageFileRemoveWindow;
}

class ImageFileRemoveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageFileRemoveWindow(QWidget* parent = nullptr);
    ~ImageFileRemoveWindow();
    void setPath(const QString& path);

private slots:
    void on_btnOpen_clicked();

    void on_btnRemove_clicked();

private:
    Ui::ImageFileRemoveWindow* ui;
    int m_maxImgSize;
    QList<RemovedImageFile> m_removedFiles;
};

#endif // IMAGEFILEREMOVEWINDOW_H
