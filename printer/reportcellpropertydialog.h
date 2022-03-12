#ifndef REPORTCELLPROPERTYDIALOG_H
#define REPORTCELLPROPERTYDIALOG_H

#include <QDialog>
#include "reportcell.h"

namespace Ui
{
class ReportCellPropertyDialog;
}

class ReportCellPropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportCellPropertyDialog(QWidget* parent = nullptr);
    ~ReportCellPropertyDialog();


    ReportCell* cell() const;
    void setCell(ReportCell* newCell);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::ReportCellPropertyDialog* ui;
    ReportCell* m_cell;
};

#endif // REPORTCELLPROPERTYDIALOG_H
