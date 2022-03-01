#include "randomipfunctionitem.h"

RandomIPFunctionItem::RandomIPFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#randomIP";

}

QString RandomIPFunctionItem::run()
{
    QString s;
    for (int i = 0; i < 4; i++)
    {
        int v = QRandomGenerator::global()->bounded(0, 255);
        if (s == "")
        {
            s = QString("%1").arg(v);
        }
        else
        {
            s += "." + QString("%1").arg(v);
        }
    }
    return s;

}
