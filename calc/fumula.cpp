#include "fumula.h"


QString getSubStr(QString s)
{
    QString t1;
    int m = 0;
    int n = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '(')
        {
            m = i;
            QString s1 = s.mid(i);
            n = s1.indexOf(")");
            t1 = s1.mid(0, n + 1);
            n = t1.length();
            break;

        }
    }
    QString x1 = t1.mid(1, t1.length() - 2);
    QString value = getValue(x1);
    QString s1 = s.left(m) + value + s.mid(m + n);

    return s1;
}
QString getFumlaResult(QString inputStr)
{
    QString ret;
    QString s = inputStr;
    while (s.indexOf("(") >= 0)
    {
        s = getSubStr(s);


    }
    ret = getValue(s);

    return ret;

}

QString getValue(QString inputStr)
{
    QString s = inputStr;

    QStringList stl;
    QString v;
    QSet<QChar> sets;
    sets << '+' << '-' << '*' << '/';
    for (int i = 0; i < s.length(); i++)
    {
        if (sets.contains(s.at(i)))
        {
            stl << v;
            stl << s.at(i);
            v = "";
        }
        else
        {
            v = v + s.at(i);
        }
    }
    if (v != "")
    {
        stl << v;
    }

    while ((stl.contains("*")) || (stl.contains("/")))
    {
        for (int i = 0; i < stl.count(); i++)
        {
            if ((stl[i] == "*") || (stl[i] == "/"))
            {

                if (stl[i] == "*")
                {
                    double d = stl[i - 1].toDouble() * stl[i + 1].toDouble();
                    stl[i] = QString("%1").arg(d);
                    stl.removeAt(i + 1);
                    stl.removeAt(i - 1);
                }
                else if (stl[i] == "/")
                {
                    double d = stl[i - 1].toDouble() / stl[i + 1].toDouble();
                    stl[i] = QString("%1").arg(d);
                    stl.removeAt(i + 1);
                    stl.removeAt(i - 1);
                }

                break;
            }
        }

    }
    while ((stl.contains("+")) || (stl.contains("-")))
    {
        for (int i = 0; i < stl.count(); i++)
        {
            if ((stl[i] == "+") || (stl[i] == "-"))
            {

                if (stl[i] == "+")
                {
                    double d = stl[i - 1].toDouble() + stl[i + 1].toDouble();
                    stl[i] = QString("%1").arg(d);
                    stl.removeAt(i + 1);
                    stl.removeAt(i - 1);
                }
                else if (stl[i] == "-")
                {
                    double d = stl[i - 1].toDouble() - stl[i + 1].toDouble();
                    stl[i] = QString("%1").arg(d);
                    stl.removeAt(i + 1);
                    stl.removeAt(i - 1);
                }

                break;
            }
        }

    }



    return stl[0];
}


