#include "addition.h"
#include <QDebug>

QString addNumber(QString n1, QString n2)
{
    QString s1, s2;
    if (n1.length() >= n2.length())
    {
        s1 = n1;
        s2 = n2;
    }
    else
    {
        s1 = n2;
        s2 = n1;
    }
    while (s1.length() != s2.length())
    {
        s2 = "0" + s2;
    }
    QString s;
    bool f = false;

    for (int i = s1.length() - 1; i >= 0; i--)
    {
        QString m1 = s1.at(i);
        QString m2 = s2.at(i);
        int n1 = m1.toInt();
        int n2 = m2.toInt();
        int n = n1 + n2;
        n = n + (f == true ? 1 : 0);
        s = QString("%1").arg(n % 10) + s;
        f = n >= 10;
    }
    if (f)
    {
        s = "1" + s;
    }

    return s;


}
