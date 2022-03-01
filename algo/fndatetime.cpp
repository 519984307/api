#include "fndatetime.h"

FnDateTime::FnDateTime(QObject* parent) : QObject(parent)
{

}

QString secondToString(int i)
{
    if (i < 60)
    {
        return QString("00:00:%1").arg(i, 2, 10, QLatin1Char('0'));
    }
    else if (i < 3600)
    {
        int n = i % 60;
        int m = (i - n) / 60;
        return QString("00:%1:%2").arg(m, 2).arg(n, 2);

    }
    else
    {
        return "";
    }
}
