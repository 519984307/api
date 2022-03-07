#include "dmsqlquery.h"

DmSQLQuery::DmSQLQuery(QObject* parent) : QObject(parent)
{
    m_dhstmt = 0;
}

bool DmSQLQuery::select(DmSQLDb* db, QString sql, QJsonArray& rows)
{
    qDebug() << sql;
    m_database = db;
    close();
    open();
    DPIRETURN ret = selectSQL(sql);
    getColInfos();
    int n = colCount();
    int count = 0;
    while (next())
    {
        QJsonArray cols;
        for (int i = 1; i <= n; i++)
        {
            QJsonObject row;
            row["index"] = i - 1;
            row["fieldName"] = m_conInfos.key(i).toUpper();
            row["value"] = fieldValue(i);
            cols.append(row);
        }
        count++;

        rows.append(cols);
    }
    return  count > 0;

}

bool DmSQLQuery::insert(DmSQLDb* db, QString tableName, QJsonArray& cols)
{
    m_database = db;
    QString sql;
    QStringList fields, values;
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        fields << jobj["fieldName"].toString();
        values << "'" + jobj["value"].toString() + "'";
    }
    sql = "insert into " + db->databaseName() + "." + tableName + "(" + fields.join(",") +
          ") values (" + values.join(",") + ")";
    qDebug() << sql;
    return execute(sql);

}

bool DmSQLQuery::update(DmSQLDb* db, QString tableName, QString whereStr, QJsonArray& cols)
{
    m_database = db;
    QString sql;
    QStringList fieldsValues;
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        fieldsValues << jobj["fieldName"].toString() + "=" +
                     "'" + jobj["value"].toString() + "'";
    }
    sql = "update " + db->databaseName() + "." + tableName + " set " + fieldsValues.join(",") +
          " " + whereStr;
    qDebug() << sql;
    return execute(sql);
}

bool DmSQLQuery::update(DmSQLDb* db, QString tableName, QString fieldName, QString value, QJsonArray& cols)
{
    m_database = db;
    QString sql;
    QStringList fieldsValues;
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        if (fieldName == jobj["fieldName"].toString())
        {
            continue;
        }
        fieldsValues << jobj["fieldName"].toString() + "=" +
                     "'" + jobj["value"].toString() + "'";
    }
    sql = "update " + db->databaseName() + "." + tableName + " set " + fieldsValues.join(",") +
          " where " + fieldName + "='" + value + "'" ;
    qDebug() << sql;
    return execute(sql);
}

int DmSQLQuery::rowCount(DmSQLDb* db, QString tableName, QString fieldName, QString value)
{
    QString sql = QString("select * from %1.%2 where %3='%4'").arg(db->databaseName()).arg(tableName).arg(fieldName).arg(value);
    QJsonArray rows;
    select(db, sql, rows);
    return rows.count();
}

void DmSQLQuery::close()
{
    if (m_dhstmt == 0)
    {
        return;
    }
    dpi_free_stmt(m_dhstmt);
    qDebug() << "dpi_free_stmt(m_dhstmt);";
    m_dhstmt = 0;
}

DPIRETURN DmSQLQuery::open()
{
    close();
    DPIRETURN ret = dpi_alloc_stmt(m_database->hcon(), &m_dhstmt);
    qDebug() << "dpi_alloc_stmt(m_database->hcon(), &m_dhstmt);";
    qDebug() << m_dhstmt;

    return ret;
}

void DmSQLQuery::getColInfos()
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
    qDebug() << m_conInfos;

}

DmSQLDb* DmSQLQuery::database() const
{
    return m_database;
}

void DmSQLQuery::setDatabase(DmSQLDb* newDatabase)
{
    m_database = newDatabase;
}

int DmSQLQuery::colCount()
{
    sdint2 n;
    dpi_number_columns(m_dhstmt, &n);
    return n;
}

DPIRETURN DmSQLQuery::selectSQL(QString sql)
{
    string s = sql.toLocal8Bit().toStdString();

    sdbyte* bsql = (sdbyte*) s.c_str();






    DPIRETURN ret = dpi_exec_direct(m_dhstmt, bsql);

    return ret;
}
bool DmSQLQuery::next()
{

    ulength rowNum;


    bool ret = dpi_fetch(m_dhstmt, &rowNum) != DSQL_NO_DATA;
    qDebug() << m_dhstmt;
    if (ret == false)
    {
        close();
    }
    return ret;
}

QString DmSQLQuery::fieldValue(int i)
{
    char* d = new char[2048];
    memset(d, 0, 2048);
    slength len = 0;
    qDebug() << m_dhstmt;
    dpi_get_data(m_dhstmt, i, DSQL_C_CHAR, d, 2048, &len);
    QString ret = QString::fromLocal8Bit(d);
    delete [] d;
    return ret;
}

bool DmSQLQuery::execute(QString sql)
{
    open();
    DPIRETURN ret = executeSQL(sql);
    close();
    return ret == DSQL_SUCCESS;
}

DPIRETURN DmSQLQuery::executeSQL(QString sql)
{
    string str = sql.toLocal8Bit().toStdString();

    sdbyte* bsql = (sdbyte*) str.c_str();






    DPIRETURN ret = dpi_exec_direct(m_dhstmt, bsql);
    qDebug() << ret;
    return ret;
}

DPIRETURN DmSQLQuery::prepareSQL(QString sql)
{
    string str = sql.toLocal8Bit().toStdString();

    sdbyte* bsql = (sdbyte*) str.c_str();

    DPIRETURN ret = dpi_prepare(m_dhstmt, bsql);
    qDebug() << ret;
    return ret;

}
bool DmSQLQuery::saveBlob(DmSQLDb* db, QString sql, QByteArray& data)
{
    sdbyte  tmpbuf[80 * 1024];

    qDebug() << sql;
    m_database = db;
    close();
    open();
    DPIRETURN rt = prepareSQL(sql);
    sdint4     c1 = DSQL_DATA_AT_EXEC;
    slength     c1_ind_ptr = DSQL_DATA_AT_EXEC;
    dpointer     c1_val_ptr = nullptr;
    rt = dpi_bind_param(m_dhstmt, 1, DSQL_PARAM_INPUT, DSQL_C_BINARY,  DSQL_BLOB, sizeof(c1), 0, &c1, sizeof(c1), &c1_ind_ptr);
    if (dpi_exec(m_dhstmt) == DSQL_NEED_DATA)
    {
        if (dpi_param_data(m_dhstmt, &c1_val_ptr) == DSQL_NEED_DATA) /* 绑定数据 */
        {
            int m = data.size();
            int n = 0;

            while (m > n)
            {
                int len = (m - n) >= (80 * 1024) ? (80 * 1024) : (m - n);
                const char* buf = data.data();

                memcpy(tmpbuf, &buf[n], len);
                dpi_put_data(m_dhstmt, tmpbuf, len);
                n += len;
            }
        }
        dpi_param_data(m_dhstmt, &c1_val_ptr); /* 绑定数据 */
    }

    qDebug() << "end";
    return true;
}

QByteArray DmSQLQuery::getBlob(DmSQLDb* db, QString sql)
{
    qDebug() << sql;
    m_database = db;
    close();
    open();
    selectSQL(sql);
    slength val_len = 0;
    slength len = 0;
    sdbyte  tmpbuf[80 * 1024];
    QByteArray data;
    while (next())
    {
        while (DSQL_SUCCEEDED(dpi_get_data(m_dhstmt, 1, DSQL_C_BINARY, tmpbuf, 80 * 1024, &val_len)))
        {
            len = val_len > (80 * 1024) ? (80 * 1024) : val_len;
            if (len == -1)
            {
                break;
            }
            char* buf = new char[len];
            memcpy(buf, &tmpbuf, len);
            data.append(buf, len);
            delete [] buf;

        }
    }
    return data;
}
