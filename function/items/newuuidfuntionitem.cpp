#include "newuuidfuntionitem.h"


NewUUIDFuntionItem::NewUUIDFuntionItem(QObject* parent) : AbstractFunctionItem(parent)
{
    m_name = "#newUUID";

}

QString NewUUIDFuntionItem::run()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}
