#include "imagefileremovewindow.h"
#include "ui_imagefileremovewindow.h"

ImageFileRemoveWindow::ImageFileRemoveWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ImageFileRemoveWindow)
{
    ui->setupUi(this);
}

ImageFileRemoveWindow::~ImageFileRemoveWindow()
{
    delete ui;
}

void ImageFileRemoveWindow::setPath(const QString& path)
{
    ui->edtPath->setText(path);
}

void ImageFileRemoveWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path == "")
    {
        return;
    }
    ui->edtPath->setText(path);
}


void ImageFileRemoveWindow::on_btnRemove_clicked()
{
    ui->edtLog->clear();
    m_removedFiles.clear();
    m_maxImgSize = ui->edtMax->text().toInt();
    FileSeacher* seacher = new FileSeacher(this);
    connect(seacher, &FileSeacher::findFileInfo, this, [this](QString rootPath, QFileInfo & fileInfo)
    {
        if (fileInfo.isFile())
        {
            QString suffix = fileInfo.suffix();
            if ((suffix == "jpg") || (suffix == "png") || (suffix == "bmp"))
            {
                QString filePath = fileInfo.absoluteFilePath();
                QImageReader reader(filePath);
                QSize sz = reader.size();
                int w = sz.width() > sz.height() ? sz.width() : sz.height();
                if (w <= this->m_maxImgSize)
                {
                    RemovedImageFile info;
                    info.pathName = filePath;
                    info.width = sz.width();
                    info.height = sz.height();
                    m_removedFiles << info;

                    ui->edtLog->appendPlainText(QString("找到 %1 长:%2,宽:%3").arg(filePath).arg(sz.width()).arg(sz.height()));
                    QApplication::processEvents();
                }


            }

        }
    });
    seacher->startSearch(ui->edtPath->text());
    delete seacher;
    if (m_removedFiles.count() > 0)
    {
        if (QMessageBox::question(this, "提示", "确定删除吗?") == QMessageBox::No)
        {
            return;
        }
        for (const RemovedImageFile& info : qAsConst(m_removedFiles))
        {
            bool ret = QFile::remove(info.pathName);
            ui->edtLog->appendPlainText(QString("删除 %1 长:%2,宽:%3").arg(info.pathName).arg(info.width).arg(info.height));
            qDebug() << ret;
        }


    }

}

