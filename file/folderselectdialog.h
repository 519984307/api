#ifndef FOLDERSELECTDIALOG_H
#define FOLDERSELECTDIALOG_H

#include <QDialog>
#include <QSet>
#include <QListWidget>
#include <QFileDialog>
#include "../api/config/stringlistinfo.h"

namespace Ui
{
class FolderSelectDialog;
}

class FolderSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FolderSelectDialog(QWidget* parent = nullptr);
    ~FolderSelectDialog();
    QString path();

private slots:


    void on_btnCancel_clicked();

    void on_btnOk_clicked();



    void on_btnOpen_clicked();

    void on_lvData_itemClicked(QListWidgetItem* item);

private:
    Ui::FolderSelectDialog* ui;
    QSet<QString> m_paths;
    StringListInfo m_saveInfos;
};
QString selectFolderPath();

#endif // FOLDERSELECTDIALOG_H
