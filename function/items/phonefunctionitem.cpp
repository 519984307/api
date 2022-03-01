#include "phonefunctionitem.h"

PhoneFunctionItem::PhoneFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#phoneNumber";

}

QString PhoneFunctionItem::run()
{
    QString s = "13";
    for (int i = 0; i < 9; i++)
    {
        int n = QRandomGenerator::global()->bounded(0, 9);
        s = s + QString("%1").arg(n);

    }
    return s;
}
