#ifndef TABITEM_H
#define TABITEM_H

#include <QObject>
#include <QRect>
#include <QAction>

class TabItem : public QObject
{
    Q_OBJECT
public:
    explicit TabItem(QObject* parent = nullptr);

    QString caption() const;
    void setCaption(const QString& caption);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    int index() const;
    void setIndex(int index);

    bool isActive() const;
    void setIsActive(bool isActive);

    QRect rect() const;
    void setRect(const QRect& rect);
    QList<QAction*> actions;

    int id() const;
    void setId(int newId);

signals:

private:
    QString m_caption;
    int m_width;
    int m_height;
    int m_index;
    int m_id;
    bool m_isActive;
    QRect m_rect;

};

#endif // TABITEM_H
