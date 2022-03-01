#include "labeledit.h"

LabelEdit::LabelEdit(QWidget* parent) : QLineEdit(parent)
{
    setStyleSheet(R"(border:none;)");
    setAlignment(Qt::AlignCenter);



}

void LabelEdit::hideEdit()
{
    emit changeEditInfo(this->text());
    hide();

}

void LabelEdit::showEdit(QRect rc, QString info, bool bFocus)
{
    setHidden(false);
    setGeometry(rc);
    setText(info);
    if (bFocus)
    {
        setFocus();
    }

}

void LabelEdit::judgeShowOrHide(QRect rc, QPoint pt, QString info)
{
    if (rc.contains(pt))
    {

        showEdit(rc, info);
    }
    else
    {
        hideEdit();
    }

}


