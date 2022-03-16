#include "imagefilterwindow.h"
#include "ui_imagefilterwindow.h"

ImageFilterWindow::ImageFilterWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ImageFilterWindow)
{
    ui->setupUi(this);
    initComboboxValues();
    m_model = new QStandardItemModel(this);
    ui->lvData->setModel(m_model);
    QStringList labels;
    labels << "文件名" << "宽" << "高"  << "后缀" << "路径文件名";
    m_model->setHorizontalHeaderLabels(labels);
    QButtonGroup* grp1 = new QButtonGroup(this);
    grp1->addButton(ui->rdSize);
    grp1->addButton(ui->rdWidth);
    grp1->addButton(ui->rdHeight);
    grp1->addButton(ui->rdWidthOrHeight);
    grp1->addButton(ui->rdSizeLage);
    ui->rdSize->setChecked(true);

    QButtonGroup* grp2 = new QButtonGroup(this);
    grp2->addButton(ui->rdIgnore);
    grp2->addButton(ui->rdHor);
    grp2->addButton(ui->rdVer);
    ui->rdIgnore->setChecked(true);

}

ImageFilterWindow::~ImageFilterWindow()
{
    delete ui;
}

void ImageFilterWindow::setPath(const QString& path)
{
    ui->edtPath->setText(path);

}

void ImageFilterWindow::initComboboxValues()
{
    QString values[] = {"128", "256", "1080", "1920", "2160", "3840", "4320", "7680"};
    for (QString& v : values)
    {
        ui->cbbWidth->addItem(v);
        ui->cbbHeight->addItem(v);
    }

}

void ImageFilterWindow::operatorFiles(bool bDeleteSrc)
{
    QString path = selectFolderPath();
    if (path == "")
    {
        return;
    }
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        QString destPath = path + "/" + m_model->item(i)->text();
        QString srcPath = m_model->item(i, 4)->text();
        QFileInfo info(destPath);
        if (info.exists())
        {
            destPath = path + "/" + newNoDashUuid() + "." + info.suffix() ;
        }
        QFile::copy(srcPath, destPath);
        if (bDeleteSrc)
        {
            QFile::remove(srcPath);
        }
    }
    emit ui->btnCheck->clicked();
}

void ImageFilterWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path == "")
    {
        return;
    }
    ui->edtPath->setText(path);
}


void ImageFilterWindow::on_btnCheck_clicked(bool checked)
{
    FileSeacher* fileSearcher = new FileSeacher(this);
    m_model->removeRows(0, m_model->rowCount());
    m_selWidth = ui->cbbWidth->currentText().toInt();
    m_selHeight = ui->cbbHeight->currentText().toInt();
    connect(fileSearcher, &FileSeacher::findFileInfo, this, [this](QString rootPath, QFileInfo & fileInfo)
    {
        if (fileInfo.isDir())
        {
            return;
        }

        QImageReader reader(fileInfo.absoluteFilePath());
        QSize sz = reader.size();
        bool isFit1 = true;
        if (ui->rdSize->isChecked() == true)
        {
            isFit1 = ((sz.width() == m_selWidth) && (sz.height() == m_selHeight)) ? true : false;
        }
        if (ui->rdWidthOrHeight->isChecked() == true)
        {
            isFit1 = ((sz.width() == m_selWidth) || (sz.height() == m_selHeight)) ? true : false;
        }
        else if (ui->rdWidth->isChecked() == true)
        {
            isFit1 = (sz.width() == m_selWidth)  ? true : false;
        } if (ui->rdHeight->isChecked() == true)
        {
            isFit1 = (sz.height() == m_selHeight)  ? true : false;
        }
        else  if (ui->rdSizeLage->isChecked() == true)
        {
            isFit1 = ((sz.width() >= m_selWidth) && (sz.height() >= m_selHeight)) ? true : false;
        }

        bool isFit2 = true;

        if (ui->rdIgnore->isChecked())
        {
            isFit2 = true;
        }
        else if (ui->rdHor->isChecked())
        {
            isFit2 = sz.width() >= sz.height() ? true : false;
        }
        else if (ui->rdVer->isChecked())
        {
            isFit2 = sz.width() < sz.height() ? true : false;
        }

        if (isFit1 && isFit2)
        {
            QList<QStandardItem*> items;
            QStandardItem* item = nullptr;

            item = new QStandardItem();
            item->setText(fileInfo.fileName());
            items << item;

            item = new QStandardItem();
            item->setText(QString("%1").arg(sz.width()));
            items << item;

            item = new QStandardItem();
            item->setText(QString("%1").arg(sz.height()));
            items << item;

            item = new QStandardItem();
            item->setText(fileInfo.suffix());
            items << item;


            item = new QStandardItem();
            item->setText(fileInfo.absoluteFilePath());
            items << item;

            m_model->appendRow(items);

        }



    });
    fileSearcher->startSearch(ui->edtPath->text());
    delete fileSearcher;

}


void ImageFilterWindow::on_lvData_doubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }
    QString path = m_model->item(index.row(), 4)->text();
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}


void ImageFilterWindow::on_cbbWidth_currentIndexChanged(const QString& arg1)
{
    QMap<QString, QString> imgSize;
    imgSize["3840"] = "2160";
    imgSize["1920"] = "1080";
    imgSize["7680"] = "4320";
    imgSize["1080"] = "1920";

    ui->cbbHeight->setCurrentText(imgSize[arg1]);
}


void ImageFilterWindow::on_btnCopyTo_clicked()
{
    operatorFiles(false);
}


void ImageFilterWindow::on_btnMoveTo_clicked()
{
    operatorFiles(true);
}

