#ifndef SELECTVALUEDIALOG_H
#define SELECTVALUEDIALOG_H

#include <QDialog>

namespace Ui {
class SelectValueDialog;
}

class SelectValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectValueDialog(QWidget *parent = nullptr);
    ~SelectValueDialog();

private:
    Ui::SelectValueDialog *ui;
};

#endif // SELECTVALUEDIALOG_H
