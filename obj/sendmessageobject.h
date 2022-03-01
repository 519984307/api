#ifndef SENDMESSAGEOBJECT_H
#define SENDMESSAGEOBJECT_H

#include <QObject>

class SendMessageObject : public QObject
{
    Q_OBJECT
public:
    explicit SendMessageObject(QObject* parent = nullptr);

signals:
    void onSendMessage(const QString& msg);

};

#endif // SENDMESSAGEOBJECT_H
