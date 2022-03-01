#ifndef FNCHARTYVALUE_H
#define FNCHARTYVALUE_H

#include <QObject>

class FnChartYValue : public QObject
{
    Q_OBJECT
public:
    explicit FnChartYValue(QObject* parent = nullptr);

    double value() const;
    void setValue(double value);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    QString caption() const;
    void setCaption(const QString& caption);

signals:

private:
    double m_value;
    int m_x;
    int m_y;
    QString m_caption;

};

#endif // FNCHARTYVALUE_H
