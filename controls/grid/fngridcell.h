#ifndef FNGRIDCELL_H
#define FNGRIDCELL_H

#include <QObject>
#include <QRect>
#include "fngridrow.h"
#include "fngridline.h"
class FnGridRow;
class FnGridCell : public QObject
{
    Q_OBJECT
public:
    explicit FnGridCell(QObject* parent = nullptr);

    FnGridRow* rowData() const;
    void setRowData(FnGridRow* rowData);

    int left() const;
    void setLeft(int left);

    int width() const;
    void setWidth(int width);

    QString value() const;
    void setValue(const QString& value);


    FnGridLine* leftLine() const;
    void setLeftLine(FnGridLine* leftLine);

    FnGridLine* topLine() const;
    void setTopLine(FnGridLine* topLine);

    FnGridLine* rightLine() const;
    void setRightLine(FnGridLine* rightLine);

    FnGridLine* bottomLine() const;
    void setBottomLine(FnGridLine* bottomLine);

    QRect textRect() const;
    void setTextRect(const QRect& textRect);

    bool readOnly() const;
    void setReadOnly(bool readOnly);

    QColor backColor() const;
    void setBackColor(const QColor& backColor);

    FnGridCell* nextCell() const;
    void setNextCell(FnGridCell* nextCell);

    int extraHeight() const;
    void setExtraHeight(int newExtraHeight);

    int extraLeft() const;
    void setExtraLeft(int newExtraLeft);

    int extraTop() const;
    void setExtraTop(int newExtraTop);
    bool isLastInRow();


    const QString& fieldName() const;
    void setFieldName(const QString& newFieldName);

    const QString& dataType() const;
    void setDataType(const QString& newDataType);
    QString parentUuid();

signals:
private:
    FnGridRow* m_rowData;
    int m_left;
    int m_width;
    QString m_value;
    FnGridLine* m_leftLine;
    FnGridLine* m_topLine;
    FnGridLine* m_rightLine;
    FnGridLine* m_bottomLine;
    QRect m_textRect;
    bool m_readOnly;
    QColor m_backColor;
    FnGridCell* m_nextCell = nullptr;
    int m_extraHeight;
    int m_extraLeft;
    int m_extraTop;
    QString m_fieldName;
    QString m_dataType;

};

#endif // FNGRIDCELL_H
