#include "settwovaluedialog.h"
#include "ui_settwovaluedialog.h"

SetTwoValueDialog::SetTwoValueDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetTwoValueDialog)
{
    ui->setupUi(this);
}

SetTwoValueDialog::~SetTwoValueDialog()
{
    delete ui;
}

QString SetTwoValueDialog::firstCaption() const
{
    return m_firstCaption;
}

void SetTwoValueDialog::setFirstCaption(const QString& firstCaption)
{
    m_firstCaption = firstCaption;
    ui->lblFirstCaption->setText(m_firstCaption + ":");
}

QString SetTwoValueDialog::firstValue()
{
    m_firstValue = ui->edtFirstValue->text();
    return m_firstValue;
}

void SetTwoValueDialog::setFirstValue(const QString& firstValue)
{
    m_firstValue = firstValue;
    ui->edtFirstValue->setText(m_firstValue);
}

QString SetTwoValueDialog::secondCaption() const
{
    return m_secondCaption;
}

void SetTwoValueDialog::setSecondCaption(const QString& secondCaption)
{
    m_secondCaption = secondCaption;
    ui->lblSecondCaption->setText(m_secondCaption + ":");
}

QString SetTwoValueDialog::secondValue()
{
    m_secondValue = ui->edtSecondValue->text();
    return m_secondValue;
}

void SetTwoValueDialog::setSecondValue(const QString& secondValue)
{
    m_secondValue = secondValue;
    ui->edtSecondValue->setText(m_secondValue);
}

int SetTwoValueDialog::captionWidth() const
{
    return m_captionWidth;
}

void SetTwoValueDialog::setCaptionWidth(int captionWidth)
{
    m_captionWidth = captionWidth;
    ui->lblFirstCaption->setMinimumWidth(m_captionWidth);
    ui->lblFirstCaption->setMaximumWidth(m_captionWidth);
    ui->lblSecondCaption->setMinimumWidth(m_captionWidth);
    ui->lblSecondCaption->setMaximumWidth(m_captionWidth);
}
bool setTwoValue(QString title, QString firstCaption, QString& firstValue,
                 QString secondCaption, QString& secondValue, int captionWidth)
{
    bool f = false;
    SetTwoValueDialog* dlg = new SetTwoValueDialog(nullptr);
    dlg->setWindowTitle(title);
    dlg->setFirstCaption(firstCaption);
    dlg->setFirstValue(firstValue);
    dlg->setSecondCaption(secondCaption);
    dlg->setSecondValue(firstValue);
    dlg->setCaptionWidth(captionWidth);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        firstValue = dlg->firstValue();
        secondValue = dlg->secondValue();
        f = true;
    }
    delete dlg;
    return f;
}

void SetTwoValueDialog::on_btnCancel_clicked()
{
    reject();
}

void SetTwoValueDialog::on_btnOk_clicked()
{
    accept();
}
