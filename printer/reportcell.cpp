#include "reportcell.h"

ReportCell::ReportCell(QObject* parent) : QObject(parent)
{
    m_fontName = "宋体";
    m_fontSize = 11;
    m_selected = false;
    m_drawLeft = true;
    m_drawTop = true;
    m_drawRight = true;
    m_drawBottom = true;
    m_bold = false;

}

const QString& ReportCell::text() const
{
    return m_text;
}

void ReportCell::setText(const QString& newText)
{
    m_text = newText;

}



double ReportCell::right()
{
    return m_left + m_width;
}

void ReportCell::setRectMm(double leftMm, double topMm, double widthMm, double BottomMm)
{
    m_left = MmToPt(leftMm);
    m_top = MmToPt(topMm);
    m_width = MmToPt(widthMm);
    m_height = MmToPt(BottomMm);
}

double ReportCell::MmToPt(double m)
{
    return m * 4;
}

double ReportCell::left() const
{
    return m_left;
}

void ReportCell::setLeft(double newLeft)
{
    m_left = newLeft;
}

double ReportCell::top() const
{
    return m_top;
}

void ReportCell::setTop(double newTop)
{
    m_top = newTop;
}

double ReportCell::width() const
{
    return m_width;
}

void ReportCell::setWidth(double newWidth)
{
    m_width = newWidth;
}

double ReportCell::height() const
{
    return m_height;
}

void ReportCell::setHeight(double newHeight)
{
    m_height = newHeight;
}

const QString& ReportCell::fontName() const
{
    return m_fontName;
}

void ReportCell::setFontName(const QString& newFontName)
{
    m_fontName = newFontName;
}

int ReportCell::fontSize() const
{
    return m_fontSize;
}

void ReportCell::setFontSize(int newFontSize)
{
    m_fontSize = newFontSize;
}

void ReportCell::drawAllBorder(bool b)
{
    m_drawLeft = b;
    m_drawRight = b;
    m_drawTop = b;
    m_drawBottom = b;
}

bool ReportCell::drawLeft() const
{
    return m_drawLeft;
}

void ReportCell::setDrawLeft(bool newDrawLeft)
{
    m_drawLeft = newDrawLeft;
}

bool ReportCell::drawRight() const
{
    return m_drawRight;
}

void ReportCell::setDrawRight(bool newDrawRight)
{
    m_drawRight = newDrawRight;
}

bool ReportCell::drawTop() const
{
    return m_drawTop;
}

void ReportCell::setDrawTop(bool newDrawTop)
{
    m_drawTop = newDrawTop;
}

bool ReportCell::drawBottom() const
{
    return m_drawBottom;
}

void ReportCell::setDrawBottom(bool newDrawBottom)
{
    m_drawBottom = newDrawBottom;
}

QRectF ReportCell::rectF()
{

    return  QRectF(m_left, m_top, m_width, m_height);
}

QRect ReportCell::rect()
{
    return  QRect(m_left, m_top, m_width, m_height);
}

bool ReportCell::selected() const
{
    return m_selected;
}

void ReportCell::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

void ReportCell::movePositionBy(double dx, double dy)
{
    m_left += dx;
    m_top += dy;
}

int ReportCell::colIndex() const
{
    return m_colIndex;
}

void ReportCell::setColIndex(int newColIndex)
{
    m_colIndex = newColIndex;
}

int ReportCell::rowIndex() const
{
    return m_rowIndex;
}

void ReportCell::setRowIndex(int newRowIndex)
{
    m_rowIndex = newRowIndex;
}

double ReportCell::bottom()
{
    return m_top + m_height;

}

QJsonObject ReportCell::toJsonObject()
{
    QJsonObject jobj;
    jobj["left"] = m_left;
    jobj["top"] = m_top;
    jobj["width"] = m_width;
    jobj["height"] = m_height;
    jobj["text"] = m_text;

    jobj["drawLeft"] = m_drawLeft;
    jobj["drawTop"] = m_drawRight;
    jobj["drawRight"] = m_drawTop;
    jobj["drawBottom"] = m_drawBottom;
    jobj["fontName"] = m_fontName;
    jobj["fontSize"] = m_fontSize;
    jobj["bold"] = m_bold;

    return jobj;
}

void ReportCell::fromJObject(QJsonObject& jobj)
{
    m_left = jobj["left"].toDouble();
    m_top = jobj["top"].toDouble();
    m_width = jobj["width"].toDouble();
    m_height = jobj["height"].toDouble();
    m_drawLeft = jobj["drawLeft"].toBool();
    m_drawRight = jobj["drawTop"].toBool();
    m_drawTop = jobj["drawRight"].toBool();
    m_drawBottom = jobj["drawBottom"].toBool();
    m_text = jobj["text"].toString();
    m_fontName = jobj["fontName"].toString();
    m_fontSize = jobj["fontSize"].toInt();
    m_bold = jobj["bold"].toBool();

}

bool ReportCell::bold() const
{
    return m_bold;
}

void ReportCell::setBold(bool newBold)
{
    m_bold = newBold;
}
