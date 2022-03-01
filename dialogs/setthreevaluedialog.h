#ifndef SETTHREEVALUEDIALOG_H
#define SETTHREEVALUEDIALOG_H

#include <QDialog>

namespace Ui
{
class SetThreeValueDialog;
}

class SetThreeValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetThreeValueDialog(QWidget* parent = nullptr);
    ~SetThreeValueDialog();

    const QString& firstValue();
    void setFirstValue(const QString& newFirstValue);

    const QString& secondValue() ;
    void setSecondValue(const QString& newSecondValue);

    const QString& thirdValue();
    void setThirdValue(const QString& newThirdValue);

    const QString& firstCaption() const;
    void setFirstCaption(const QString& newFirstCaption);

    const QString& secondCaption() const;
    void setSecondCaption(const QString& newSecondCaption);

    const QString& thirdCaption() const;
    void setThirdCaption(const QString& newThirdCaption);

    int captionWidth() const;
    void setCaptionWidth(int newCaptionWidth);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SetThreeValueDialog* ui;
    QString m_firstCaption;
    QString m_secondCaption;
    QString m_thirdCaption;
    QString m_firstValue;
    QString m_secondValue;
    QString m_thirdValue;
    int m_captionWidth;
};
bool setThreeValue(QString title, QString firstCaption, QString& firstValue,
                   QString secondCaption, QString& secondValue,
                   QString thirdCaption, QString& thirdValue, int captionWidth = 100);
#endif // SETTHREEVALUEDIALOG_H
