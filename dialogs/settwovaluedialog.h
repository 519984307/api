#ifndef SETTWOVALUEDIALOG_H
#define SETTWOVALUEDIALOG_H

#include <QDialog>

namespace Ui
{
class SetTwoValueDialog;
}

class SetTwoValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetTwoValueDialog(QWidget* parent = nullptr);
    ~SetTwoValueDialog();

    QString firstCaption() const;
    void setFirstCaption(const QString& firstCaption);

    QString firstValue() ;
    void setFirstValue(const QString& firstValue);

    QString secondCaption() const;
    void setSecondCaption(const QString& secondCaption);

    QString secondValue();
    void setSecondValue(const QString& secondValue);

    int captionWidth() const;
    void setCaptionWidth(int captionWidth);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SetTwoValueDialog* ui;
    QString m_firstCaption;
    QString m_firstValue;
    QString m_secondCaption;
    QString m_secondValue;
    int m_captionWidth;
};
bool setTwoValue(QString title, QString firstCaption, QString& firstValue,
                 QString secondCaption, QString& secondValue, int captionWidth = 100);
#endif // SETTWOVALUEDIALOG_H
