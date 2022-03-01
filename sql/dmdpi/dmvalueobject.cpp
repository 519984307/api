#include "dmvalueobject.h"
#ifdef DM_DPI_WIN32
DmValueObject::DmValueObject()
{

}

dhstmt DmValueObject::mdhstmt() const
{
    return m_dhstmt;
}

void DmValueObject::setDhstmt(dhstmt d)
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
    qDebug()<<m_dhstmt;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_CHAR, d, 2048, &len);
    QString ret = QString::fromLocal8Bit(d);
    delete [] d;
    return ret;
}

int DmValueObject::toInt()
{
    int i;
    slength len = 0;
    qDebug()<<m_dhstmt;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_SLONG, &i, sizeof(i), &len);
    return i;

}

double DmValueObject::toDouble()
{
    double d = 0;
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_DOUBLE, &d, sizeof(d), &len);
    return d;

}


QByteArray DmValueObject::toByteArray()
{
    QByteArray ba;
    slength len = 0;
    sdbyte buf[1024];
    while(dpi_get_data(m_dhstmt, m_index, DSQL_C_BINARY, &buf, 1024, &len))
    {
        int n=len>1024?1024:len;

        ba.append((char*)buf,n);
    }
    return ba;

}

float DmValueObject::toFloat()
{

    float f = 0.0;
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_FLOAT, &f, sizeof(f), &len);
    return f;

}

QDate DmValueObject::toDate()
{
    dpi_date_t d;
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_DATE, &d, sizeof(d), &len);
    return QDate(d.year,d.month,d.day);

}

QDateTime DmValueObject::toDateTime()
{
    dpi_timestamp_t d;
    slength len = 0;
    dpi_get_data(m_dhstmt, m_index, DSQL_C_TIMESTAMP, &d, sizeof(d), &len);
    QDateTime dt;
    dt.setDate(QDate(d.year,d.month,d.day));
    dt.setTime(QTime(d.hour,d.minute,d.second));
    return dt;

}
#endif
