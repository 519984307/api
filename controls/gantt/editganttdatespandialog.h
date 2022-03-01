#ifndef EDITGANTTDATESPANDIALOG_H
#define EDITGANTTDATESPANDIALOG_H

#include <QDialog>
#include "gantttask.h"

namespace Ui
{
class EditGanttDateSpanDialog;
}

class EditGanttDateSpanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGanttDateSpanDialog(QWidget* parent = nullptr);
    ~EditGanttDateSpanDialog();

    GanttTask* task() const;
    void setTask(GanttTask* newTask);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::EditGanttDateSpanDialog* ui;
    GanttTask* m_task;
};

#endif // EDITGANTTDATESPANDIALOG_H
