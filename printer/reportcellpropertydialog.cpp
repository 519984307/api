#include "reportcellpropertydialog.h"
#include "ui_reportcellpropertydialog.h"

ReportCellPropertyDialog::ReportCellPropertyDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ReportCellPropertyDialog)
{
    ui->setupUi(this);
}

ReportCellPropertyDialog::~ReportCellPropertyDialog()
{
    delete ui;
}

ReportCell* ReportCellPropertyDialog::cell() const
{
    return m_cell;
}

void ReportCellPropertyDialog::setCell(ReportCell* newCell)
{
    m_cell = newCell;
    ui->edtText->setText(m_cell->text());
    ui->edtLeft->setText(QString("%1").arg(m_cell->left()));
    ui->edtTop->setText(QString("%1").arg(m_cell->top()));
    ui->edtWidth->setText(QString("%1").arg(m_cell->width()));
    ui->edtHeight->setText(QString("%1").arg(m_cell->height()));
    ui->edtFontSize->setText(QString("%1").arg(m_cell->fontSize()));
    ui->cbbFontName->setCurrentText(m_cell->fontName());
    ui->chkBold->setChecked(m_cell->bold());



}

void ReportCellPropertyDialog::on_btnCancel_clicked()
{
    reject();
}


void ReportCellPropertyDialog::on_btnOk_clicked()
{
    m_cell->setText(ui->edtText->text());
    m_cell->setLeft(ui->edtLeft->text().toDouble());
    m_cell->setTop(ui->edtTop->text().toDouble());
    m_cell->setWidth(ui->edtWidth->text().toDouble());
    m_cell->setHeight(ui->edtHeight->text().toDouble());
    m_cell->setFontSize(ui->edtFontSize->text().toInt());
    m_cell->setFontName(ui->cbbFontName->currentText());
    m_cell->setBold(ui->chkBold->isChecked());

    accept();
}

