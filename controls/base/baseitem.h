#ifndef BASEITEM_H
#define BASEITEM_H

#include <QObject>
#include <QRect>
#include <QWidget>
#include <QPixmap>
#include "../../global/globaldata.h"

class BaseItem : public QObject
{
    Q_OBJECT
public:
    explicit BaseItem(QObject* parent = nullptr);

    QString caption() const;
    void setCaption(const QString& caption);

    int id() const;
    void setId(int id);

    QRect rect() const;
    void setRect(const QRect& rect);

    QRect closeRect() const;
    void setCloseRect(const QRect& closeRect);

    bool selected() const;
    void setSelected(bool selected);

    QString uuid() const;
    void setUuid(const QString& uuid);

    QWidget* widget() const;
    void setWidget(QWidget* widget);

    bool canClose() const;
    void setCanClose(bool canClose);

    QPixmap icon() const;
    void setIcon(const QPixmap& icon);

    int iconAreaWidth() const;
    void setIconAreaWidth(int iconAreaWidth);

    QString value() const;
    void setValue(const QString& value);

    QPoint centerPoint() const;
    void setCenterPoint(const QPoint& centerPoint);

    int row() const;
    void setRow(int row);

    int col() const;
    void setCol(int col);

    QRect iconRect() const;
    void setIconRect(const QRect& iconRect);

    int number() const;
    void setNumber(int newNumber);

    const QColor& color() const;
    void setColor(const QColor& newColor);

    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);

    int width() const;
    void setWidth(int newWidth);

    const QString& name() const;
    void setName(const QString& newName);

    const QString& path() const;
    void setPath(const QString& newPath);

    int index() const;
    void setIndex(int newIndex);

    bool canSelected() const;
    void setCanSelected(bool newCanSelected);

signals:
protected:
    QString m_caption;
    int m_id;
    QRect m_rect;
    QRect m_closeRect;
    QRect m_iconRect;
    bool m_selected;
    bool m_canSelected;
    QString m_uuid;
    QWidget* m_widget;
    bool m_canClose;
    int m_iconAreaWidth;
    QPixmap m_icon;
    QString m_value;
    QPoint m_centerPoint;
    int m_row;
    int m_col;
    int m_number;
    int m_width;
    QColor m_color;
    QColor m_backgroundColor;
    QString m_name;
    QString m_path;
    int m_index;

};

#endif // BASEITEM_H
