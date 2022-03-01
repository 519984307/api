#include "randommacfunctionitem.h"

RandomMACFunctionItem::RandomMACFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#randomMAC";

}

QString RandomMACFunctionItem::run()
{

    QString hexs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    QString s;
    for (int i = 0; i < 12; i++)
    {
        int v = QRandomGenerator::global()->bounded(0, 15);
        if (s == "")
        {
            s = hexs[v];
        }
        else
        {
            if (i % 2 == 0)
            {
                s += "-" + hexs[v];
            }
            else
            {
                s +=  hexs[v];
            }

        }
    }
    return s;

}
