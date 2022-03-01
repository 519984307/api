#include "setvaluedialog.h"
#include "ui_setvaluedialog.h"

SetValueDialog::SetValueDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SetValueDialog)
{
    ui->setupUi(this);
}

SetValueDialog::~SetValueDialog()
{
    delete ui;
}

void SetValueDialog::setValue(QString& value)
{
    ui->edtValue->setText(value);
}

void SetValueDialog::setCaption(QString caption)
{
    ui->lblCaption->setText(caption + "：");
}

QString SetValueDialog::value()
{
    return ui->edtValue->text();
}

void SetValueDialog::on_btnCancel_clicked()
{
    reject();
}

void SetValueDialog::on_btnOk_clicked()
{
    accept();
}

bool setValue(QString title, QString caption, QString& value)
{
    bool f = false;
    SetValueDialog* dlg = new SetValueDialog(nullptr);
    dlg->setWindowTitle(title);
    dlg->setCaption(caption);
    dlg->setValue(value);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted) {
        value = dlg->value();
        f = true;
    }
    delete dlg;
    return f;
}
