#ifndef IMAGEFILTERWINDOW_H
#define IMAGEFILTERWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QStandardItemModel>

#include "../api/file/fileseacher.h"
#include "../api/file/folderselectdialog.h"
#include <QDesktopServices>
#include <QFile>
#include <QButtonGroup>
#include "../api/global/globaldata.h"

namespace Ui
{
class ImageFilterWindow;
}

class ImageFilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageFilterWindow(QWidget* parent = nullptr);
    ~ImageFilterWindow();
    void setPath(const QString& path);
    void initComboboxValues();
    void operatorFiles(bool bDeleteSrc = false);

private slots:
    void on_btnOpen_clicked();

    void on_btnCheck_clicked(bool checked);

    void on_lvData_doubleClicked(const QModelIndex& index);

    void on_cbbWidth_currentIndexChanged(const QString& arg1);

    void on_btnCopyTo_clicked();

    void on_btnMoveTo_clicked();

private:
    Ui::ImageFilterWindow* ui;
    QStandardItemModel* m_model;
    int m_selWidth;
    int m_selHeight;
};

#endif // IMAGEFILTERWINDOW_H
