#include "editganttdatespandialog.h"
#include "ui_editganttdatespandialog.h"

EditGanttDateSpanDialog::EditGanttDateSpanDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::EditGanttDateSpanDialog)
{
    ui->setupUi(this);
}

EditGanttDateSpanDialog::~EditGanttDateSpanDialog()
{
    delete ui;
}

void EditGanttDateSpanDialog::on_btnCancel_clicked()
{
    reject();

}


void EditGanttDateSpanDialog::on_btnOk_clicked()
{
    m_task->setStartDate(ui->dtpStart->date());
    m_task->setEndDate(ui->dtpEnd->date());
    m_task->setValue("起始时间", ui->dtpStart->date().toString("yyyy-MM-dd"));
    m_task->setValue("截止时间", ui->dtpEnd->date().toString("yyyy-MM-dd"));
    accept();
}

GanttTask* EditGanttDateSpanDialog::task() const
{
    return m_task;
}

void EditGanttDateSpanDialog::setTask(GanttTask* newTask)
{
    m_task = newTask;
    QDate d;

    ui->dtpStart->setDate(m_task->startDate());
    ui->dtpEnd->setDate(m_task->endDate());
}

