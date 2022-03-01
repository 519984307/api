#include "setthreevaluedialog.h"
#include "ui_setthreevaluedialog.h"

SetThreeValueDialog::SetThreeValueDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetThreeValueDialog)
{
    ui->setupUi(this);
}

SetThreeValueDialog::~SetThreeValueDialog()
{
    delete ui;
}

const QString& SetThreeValueDialog::firstValue()
{
    m_firstValue = ui->edtFirstValue->text();
    return m_firstValue;
}

void SetThreeValueDialog::setFirstValue(const QString& newFirstValue)
{
    m_firstValue = newFirstValue;
    ui->edtFirstValue->setText(m_firstValue);
}

const QString& SetThreeValueDialog::secondValue()
{
    m_secondValue = ui->edtSecondValue->text();
    return m_secondValue;
}

void SetThreeValueDialog::setSecondValue(const QString& newSecondValue)
{
    m_secondValue = newSecondValue;
    ui->edtSecondValue->setText(m_secondValue);
}

const QString& SetThreeValueDialog::thirdValue()
{
    m_thirdValue = ui->edtThirdValue->text();
    return m_thirdValue;
}

void SetThreeValueDialog::setThirdValue(const QString& newThirdValue)
{
    m_thirdValue = newThirdValue;
    ui->edtThirdValue->setText(m_thirdValue);
}

const QString& SetThreeValueDialog::firstCaption() const
{
    return m_firstCaption;
}

void SetThreeValueDialog::setFirstCaption(const QString& newFirstCaption)
{
    m_firstCaption = newFirstCaption;
    ui->lblFirstCaption->setText(m_firstCaption);
}

const QString& SetThreeValueDialog::secondCaption() const
{
    return m_secondCaption;
}

void SetThreeValueDialog::setSecondCaption(const QString& newSecondCaption)
{
    m_secondCaption = newSecondCaption;
    ui->lblSecondCaption->setText(m_secondCaption);
}

const QString& SetThreeValueDialog::thirdCaption() const
{
    return m_thirdCaption;
}

void SetThreeValueDialog::setThirdCaption(const QString& newThirdCaption)
{
    m_thirdCaption = newThirdCaption;
    ui->lblThirdCaption->setText(m_thirdCaption);
}

int SetThreeValueDialog::captionWidth() const
{
    return m_captionWidth;
}

void SetThreeValueDialog::setCaptionWidth(int newCaptionWidth)
{
    m_captionWidth = newCaptionWidth;
    ui->lblFirstCaption->setMinimumWidth(m_captionWidth);
    ui->lblFirstCaption->setMaximumWidth(m_captionWidth);
    ui->lblSecondCaption->setMinimumWidth(m_captionWidth);
    ui->lblSecondCaption->setMaximumWidth(m_captionWidth);
    ui->lblThirdCaption->setMinimumWidth(m_captionWidth);
    ui->lblThirdCaption->setMaximumWidth(m_captionWidth);
}

bool setThreeValue(QString title, QString firstCaption, QString& firstValue, QString secondCaption, QString& secondValue, QString thirdCaption, QString& thirdValue, int captionWidth)
{
    bool f = false;
    SetThreeValueDialog* dlg = new SetThreeValueDialog(nullptr);
    dlg->setWindowTitle(title);
    dlg->setFirstCaption(firstCaption);
    dlg->setFirstValue(firstValue);
    dlg->setSecondCaption(secondCaption);
    dlg->setSecondValue(firstValue);
    dlg->setThirdCaption(thirdCaption);
    dlg->setThirdValue(thirdValue);
    dlg->setCaptionWidth(captionWidth);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        firstValue = dlg->firstValue();
        secondValue = dlg->secondValue();
        thirdValue = dlg->thirdValue();
        f = true;
    }
    delete dlg;
    return f;
}

void SetThreeValueDialog::on_btnOk_clicked()
{
    accept();
}


void SetThreeValueDialog::on_btnCancel_clicked()
{
    reject();
}

