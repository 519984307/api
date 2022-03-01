#ifndef SHOWIMAGEPROCHISTORYDIALOG_H
#define SHOWIMAGEPROCHISTORYDIALOG_H

#include <QDialog>
#include "imageprochistoryobject.h"
#include "../imageprocviewerlist.h"
#include "../api/controls/base/fnwidgetapi.h"
#include <QMessageBox>

namespace Ui
{
class ShowImageProcHistoryDialog;
}

class ShowImageProcHistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowImageProcHistoryDialog(QWidget* parent = nullptr);
    ~ShowImageProcHistoryDialog();

    const QList<ImageProcHistoryObject*>& procHistoryList() const;
    void setProcHistoryList(const QList<ImageProcHistoryObject*>& newProcHistoryList);
    ImageProcHistoryObject* selObj();
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::ShowImageProcHistoryDialog* ui;
    QList<ImageProcHistoryObject*> m_procHistoryList;
    ImageProcViewerList* m_list;
};

#endif // SHOWIMAGEPROCHISTORYDIALOG_H
