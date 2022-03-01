#include "abstractdao.h"

AbstractDao::AbstractDao(QObject* parent)
    : QObject(parent)
{
}

QString AbstractDao::createuuid()
{
    QUuid uuid = QUuid::createUuid();
    QString s = uuid.toString();
    s = s.replace("{", "");
    s = s.replace("}", "");
    s = s.toUpper();
    return s;
}
