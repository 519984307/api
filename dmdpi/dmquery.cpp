#include "dmquery.h"

DmQuery::DmQuery(QObject* parent) : QObject(parent)
{

}

DmDataBase* DmQuery::database() const
{
    return m_database;
}

void DmQuery::setDatabase(DmDataBase* database)
{
    m_database = database;
}

bool DmQuery::execute(QString sql)
{


    open();
    DPIRETURN ret = executeSQL(sql);
    close();
    return ret == DSQL_SUCCESS;
}

bool DmQuery::select(QString sql)
{


    DPIRETURN ret = executeSQL(sql);
    getColInfos();
    return ret;




}

void DmQuery::commit()
{
    dpi_commit(m_database->hcon());
}

void DmQuery::rollback()
{
    dpi_rollback(m_database->hcon());
}

int DmQuery::colCount()
{
    sdint2 n;
    dpi_number_columns(m_dhstmt, &n);
    return n;
}

bool DmQuery::next()
{
    ulength rowNum;

    return dpi_fetch(m_dhstmt, &rowNum) != DSQL_NO_DATA;
}

DmValueObject DmQuery::value(int i)
{
    DmValueObject obj;
    obj.setDhstmt(m_dhstmt);
    obj.setIndex(i);
    return obj;
}

DmValueObject DmQuery::value(QString colName)
{
    qDebug() << m_conInfos;
    int i = m_conInfos[colName];
    DmValueObject obj;
    obj.setDhstmt(m_dhstmt);
    obj.setIndex(i);
    return obj;
}

void DmQuery::close()
{
    dpi_free_stmt(m_dhstmt);
}

DPIRETURN DmQuery::open()
{
    return dpi_alloc_stmt(m_database->hcon(), &m_dhstmt);
}

void DmQuery::getColInfos()
{
    int n = colCount();
    for (int i = 1; i <= n; i++)
    {

        sdbyte*         name = new sdbyte[2048];

        sdint2         name_len;
        sdint2         sqltype;
        ulength       col_sz;
        sdint2         dec_digits;
        sdint2         nullable;
        dpi_desc_column(m_dhstmt, i, name, 2048, &name_len, &sqltype, &col_sz, &dec_digits, &nullable);
        const char* c = (char*)name;
        QString colName = QString::fromLocal8Bit(c);
        m_conInfos.insert(colName, i);
    }
}


DPIRETURN DmQuery::executeSQL(QString sql)
{

    string str = sql.toStdString();

    sdbyte* bsql = (sdbyte*) str.c_str();






    open();
    DPIRETURN ret = dpi_exec_direct(m_dhstmt, bsql);

    return ret == DSQL_SUCCESS;
}
