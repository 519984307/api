#include "valuespliter.h"

ValueSpliter::ValueSpliter(QObject* parent) : QObject(parent)
{
    m_valueStep = 1;

}

const QString& ValueSpliter::value() const
{
    return m_value;
}

void ValueSpliter::setValue(const QString& newValue)
{
    m_value = newValue;
}

QStringList ValueSpliter::result()
{
    QStringList stl;
    stl = m_value.split(",");
    while (true)
    {
        bool ret = false;

        for (int i = stl.count() - 1; i >= 0; i--)
        {
            if (stl[i].indexOf("-") >= 0)
            {
                QString s = stl[i];
                stl.removeAt(i);
                QStringList stl1 = valueToStringList(s);
                int n = i;
                for (int j = 0; j < stl1.count(); j++)
                {
                    stl.insert(n, stl1[j]);
                    n++;
                }

            }
        }


        if (!ret)
        {
            break;
        }

    }

    return stl;
}

QStringList ValueSpliter::valueToStringList(QString s)
{
    QStringList stl;
    int n = s.indexOf("-");
    QString s1 = s.left(n);
    QString s2 = s.mid(n + 1);
    double f1 = s1.toDouble();
    double f2 = s2.toDouble();
    while (true)
    {
        stl << QString("%1").arg(f1);
        if ((f2 - f1) >= m_valueStep)
        {
            f1 += m_valueStep;
        }
        else
        {
            f1 = f2;
            stl << QString("%1").arg(f1);
            break;
        }

    }

    return  stl;

}

double ValueSpliter::valueStep() const
{
    return m_valueStep;
}

void ValueSpliter::setValueStep(double newValueStep)
{
    m_valueStep = newValueStep;
}
