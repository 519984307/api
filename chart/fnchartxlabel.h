#ifndef FNCHARTXLABEL_H
#define FNCHARTXLABEL_H

#include <QObject>
#include <QRect>

class FnChartXLabel : public QObject
{
    Q_OBJECT
public:
    explicit FnChartXLabel(QObject* parent = nullptr);


    QString caption() const;
    void setCaption(const QString& caption);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);
    QRect labelRect;

signals:

private:
    QString m_caption;
    int m_x;
    int m_y;
};

#endif // FNCHARTXLABEL_H
