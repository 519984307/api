#include "idcardfunctionitem.h"

IDCardFunctionItem::IDCardFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#IDCARD";

}

QString IDCardFunctionItem::run()
{
    static QString mm[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    static QString dd[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                           "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
                           "25", "26", "27", "28"
                          };
    QString s;
    for (int i = 0; i < 6; i++)
    {
        int n = QRandomGenerator::global()->bounded(0, 9);
        s = s + QString("%1").arg(n);
    }
    QDate date = QDate::currentDate();
    int y = QRandomGenerator::global()->bounded(1900, date.year());
    s = s + QString("%1").arg(y);
    int m = QRandomGenerator::global()->bounded(0, 11);
    s = s + mm[m];

    int d = QRandomGenerator::global()->bounded(0, 27);
    s = s + dd[d];

    for (int i = 0; i < 4; i++)
    {
        int n = QRandomGenerator::global()->bounded(0, 9);
        s = s + QString("%1").arg(n);
    }
    return s;
}
