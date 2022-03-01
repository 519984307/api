#ifndef ROWDATA_H
#define ROWDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
using FieldValues = QMap<QString, QString>;
class RowData : public QObject
{
    Q_OBJECT
public:
    explicit RowData(QObject* parent = nullptr);

signals:

};
QString getFirstRowDataValue(QString fieldName, QJsonArray& rows);
int getFirstRowDataIntValue(QString fieldName, QJsonArray& rows);

QString getColsDataValue(QString fieldName, QJsonArray& cols);

void getSelectRows(QString fieldName, QString value, QJsonArray& rows, QList<QJsonArray>& selRows);
bool existsRowDataValue(QString fieldName, QString value, QJsonArray& cols);
bool getValuesFromRows(QString fieldName, QString value, QJsonArray& rows, QMap<QString, QString>& values);

void colsToMap(QJsonArray& cols, QMap<QString, QString>& values);
void getColsInRows(QJsonArray& rows, int i, QMap<QString, QString>& values);
#endif // ROWDATA_H
