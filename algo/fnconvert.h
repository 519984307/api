#ifndef FNCONVERT_H
#define FNCONVERT_H

#include <QObject>

class FnConvert : public QObject
{
    Q_OBJECT
public:
    explicit FnConvert(QObject* parent = nullptr);

signals:

};
QString intToStr(int i);

#endif // FNCONVERT_H
