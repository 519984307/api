#ifndef DRAWTEXTITEM_H
#define DRAWTEXTITEM_H

#include <QObject>
#include <QWidget>
#include <QRect>

class DrawTextItem : public QObject
{
    Q_OBJECT
public:
    explicit DrawTextItem(QObject* parent = nullptr);

    const QString& text() const;
    void setText(const QString& newText);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    const QColor& textColor() const;
    void setTextColor(const QColor& newTextColor);

signals:
private:
    QString m_text;
    QRect m_rect;
    QColor m_textColor;

};

#endif // DRAWTEXTITEM_H
