#ifndef FNCRON_H
#define FNCRON_H

#include <QObject>
#include  <QDateTime>

class FnCron : public QObject
{
    Q_OBJECT
public:
    explicit FnCron(QObject* parent = nullptr);
    bool match(QString cronText, QDateTime datetime);
    bool matchValue(QString s, int v, int minValue, int MaxValue);
    void getTwoValue(QString s, int& a, int& b, QString sp = "-");
signals:

};

#endif // FNCRON_H
