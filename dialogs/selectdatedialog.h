#ifndef SELECTDATEDIALOG_H
#define SELECTDATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>

namespace Ui
{
class SelectDateDialog;
}

class SelectDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDateDialog(QWidget* parent = nullptr);
    ~SelectDateDialog();
    QString date();
    bool eventFilter(QObject* watched, QEvent* event);
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SelectDateDialog* ui;
};
bool selectDateDialog(QLineEdit* edit);

#endif // SELECTDATEDIALOG_H
