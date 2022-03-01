#include "rowdata.h"

RowData::RowData(QObject* parent) : QObject(parent)
{

}

QString getFirstRowDataValue(QString fieldName, QJsonArray& rows)
{
    QJsonArray cols = rows.at(0).toArray();
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        if (jobj["fieldName"].toString().toUpper() == fieldName.toUpper())
        {
            return jobj["value"].toString();
        }
    }

    return "";
}

int getFirstRowDataIntValue(QString fieldName, QJsonArray& rows)
{
    return getFirstRowDataValue(fieldName, rows).toInt();
}

void getSelectRows(QString fieldName, QString value, QJsonArray& rows, QList<QJsonArray>& selRows)
{
    for (int i = 0; i < rows.count(); i++)
    {
        QJsonArray cols = rows.at(i).toArray();

        if (existsRowDataValue(fieldName, value, cols))
        {
            selRows << cols;
        }

    }
}

bool existsRowDataValue(QString fieldName, QString value, QJsonArray& cols)
{

    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        if ((jobj["fieldName"].toString().toUpper() == fieldName.toUpper())
            && (jobj["value"].toString() == value))
        {
            return true;
        }
    }
    return false;
}



QString getColsDataValue(QString fieldName, QJsonArray& cols)
{
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        if (jobj["fieldName"].toString().toUpper() == fieldName.toUpper())
        {
            return jobj["value"].toString();
        }
    }

    return "";
}

void colsToMap(QJsonArray& cols, QMap<QString, QString>& values)
{
    for (int i = 0; i < cols.count(); i++)
    {
        QJsonObject jobj = cols.at(i).toObject();
        values[jobj["fieldName"].toString()] = jobj["value"].toString();

    }
}

bool getValuesFromRows(QString fieldName, QString value, QJsonArray& rows, QMap<QString, QString>& values)
{
    for (int i = 0; i < rows.count(); i++)
    {
        QJsonArray cols = rows.at(i).toArray();
        colsToMap(cols, values);
        if (values[fieldName] == value)
        {
            return true;
        }
    }
    values.clear();
    return false;
}

void getColsInRows(QJsonArray& rows, int i, QMap<QString, QString>& values)
{
    QJsonArray cols = rows.at(i).toArray();
    colsToMap(cols, values);
}
