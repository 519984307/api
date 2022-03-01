#include "chatplaintextedit.h"

ChatPlainTextEdit::ChatPlainTextEdit(QWidget* parent)
    : QPlainTextEdit(parent)
{
}

void ChatPlainTextEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_Return) {
            emit pressReturnButton();
            return;
        }
    }
    QPlainTextEdit::keyPressEvent(event);
}
