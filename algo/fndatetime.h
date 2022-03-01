#ifndef FNDATETIME_H
#define FNDATETIME_H

#include <QObject>

class FnDateTime : public QObject
{
    Q_OBJECT
public:
    explicit FnDateTime(QObject* parent = nullptr);

signals:

};
QString secondToString(int i);

#endif // FNDATETIME_H
