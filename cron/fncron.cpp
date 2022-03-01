#include "fncron.h"

FnCron::FnCron(QObject* parent) : QObject(parent)
{

}

bool FnCron::match(QString cronText, QDateTime datetime)
{
    QStringList cronStl = cronText.split(" ");
    bool ret = false;
    if (cronStl.count() < 6)
    {
        return ret;
    }
    QTime time = datetime.time();
    if (matchValue(cronStl[0], time.second(), 0, 59) == false)
    {
        return ret;
    }
    if (matchValue(cronStl[1], time.minute(), 0, 59) == false)
    {
        return ret;
    }
    if (matchValue(cronStl[2], time.hour(), 0, 23) == false)
    {
        return ret;
    }




    ret = true;
    return ret;
}

bool FnCron::matchValue(QString s, int v, int minValue, int MaxValue)
{
    if (s == "*")
    {
        return true;
    }
    bool ok;
    int n = s.toUInt(&ok);
    if (ok == true)
    {
        if ((n >= minValue) && (n <= MaxValue))
        {
            return n == v;
        }
        else
        {
            return false;
        }
    }
    if (s.indexOf("-") >= 0)
    {
        int a;
        int b;
        getTwoValue(s, a, b, "-");
        if ((v >= a) && (v <= b))
        {
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    if (s.indexOf("/") >= 0)
    {
        int a;
        int b;
        getTwoValue(s, a, b, "/");
        if ((v - a) % b == 0)
        {
            return true;
        }

        return false;
    }
    if (s.indexOf(",") >= 0)
    {
        QStringList values = s.split(",");
        QString vs = QString("%1").arg(v);
        return values.indexOf(vs) >= 0;
    }
    return false;
}

void FnCron::getTwoValue(QString s, int& a, int& b, QString sp)
{
    int n = s.indexOf(sp);
    a = s.left(n).toInt();
    b = s.mid(n + 1).toInt();
}
