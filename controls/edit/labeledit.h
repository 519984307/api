#ifndef LABELEDIT_H
#define LABELEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QDebug>
class LabelEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LabelEdit(QWidget* parent = nullptr);
    void hideEdit();
    void showEdit(QRect rc, QString info, bool bFocus = true);
    void judgeShowOrHide(QRect rc, QPoint pt, QString info);
signals:
    void changeEditInfo(QString info);
signals:

};

#endif // LABELEDIT_H
