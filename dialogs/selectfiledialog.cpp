#include "selectfiledialog.h"
#include "ui_selectfiledialog.h"

SelectFileDialog::SelectFileDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SelectFileDialog)
{
    ui->setupUi(this);
    m_model = new QFileSystemModel(this);
    m_model->setRootPath(QApplication::applicationDirPath());
    ui->tvData->setModel(m_model);
    ui->tvData->setColumnHidden(1, true);
    ui->tvData->setColumnHidden(2, true);
    ui->tvData->setColumnHidden(3, true);
    ui->tvData->resizeColumnToContents(0);
}

SelectFileDialog::~SelectFileDialog()
{
    delete ui;
}

QFileInfo SelectFileDialog::getFileInfo()
{
    QModelIndex index = ui->tvData->currentIndex();
    QFileInfo info = m_model->fileInfo(index);
    return info;
}

void SelectFileDialog::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path == "") {
        return;
    }
    ui->edtPath->setText(path);
    m_model->setRootPath(path);
    ui->tvData->setRootIndex(m_model->index(path));
}

void SelectFileDialog::on_btnOk_clicked()
{
    accept();
}

void SelectFileDialog::on_btnCancel_clicked()
{
    reject();
}
