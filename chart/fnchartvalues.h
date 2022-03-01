#ifndef FNCHARTVALUES_H
#define FNCHARTVALUES_H

#include <QObject>
#include "fnchartyvalue.h"
#include <QColor>
#include <QRect>

class FnChartValues : public QObject
{
    Q_OBJECT
public:
    explicit FnChartValues(QObject* parent = nullptr);
    QList<FnChartYValue*> values;
    QColor color() const;
    void setColor(const QColor& color);

    QString caption() const;
    void setCaption(const QString& caption);



    QRect colorRect() const;
    void setColorRect(const QRect& colorRect);

    bool isShow() const;
    void setIsShow(bool isShow);

    int pointNumber() const;
    void setPointNumber(int pointNumber);
    FnChartYValue* getValueByCaption(QString caption);

signals:

private:
    QColor m_color;
    QString m_caption;
    bool m_isShow;
    QRect m_colorRect;
    int m_pointNumber;

};

#endif // FNCHARTVALUES_H
