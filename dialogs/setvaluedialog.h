#ifndef SETVALUEDIALOG_H
#define SETVALUEDIALOG_H

#include <QDialog>

namespace Ui {
class SetValueDialog;
}

class SetValueDialog : public QDialog {
    Q_OBJECT

public:
    explicit SetValueDialog(QWidget* parent = nullptr);
    ~SetValueDialog();
    QString value();
    void setValue(QString& value);
    void setCaption(QString caption);
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SetValueDialog* ui;
};
bool setValue(QString title, QString caption, QString& value);

#endif // SETVALUEDIALOG_H
