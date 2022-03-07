#ifndef WORDSTYLETABLECELL_H
#define WORDSTYLETABLECELL_H

#include <QObject>
#include "../api/controls/edit/labeledit.h"

const QString WSTC_EDIT = "edit";
const QString WSTC_TEXT = "edit";
const QString WSTC_BUTTON = "button";


class WordStyleTableCell : public QObject
{
    Q_OBJECT
public:
    explicit WordStyleTableCell(QObject* parent = nullptr);

    bool borderLeft() const;
    void setBorderLeft(bool newBorderLeft);

    bool borderTop() const;
    void setBorderTop(bool newBorderTop);

    bool borderRight() const;
    void setBorderRight(bool newBorderRight);

    bool borderBottom() const;
    void setBorderBottom(bool newBorderBottom);

    int colIndex() const;
    void setColIndex(int newColIndex);

    int rowIndex() const;
    void setRowIndex(int newRowIndex);

    int colSpan() const;
    void setColSpan(int newColSpan);

    int rowSpan() const;
    void setRowSpan(int newRowSpan);

    const QString& style() const;
    void setStyle(const QString& newStyle);

    const QString& value();
    void setValue(const QString& newValue);

    int extraWidth() const;
    void setExtraWidth(int newExtraWidth);

    int extraLeft() const;
    void setExtraLeft(int newExtraLeft);
    LabelEdit* edit;

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    const QString& fieldName() const;
    void setFieldName(const QString& newFieldName);



    const QString& name() const;
    void setName(const QString& newName);

    const QPixmap& image() const;
    void setImage(const QPixmap& newImage);

signals:

private:
    int m_colIndex;
    int m_rowIndex;
    int m_colSpan;
    int m_rowSpan;
    QString m_style;
    bool m_borderLeft;
    bool m_borderTop;
    bool m_borderRight;
    bool m_borderBottom;
    int m_extraWidth;
    int m_extraLeft;
    QString m_value;
    QRect m_rect;
    QString m_fieldName;
    QPixmap m_image;
    QString m_name;
};

#endif // WORDSTYLETABLECELL_H
