#include "nowdatetimefunctionitem.h"

NowDateTimeFunctionItem::NowDateTimeFunctionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#nowDateTime";

}

QString NowDateTimeFunctionItem::run()
{
    QDateTime d = QDateTime::currentDateTime();
    return d.toString("yyyy-MM-dd hh:mm:ss");
}
