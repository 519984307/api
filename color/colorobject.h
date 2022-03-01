#ifndef COLOROBJECT_H
#define COLOROBJECT_H

#include <QColor>
#include <QObject>
#include <QRect>

class ColorObject : public QObject
{
    Q_OBJECT
public:
    explicit ColorObject(QObject* parent = nullptr);

    int id() const;
    void setId(int id);

    int r() const;
    void setR(int r);

    int g() const;
    void setG(int g);

    int b() const;
    void setB(int b);

    int a() const;
    void setA(int a);

    QRect rect() const;
    void setRect(const QRect& rect);

    QString name() const;
    void setName(const QString& name);
    QColor color();
    QColor antiColor();
    QString rgbColor();
    QString htmlColor();
    static QString htmlColor(int r, int g, int b);
    static QString intToHex(int i);
signals:

private:
    QString m_name;
    int m_id;
    int m_r;
    int m_g;
    int m_b;
    int m_a;
    QRect m_rect;
};

#endif // COLOROBJECT_H
