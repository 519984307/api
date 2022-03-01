#include "nowdatefunctionitem.h"

NowDateFunctionItem::NowDateFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#nowDate";

}

QString NowDateFunctionItem::run()
{
    QDate d = QDate::currentDate();
    return d.toString("yyyy-MM-dd");

}
