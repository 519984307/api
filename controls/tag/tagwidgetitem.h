#ifndef TAGWIDGETITEM_H
#define TAGWIDGETITEM_H

#include <QObject>
#include <QRect>
#include <QColor>

class TagWidgetItem : public QObject
{
    Q_OBJECT
public:
    explicit TagWidgetItem(QObject* parent = nullptr);
    QRect rect;
    QString caption() const;
    void setCaption(const QString& caption);

    QColor color() const;
    void setColor(const QColor& color);

    int id() const;
    void setId(int id);

    bool selected() const;
    void setSelected(bool selected);

    int index() const;
    void setIndex(int index);

signals:
private:
    QString m_caption;
    QColor m_color;
    int m_id;
    bool m_selected;
    int m_index;
};

#endif // TAGWIDGETITEM_H
