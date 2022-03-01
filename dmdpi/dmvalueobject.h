#ifndef DMVALUEOBJECT_H
#define DMVALUEOBJECT_H


#include "dmapi.h"
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

private:
    dhstmt m_dhstmt;
    int m_index;
};

#endif // DMVALUEOBJECT_H
