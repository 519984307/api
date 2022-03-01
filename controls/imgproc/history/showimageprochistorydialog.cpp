#include "showimageprochistorydialog.h"
#include "ui_showimageprochistorydialog.h"

ShowImageProcHistoryDialog::ShowImageProcHistoryDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ShowImageProcHistoryDialog)
{
    ui->setupUi(this);
    m_list = new ImageProcViewerList(ui->wgtClient);
    addWidgetToPage(ui->wgtClient, m_list);
}

ShowImageProcHistoryDialog::~ShowImageProcHistoryDialog()
{
    delete ui;
}

const QList<ImageProcHistoryObject*>& ShowImageProcHistoryDialog::procHistoryList() const
{
    return m_procHistoryList;
}

void ShowImageProcHistoryDialog::setProcHistoryList(const QList<ImageProcHistoryObject*>& newProcHistoryList)
{
    m_procHistoryList = newProcHistoryList;
    m_list->procHistoryList = m_procHistoryList;
    m_list->update();
}

ImageProcHistoryObject* ShowImageProcHistoryDialog::selObj()
{
    return m_list->selObj;
}

void ShowImageProcHistoryDialog::on_btnCancel_clicked()
{
    reject();
}


void ShowImageProcHistoryDialog::on_btnOk_clicked()
{
    if (m_list->selObj == nullptr)
    {
        QMessageBox::information(this, "提示", "请选择要恢复的记录");
        return;
    }
    accept();
}

