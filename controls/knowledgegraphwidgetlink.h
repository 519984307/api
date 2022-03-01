#ifndef KNOWLEDGEGRAPHWIDGETLINK_H
#define KNOWLEDGEGRAPHWIDGETLINK_H

#include "knowledgegraphwidgetitem.h"
#include <QObject>
#include <QPainter>
#include <QtDebug>
#include <math.h>
class KnowledgeGraphWidgetLink : public QObject {
    Q_OBJECT
public:
    explicit KnowledgeGraphWidgetLink(QObject* parent = nullptr);

    QString startName() const;
    void setStartName(const QString& startName);

    QString endName() const;
    void setEndName(const QString& endName);
    void drawLine(QPainter& painter, QList<KnowledgeGraphWidgetItem*>& items);
signals:

private:
    QString m_startName;
    QString m_endName;
    KnowledgeGraphWidgetItem* m_startItem;
    KnowledgeGraphWidgetItem* m_endItem;
    KnowledgeGraphWidgetItem* getItem(QList<KnowledgeGraphWidgetItem*>& items, QString value);
};

#endif // KNOWLEDGEGRAPHWIDGETLINK_H
