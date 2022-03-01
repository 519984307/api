#include "dmvalueobject.h"

DmValueObject::DmValueObject()
{

}

dhstmt DmValueObject::mdhstmt() const
{
    return m_dhstmt;
}

void DmValueObject::setDhstmt(::dhstmt d)
{
    m_dhstmt = d;
}

int DmValueObject::index() const
{
    return m_index;
}

void DmValueObject::setIndex(int index)
{
    m_index = index;
}

QString DmValueObject::toString()
{
    char* d = new char[2048];
    memset(d, 0, 2048);
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_CHAR, d, 2048, &len);
    qDebug() << m_dhstmt;
    QString ret = QString::fromLocal8Bit(d);
    delete [] d;
    return ret;
}

int DmValueObject::toInt()
{
    int i;
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_SLONG, &i, sizeof(i), &len);
    return i;

}

double DmValueObject::toDouble()
{
    double d = 0;
    slength len = 0;
    dpi_get_data(m_dhstmt, 3, DSQL_C_DOUBLE, &d, sizeof(d), &len);
    return d;

}
