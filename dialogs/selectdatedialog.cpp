#include "selectdatedialog.h"
#include "ui_selectdatedialog.h"

SelectDateDialog::SelectDateDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SelectDateDialog)
{
    ui->setupUi(this);
    ui->wgtCal->installEventFilter(this);
}

SelectDateDialog::~SelectDateDialog()
{
    delete ui;
}

QString SelectDateDialog::date()
{
    return  ui->wgtCal->selectedDate().toString("yyyy-MM-dd");

}

bool SelectDateDialog::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->wgtCal)
    {
        qDebug() << event->type();
        if (event->type() == QEvent::MouseButtonRelease)
        {
            emit ui->btnOk->click();
        }
    }
    return true;

}

void SelectDateDialog::on_btnCancel_clicked()
{
    reject();
}

void SelectDateDialog::on_btnOk_clicked()
{
    accept();
}

bool selectDateDialog(QLineEdit* edit)
{
    bool b = false;
    SelectDateDialog* dlg = new SelectDateDialog();
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        b = true;
        edit->setText(dlg->date());
    }
    delete  dlg;
    return b;
}
