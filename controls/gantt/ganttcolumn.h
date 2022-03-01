#ifndef GANTTCOLUMN_H
#define GANTTCOLUMN_H

#include <QObject>
#include <QRect>

class GanttColumn : public QObject
{
    Q_OBJECT
public:
    explicit GanttColumn(QObject* parent = nullptr);

    const QString& caption() const;

    int width() const;

    void setCaption(const QString& newCaption);

    void setWidth(int newWidth);

    const QRect& rect() const;
    void setRect(const QRect& newRect);

signals:
private:
    QString m_caption;
    int m_width;
    QRect m_rect;

};

#endif // GANTTCOLUMN_H
