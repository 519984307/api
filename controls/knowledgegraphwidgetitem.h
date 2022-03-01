#ifndef KNOWLEDGEGRAPHWIDGETITEM_H
#define KNOWLEDGEGRAPHWIDGETITEM_H

#include <QColor>
#include <QObject>
#include <QRect>
class KnowledgeGraphWidgetItem : public QObject {
    Q_OBJECT
public:
    explicit KnowledgeGraphWidgetItem(QObject* parent = nullptr);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString& name);

    QString value() const;
    void setValue(const QString& value);

    KnowledgeGraphWidgetItem* parentItem() const;
    void setParentItem(KnowledgeGraphWidgetItem* parentItem);
    QRect rect;
    QPoint center;
    int childsNum() const;
    void setChildsNum(int childsNum);

    QColor color() const;
    void setColor(const QColor& color);

    QColor childColor() const;
    void setChildColor(const QColor& childColor);

    int index() const;
    void setIndex(int index);

    int startAngle() const;
    void setStartAngle(int startAngle);

    bool hasCheck() const;
    void setHasCheck(bool hasCheck);

signals:

private:
    int m_id;
    QString m_name;
    QString m_value;
    int m_childsNum;
    QColor m_color;
    QColor m_childColor;
    KnowledgeGraphWidgetItem* m_parentItem;
    int m_index;
    int m_startAngle;
    bool m_hasCheck;
};

#endif // KNOWLEDGEGRAPHWIDGETITEM_H
