#ifndef MAPWIDGETOBJECT_H
#define MAPWIDGETOBJECT_H

#include <QObject>
#include <QPixmap>
#include <QMap>


class MapWidgetObject : public QObject
{
    Q_OBJECT
public:
    explicit MapWidgetObject(QObject* parent = nullptr);

    int width() const;
    void setWidth(int with);

    int height() const;
    void setHeight(int height);

    int left() const;
    void setLeft(int left);

    int top() const;
    void setTop(int top);

    QString devtype() const;
    void setDevtype(const QString& devtype);

    QPixmap icon() const;
    void setIcon(const QPixmap& icon);



    QPoint centerPoint() const;
    void setCenterPoint(const QPoint& centerPoint);

    QRect viewRect() const;
    void setViewRect(const QRect& viewRect);

    int id() const;
    void setId(int id);

    QString devId() const;
    void setDevId(const QString& devId);

    QString name() const;
    void setName(const QString& name);

    QString devState() const;
    void setDevState(const QString& devState);

    int iconIndex() const;
    void setIconIndex(int iconIndex);
    static QMap<int, QPixmap> icons;
signals:
private:
    int m_width;
    int m_height;
    int m_left;
    int m_top;
    QString m_devtype;
    QPixmap m_icon;
    QPoint m_centerPoint;
    QRect m_viewRect;
    QString m_devId;
    int m_id;
    QString m_name;
    QString m_devState;
    int m_iconIndex;


};

#endif // MAPWIDGETOBJECT_H
