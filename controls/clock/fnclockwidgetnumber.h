#ifndef FNCLOCKWIDGETNUMBER_H
#define FNCLOCKWIDGETNUMBER_H

#include <QObject>
#include <QWidget>

class FnClockWidgetNumber : public QObject
{
    Q_OBJECT
public:
    explicit FnClockWidgetNumber(QObject* parent = nullptr);

    QString value() const;
    void setValue(const QString& value);

    QColor color() const;
    void setColor(const QColor& color);

signals:
private:
    QString m_value;
    QColor m_color;

};

#endif // FNCLOCKWIDGETNUMBER_H
