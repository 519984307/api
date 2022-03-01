#ifndef CHATPLAINTEXTEDIT_H
#define CHATPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QtDebug>

class ChatPlainTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit ChatPlainTextEdit(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);
signals:
    void pressReturnButton(bool checked = false);
};

#endif // CHATPLAINTEXTEDIT_H
