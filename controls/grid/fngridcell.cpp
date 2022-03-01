#include "fngridcell.h"

FnGridCell::FnGridCell(QObject* parent) : QObject(parent)
{
    m_leftLine = new FnGridLine(this);
    m_topLine = new FnGridLine(this);
    m_rightLine = new FnGridLine(this);
    m_bottomLine = new FnGridLine(this);
    m_readOnly = true;
    m_backColor = QColor(0, 0, 0, 0);
    m_extraHeight = 0;
    m_extraTop = 0;
    m_extraLeft = 0;

}

FnGridRow* FnGridCell::rowData() const
{
    return m_rowData;
}

void FnGridCell::setRowData(FnGridRow* rowData)
{
    m_rowData = rowData;
}

int FnGridCell::left() const
{
    return m_left;
}

void FnGridCell::setLeft(int left)
{
    m_left = left;
}

int FnGridCell::width() const
{
    return m_width;
}

void FnGridCell::setWidth(int width)
{
    m_width = width;
}

QString FnGridCell::value() const
{
    return m_value;
}

void FnGridCell::setValue(const QString& value)
{
    m_value = value;
}

FnGridLine* FnGridCell::leftLine() const
{
    return m_leftLine;
}

void FnGridCell::setLeftLine(FnGridLine* leftLine)
{
    m_leftLine = leftLine;
}

FnGridLine* FnGridCell::topLine() const
{
    return m_topLine;
}

void FnGridCell::setTopLine(FnGridLine* topLine)
{
    m_topLine = topLine;
}

FnGridLine* FnGridCell::rightLine() const
{
    return m_rightLine;
}

void FnGridCell::setRightLine(FnGridLine* rightLine)
{
    m_rightLine = rightLine;
}

FnGridLine* FnGridCell::bottomLine() const
{
    return m_bottomLine;
}

void FnGridCell::setBottomLine(FnGridLine* bottomLine)
{
    m_bottomLine = bottomLine;
}

QRect FnGridCell::textRect() const
{
    return m_textRect;
}

void FnGridCell::setTextRect(const QRect& textRect)
{
    m_textRect = textRect;
}

bool FnGridCell::readOnly() const
{
    return m_readOnly;
}

void FnGridCell::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
}

QColor FnGridCell::backColor() const
{
    return m_backColor;
}

void FnGridCell::setBackColor(const QColor& backColor)
{
    m_backColor = backColor;
}

FnGridCell* FnGridCell::nextCell() const
{
    return m_nextCell;
}

void FnGridCell::setNextCell(FnGridCell* nextCell)
{
    m_nextCell = nextCell;
}

int FnGridCell::extraHeight() const
{
    return m_extraHeight;
}

void FnGridCell::setExtraHeight(int newExtraHeight)
{
    m_extraHeight = newExtraHeight;
}

int FnGridCell::extraLeft() const
{
    return m_extraLeft;
}

void FnGridCell::setExtraLeft(int newExtraLeft)
{
    m_extraLeft = newExtraLeft;
}

int FnGridCell::extraTop() const
{
    return m_extraTop;
}

void FnGridCell::setExtraTop(int newExtraTop)
{
    m_extraTop = newExtraTop;
}

bool FnGridCell::isLastInRow()
{
    int i = m_rowData->rowCells.indexOf(this);
    return i == ((m_rowData->rowCells.count() - 1));
}

const QString& FnGridCell::fieldName() const
{
    return m_fieldName;
}

void FnGridCell::setFieldName(const QString& newFieldName)
{
    m_fieldName = newFieldName;
}

const QString& FnGridCell::dataType() const
{
    return m_dataType;
}

void FnGridCell::setDataType(const QString& newDataType)
{
    m_dataType = newDataType;
}

QString FnGridCell::parentUuid()
{
    return rowData()->uuid();
}

