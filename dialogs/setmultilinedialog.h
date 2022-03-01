#ifndef SETMULTILINEDIALOG_H
#define SETMULTILINEDIALOG_H

#include <QDialog>

namespace Ui
{
class SetMultilineDialog;
}

class SetMultilineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetMultilineDialog(QWidget* parent = nullptr);
    ~SetMultilineDialog();
    void setCaption(QString caption);
    void getValue(QStringList& value);
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SetMultilineDialog* ui;
};
bool SetMultiline(QString title, QString caption, QStringList& value);

#endif // SETMULTILINEDIALOG_H
