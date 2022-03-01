#include "dmquery.h"
#ifdef DM_DPI_WIN32

QSqlQuery::QSqlQuery(QSqlDatabase* database)
{
    m_database = database;
    m_dhstmt=0;
}

QSqlQuery::QSqlQuery()
{
    m_dhstmt=0;

}

QSqlDatabase* QSqlQuery::database() const
{

    return m_database;
}



void QSqlQuery::setDatabase(QSqlDatabase* database)
{
    m_database = database;
}



bool QSqlQuery::execute(QString sql)
{


    open();
    DPIRETURN ret = executeSQL(sql);
    close();
    return ret == DSQL_SUCCESS;
}

bool QSqlQuery::exec(QString sql)
{
    QString s = sql;
    bool ret;
    s = s.trimmed().toUpper();
    if (s.indexOf("SELECT") >= 0)
    {
        ret= select(sql);
    }
    else
    {
        ret= execute(sql);
    }
    if (ret==false)
    {
        qDebug()<<sql;
    }
    return ret;

}

bool QSqlQuery::select(QString sql)
{

    open();
    DPIRETURN ret = executeSQL(sql);
    getColInfos();
    return ret==DSQL_SUCCESS;




}

void QSqlQuery::commit()
{
    dpi_commit(m_database->hcon());
}

void QSqlQuery::rollback()
{
    dpi_rollback(m_database->hcon());
}

int QSqlQuery::colCount()
{
    sdint2 n;
    dpi_number_columns(m_dhstmt, &n);
    return n;
}

bool QSqlQuery::next()
{

    ulength rowNum;


    bool ret = dpi_fetch(m_dhstmt, &rowNum) != DSQL_NO_DATA;
    qDebug()<<m_dhstmt;
    if (ret==false)
    {
        close();
    }
    return ret;
}

DmValueObject QSqlQuery::value(int i)
{
    DmValueObject obj;
    obj.setDhstmt(m_dhstmt);
    qDebug()<<m_dhstmt;
    obj.setIndex(i);
    return obj;
}

DmValueObject QSqlQuery::value(QString colName)
{
    qDebug() << m_conInfos;
    int i = m_conInfos[colName.toUpper()];
    DmValueObject obj;
    qDebug()<<m_dhstmt;
    obj.setDhstmt(m_dhstmt);
    obj.setIndex(i);
    return obj;
}

void QSqlQuery::close()

{

    if (m_dhstmt==0)
    {
        return;
    }
    dpi_free_stmt(m_dhstmt);
    qDebug()<<"dpi_free_stmt(m_dhstmt);";
    m_dhstmt=0;
}

DPIRETURN QSqlQuery::open()
{
    close();
    DPIRETURN ret= dpi_alloc_stmt(m_database->hcon(), &m_dhstmt);
    qDebug()<<"dpi_alloc_stmt(m_database->hcon(), &m_dhstmt);";
    qDebug()<<m_dhstmt;
    return ret;
}

void QSqlQuery::getColInfos()
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
        m_conInfos.insert(colName.toUpper(), i);
    }
    qDebug()<<m_conInfos;
}



void QSqlQuery::prepare(QString sql)
{
    m_sql=sql;
}

void QSqlQuery::exec()
{

}

void QSqlQuery::clear()
{
    close();
}

QSqlError QSqlQuery::lastError()
{
    QSqlError obj;
    return obj;
}

void QSqlQuery::bindValue(int i, QByteArray &ba)
{

}


DPIRETURN QSqlQuery::executeSQL(QString sql)
{

    string str = sql.toStdString();

    sdbyte* bsql = (sdbyte*) str.c_str();






    DPIRETURN ret = dpi_exec_direct(m_dhstmt, bsql);

    return ret;
}
QSqlQuery::QSqlQuery(QSqlDatabase &database)
{
    m_database=&database;
}
#endif


