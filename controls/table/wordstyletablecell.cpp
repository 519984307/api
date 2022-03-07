#include "wordstyletablecell.h"

WordStyleTableCell::WordStyleTableCell(QObject* parent) : QObject(parent)
{
    m_extraWidth = 0;
    m_extraLeft = 0;
    m_image = QPixmap();

}

bool WordStyleTableCell::borderLeft() const
{
    return m_borderLeft;
}

void WordStyleTableCell::setBorderLeft(bool newBorderLeft)
{
    m_borderLeft = newBorderLeft;
}

bool WordStyleTableCell::borderTop() const
{
    return m_borderTop;
}

void WordStyleTableCell::setBorderTop(bool newBorderTop)
{
    m_borderTop = newBorderTop;
}

bool WordStyleTableCell::borderRight() const
{
    return m_borderRight;
}

void WordStyleTableCell::setBorderRight(bool newBorderRight)
{
    m_borderRight = newBorderRight;
}

bool WordStyleTableCell::borderBottom() const
{
    return m_borderBottom;
}

void WordStyleTableCell::setBorderBottom(bool newBorderBottom)
{
    m_borderBottom = newBorderBottom;
}

int WordStyleTableCell::colIndex() const
{
    return m_colIndex;
}

void WordStyleTableCell::setColIndex(int newColIndex)
{
    m_colIndex = newColIndex;
}

int WordStyleTableCell::rowIndex() const
{
    return m_rowIndex;
}

void WordStyleTableCell::setRowIndex(int newRowIndex)
{
    m_rowIndex = newRowIndex;
}

int WordStyleTableCell::colSpan() const
{
    return m_colSpan;
}

void WordStyleTableCell::setColSpan(int newColSpan)
{
    m_colSpan = newColSpan;
}

int WordStyleTableCell::rowSpan() const
{
    return m_rowSpan;
}

void WordStyleTableCell::setRowSpan(int newRowSpan)
{
    m_rowSpan = newRowSpan;
}

const QString& WordStyleTableCell::style() const
{
    return m_style;
}

void WordStyleTableCell::setStyle(const QString& newStyle)
{
    m_style = newStyle;
}

const QString& WordStyleTableCell::value()
{
    if (m_style == "edit")
    {
        if (edit != nullptr)
        {
            m_value = edit->text();
        }
    }
    return m_value;
}

void WordStyleTableCell::setValue(const QString& newValue)
{
    if (m_style == "edit")
    {
        edit->setText(newValue);
    }
    m_value = newValue;
}

int WordStyleTableCell::extraWidth() const
{
    return m_extraWidth;
}

void WordStyleTableCell::setExtraWidth(int newExtraWidth)
{
    m_extraWidth = newExtraWidth;
}

int WordStyleTableCell::extraLeft() const
{
    return m_extraLeft;
}

void WordStyleTableCell::setExtraLeft(int newExtraLeft)
{
    m_extraLeft = newExtraLeft;
}

const QRect& WordStyleTableCell::rect() const
{
    return m_rect;
}

void WordStyleTableCell::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

const QString& WordStyleTableCell::fieldName() const
{
    return m_fieldName;
}

void WordStyleTableCell::setFieldName(const QString& newFieldName)
{
    m_fieldName = newFieldName;
}

const QString& WordStyleTableCell::name() const
{
    return m_name;
}





void WordStyleTableCell::setName(const QString& newName)
{
    m_name = newName;
}

const QPixmap& WordStyleTableCell::image() const
{
    return m_image;
}

void WordStyleTableCell::setImage(const QPixmap& newImage)
{
    m_image = newImage;
}

