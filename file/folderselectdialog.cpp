#include "folderselectdialog.h"
#include "ui_folderselectdialog.h"

FolderSelectDialog::FolderSelectDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FolderSelectDialog)
{
    ui->setupUi(this);
    m_saveInfos.setFileName("savePath.txt");
    m_saveInfos.loadInfo();
    for (const QString& s : m_saveInfos)
    {
        m_paths << s;
        ui->lvData->addItem(s);
    }
}

FolderSelectDialog::~FolderSelectDialog()
{
    m_saveInfos.clear();
    for (const QString& s : qAsConst(m_paths))
    {
        m_saveInfos << s;

    }
    m_saveInfos.saveInfo();

    delete ui;
}

QString FolderSelectDialog::path()
{
    return ui->edtPath->text();

}




void FolderSelectDialog::on_btnCancel_clicked()
{
    reject();
}


void FolderSelectDialog::on_btnOk_clicked()
{
    accept();
}





void FolderSelectDialog::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path == "")
    {
        return;
    }
    ui->edtPath->setText(path);
    if (!m_paths.contains(path))
    {
        ui->lvData->addItem(path);
        m_paths << path;
    }

}


QString selectFolderPath()
{
    QString path = "";
    FolderSelectDialog* dlg = new FolderSelectDialog();
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        path = dlg->path();

    }
    delete dlg;

    return path;
}

void FolderSelectDialog::on_lvData_itemClicked(QListWidgetItem* item)
{
    ui->edtPath->setText(item->text());
}

