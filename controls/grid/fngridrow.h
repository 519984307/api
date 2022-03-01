#ifndef FNGRIDROW_H
#define FNGRIDROW_H

#include <QObject>
#include "fngridcell.h"
#include "fngrid.h"
#include <QMap>
#include "../api/global/globaldata.h"
class FnGrid;
class FnGridCell;
class FnGridRow : public QObject
{
    Q_OBJECT
public:
    explicit FnGridRow(QObject* parent = nullptr);

    int height() const;
    void setHeight(int height);
    QList<FnGridCell*> rowCells;
    FnGridCell* addCell();

    const QString& tag() const;
    void setTag(const QString& newTag);

    FnGridRow* headerRow() const;
    void setHeaderRow(FnGridRow* newHeaderRow);

    const QString& uuid() const;
    void setUuid(const QString& newUuid);

    const QString& code() const;
    void setCode(const QString& newCode);

    int childsRowCount() const;
    void setChildsRowCount(int newChildsRowCount);
    void getValues(QMap<QString, QString>& values);

    const QString& dataType() const;
    void setDataType(const QString& newDataType);
    QList<FnGridRow*> childRows();

    FnGrid* grid() const;
    void setGrid(FnGrid* newGrid);
    FnGridCell* cellAt(int i);
signals:
private:
    int m_height;
    QString m_tag;
    FnGridRow* m_headerRow;
    int m_childsRowCount;
    QString m_code;
    QString m_uuid;
    QString m_dataType;
    FnGrid* m_grid;

};

#endif // FNGRIDROW_H
