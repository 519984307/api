#ifndef FNGRIDLINE_H
#define FNGRIDLINE_H

#include <QObject>
#include <QColor>

class FnGridLine : public QObject
{
    Q_OBJECT
public:
    explicit FnGridLine(QObject* parent = nullptr);

    bool isDraw() const;
    void setIsDraw(bool isDraw);

    int width() const;
    void setWidth(int width);

    QColor color() const;

signals:
private:
    bool m_isDraw;
    int m_width;
    QColor m_color;

};

#endif // FNGRIDLINE_H
