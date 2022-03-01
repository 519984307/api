#include "selectvaluedialog.h"
#include "ui_selectvaluedialog.h"

SelectValueDialog::SelectValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectValueDialog)
{
    ui->setupUi(this);
}

SelectValueDialog::~SelectValueDialog()
{
    delete ui;
}
