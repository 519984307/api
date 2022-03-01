#ifndef TEXT2IMAGEOBJECT_H
#define TEXT2IMAGEOBJECT_H

#include <QObject>
#include <QRect>

class Text2ImageObject : public QObject
{
    Q_OBJECT
public:
    explicit Text2ImageObject(QObject* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

    QRect textRect() const;
    void setTextRect(const QRect& textRect);


    int length() const;
    void setLength(int length);

signals:
private:
    QString m_text;
    QRect m_textRect;
    int m_length;

};

#endif // TEXT2IMAGEOBJECT_H
