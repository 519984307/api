#ifndef BATCHRENAMEFILEDIALOG_H
#define BATCHRENAMEFILEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDir>
#include <QFileInfoList>
#include "../api/global/globaldata.h"
#include "../api/file/folderoperator.h"


namespace Ui
{
class BatchRenameFileDialog;
}

class BatchRenameFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatchRenameFileDialog(QWidget* parent = nullptr);
    ~BatchRenameFileDialog();
    void openFolder(QString srcFolder, QString tempFolder);
    void resetOrder();

private slots:
    void on_btnOk_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

private:
    Ui::BatchRenameFileDialog* ui;
    QStandardItemModel* m_model;
    QString m_srcFolder;
    QString m_tempFolder;
};

#endif // BATCHRENAMEFILEDIALOG_H
