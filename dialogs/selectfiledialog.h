#ifndef SELECTFILEDIALOG_H
#define SELECTFILEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace Ui {
class SelectFileDialog;
}

class SelectFileDialog : public QDialog {
    Q_OBJECT

public:
    explicit SelectFileDialog(QWidget* parent = nullptr);
    ~SelectFileDialog();
    QFileInfo getFileInfo();

private slots:

    void on_btnOpen_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SelectFileDialog* ui;
    QFileSystemModel* m_model;
    QTreeView* m_cbbTvData;
};

#endif // SELECTFILEDIALOG_H
