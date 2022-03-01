#ifndef DMVALUEOBJECT_H
#define DMVALUEOBJECT_H

#ifdef DM_DPI_WIN32
#include "dmapi.h"
#include <QDate>
#include <QDateTime>
class DmValueObject
{

public:
    DmValueObject();
    dhstmt mdhstmt() const;
    void setDhstmt(dhstmt d);

    int index() const;
    void setIndex(int index);
    QString toString();
    int toInt();
    double toDouble();
    QByteArray toByteArray();
    float toFloat();
    QDate toDate();
    QDateTime toDateTime();

private:
    dhstmt m_dhstmt;
    int m_index;
};
#endif
#endif // DMVALUEOBJECT_H
