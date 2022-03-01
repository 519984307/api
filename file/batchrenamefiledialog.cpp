#include "batchrenamefiledialog.h"
#include "ui_batchrenamefiledialog.h"

BatchRenameFileDialog::BatchRenameFileDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::BatchRenameFileDialog)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(this);
    ui->lvData->setModel(m_model);
    QStringList labels;
    labels << "旧文件名" << "新文件名";
    m_model->setHorizontalHeaderLabels(labels);
}

BatchRenameFileDialog::~BatchRenameFileDialog()
{
    delete ui;
}

void BatchRenameFileDialog::openFolder(QString srcFolder, QString tempFolder)
{
    m_srcFolder = srcFolder  ;
    m_tempFolder = tempFolder;

    //删除文件夹
    FolderOperator* folderOperator = new FolderOperator();
    folderOperator->removeFilesInFolder(tempFolder);
    delete folderOperator;

    //拷贝文件到临时文件夹
    QDir dir(srcFolder);
    QFileInfoList fileInfos = dir.entryInfoList();
    QStandardItem* item;

    int i = 1;
    for (const QFileInfo& fileInfo : qAsConst(fileInfos))
    {
        if (fileInfo.isDir())
        {
            continue;
        }
        QList<QStandardItem*> items;
        item = new QStandardItem();
        item->setText(fileInfo.fileName());
        QString tempFile = tempFolder + "/" + newNoDashUuid() + "." + fileInfo.suffix();
        QFile::copy(fileInfo.absoluteFilePath(), tempFile);
        item->setData(tempFile, Qt::UserRole + 1);
        items << item;

        item = new QStandardItem();
        item->setText(QString("%1").arg(i, 3, 10, QLatin1Char('0')) + "." + fileInfo.suffix());
        items << item;
        m_model->appendRow(items);
        i++;

    }

}

void BatchRenameFileDialog::resetOrder()
{
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        QStandardItem* item = m_model->item(i, 1);
        QFileInfo info(item->text());
        item->setText(QString("%1").arg(i + 1, 3, 10, QLatin1Char('0')) + "." + info.suffix());
    }

}

void BatchRenameFileDialog::on_btnOk_clicked()
{
    //删除文件夹
    FolderOperator* folderOperator = new FolderOperator();
    folderOperator->removeFilesInFolder(m_srcFolder);
    delete folderOperator;

    for (int i = 0; i < m_model->rowCount(); i++)
    {
        QStandardItem* oldItem = m_model->item(i);
        QStandardItem* newItem = m_model->item(i, 1);


        QFile::copy(oldItem->data(Qt::UserRole + 1).toString(), m_srcFolder + "/" + newItem->text());
    }
    close();
}


void BatchRenameFileDialog::on_btnMoveUp_clicked()
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == 0)
    {
        return;
    }

    QList<QStandardItem*> items = m_model->takeRow(row);
    row--;
    m_model->insertRow(row, items);
    ui->lvData->setCurrentIndex(items.at(0)->index());
    resetOrder();
}


void BatchRenameFileDialog::on_btnMoveDown_clicked()
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    int row = index.row();
    if (row == (m_model->rowCount() - 1))
    {
        return;
    }

    QList<QStandardItem*> items = m_model->takeRow(row);
    row++;
    m_model->insertRow(row, items);
    ui->lvData->setCurrentIndex(items.at(0)->index());
    resetOrder();
}

