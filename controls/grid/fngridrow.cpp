#include "fngridrow.h"

FnGridRow::FnGridRow(QObject* parent) : QObject(parent)
{
    m_height = 32;
    m_headerRow = nullptr;
    m_childsRowCount = 0;
    m_uuid = newDashUuid();

}

int FnGridRow::height() const
{
    return m_height;
}

void FnGridRow::setHeight(int height)
{
    m_height = height;
}

FnGridCell* FnGridRow::addCell()
{
    FnGridCell* cell = new FnGridCell(this);
    cell->setRowData(this);
    rowCells << cell;
    return cell;
}

const QString& FnGridRow::tag() const
{
    return m_tag;
}

void FnGridRow::setTag(const QString& newTag)
{
    m_tag = newTag;
}

FnGridRow* FnGridRow::headerRow() const
{
    return m_headerRow;
}

void FnGridRow::setHeaderRow(FnGridRow* newHeaderRow)
{
    m_headerRow = newHeaderRow;
    newHeaderRow->setChildsRowCount(newHeaderRow->childsRowCount() + 1);
}

const QString& FnGridRow::uuid() const
{
    return m_uuid;
}

void FnGridRow::setUuid(const QString& newUuid)
{
    m_uuid = newUuid;
}

const QString& FnGridRow::code() const
{
    return m_code;
}

void FnGridRow::setCode(const QString& newCode)
{
    m_code = newCode;
}

int FnGridRow::childsRowCount() const
{
    return m_childsRowCount;
}

void FnGridRow::setChildsRowCount(int newChildsRowCount)
{
    m_childsRowCount = newChildsRowCount;
}

void FnGridRow::getValues(QMap<QString, QString>& values)
{
    for (int i = 0; i < rowCells.count(); i++)
    {
        FnGridCell* cell = rowCells.at(i);
        QString fieldName = cell->fieldName();
        values[fieldName] = cell->value();
    }
}

const QString& FnGridRow::dataType() const
{
    return m_dataType;
}

void FnGridRow::setDataType(const QString& newDataType)
{
    m_dataType = newDataType;
}

QList<FnGridRow*> FnGridRow::childRows()
{
    QList<FnGridRow*> rows;
    for (int i = 0; i < m_grid->gridRows.count(); i++)
    {
        FnGridRow* sRow = m_grid->gridRows.at(i);
        if (sRow->headerRow() == this)
        {
            rows << sRow;

        }
    }
    return rows;
}

FnGrid* FnGridRow::grid() const
{
    return m_grid;
}

void FnGridRow::setGrid(FnGrid* newGrid)
{
    m_grid = newGrid;
}

FnGridCell* FnGridRow::cellAt(int i)
{
    return rowCells.at(i);
}


