#include "clipboardviewdialog.h"
#include "ui_clipboardviewdialog.h"

ClipBoardViewDialog::ClipBoardViewDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ClipBoardViewDialog)
{
    ui->setupUi(this);
    m_textView = new QPlainTextEdit(this);
    ui->wgtPages->addWidget(m_textView);
    m_pixView = new PixmapViewer(this);
    ui->wgtPages->addWidget(m_pixView);
    const QMimeData* data = qApp->clipboard()->mimeData();
    if (data->hasImage())
    {
        ui->wgtPages->setCurrentIndex(1);
        QPixmap pix = qApp->clipboard()->pixmap();
        m_pixView->setImage(pix);
    }
    else
    {
        ui->wgtPages->setCurrentIndex(0);
        m_textView->setPlainText(data->text());

    }

}

ClipBoardViewDialog::~ClipBoardViewDialog()
{
    delete ui;
}

void ClipBoardViewDialog::on_btnOk_clicked()
{
    close();
}

void showClipBoardViewer()
{
    ClipBoardViewDialog* dlg = new ClipBoardViewDialog();
    dlg->exec();
    delete dlg;
}
