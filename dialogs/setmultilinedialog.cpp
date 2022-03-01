#include "setmultilinedialog.h"
#include "ui_setmultilinedialog.h"

SetMultilineDialog::SetMultilineDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetMultilineDialog)
{
    ui->setupUi(this);
}

SetMultilineDialog::~SetMultilineDialog()
{
    delete ui;
}

void SetMultilineDialog::setCaption(QString caption)
{
    ui->lblCaption->setText(caption + ":");
}

void SetMultilineDialog::getValue(QStringList& value)
{
    value = ui->edtInfo->toPlainText().split("\n");
}

void SetMultilineDialog::on_btnCancel_clicked()
{
    reject();
}


void SetMultilineDialog::on_btnOk_clicked()
{
    accept();
}


bool SetMultiline(QString title, QString caption, QStringList& value)
{
    bool b = false;
    SetMultilineDialog* dlg = new SetMultilineDialog();
    dlg->setWindowTitle(title);
    dlg->setCaption(caption);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        dlg->getValue(value);
        b = true;
    }
    delete dlg;
    return b;
}
