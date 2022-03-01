#ifndef KNOWLEDGEGRAPHWIDGET_H
#define KNOWLEDGEGRAPHWIDGET_H

#include "knowledgegraphwidgetitem.h"
#include "knowledgegraphwidgetlink.h"
#include <QDebug>
#include <QPainter>
#include <QWidget>
#include <qmath.h>

namespace Ui {
class KnowledgeGraphWidget;
}

class KnowledgeGraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit KnowledgeGraphWidget(QWidget* parent = nullptr);
    ~KnowledgeGraphWidget();
    QList<KnowledgeGraphWidgetItem*> items;
    QList<KnowledgeGraphWidgetLink*> links;
    void clearItems();
    KnowledgeGraphWidgetItem* rootItem() const;
    void setRootItem(KnowledgeGraphWidgetItem* rootItem);
    void addItem(KnowledgeGraphWidgetItem* parentItem, KnowledgeGraphWidgetItem* item);
    KnowledgeGraphWidgetItem* addRootItem(QString& value);
    void drawNode(QPainter& painter, KnowledgeGraphWidgetItem* item);
    void initNode(KnowledgeGraphWidgetItem* item);

    void drawArrowLine(QPainter& painter, QPoint pt1, QPoint pt2);
    KnowledgeGraphWidgetItem* addItem(int id, QString name, QString value);
    QStringList linkNames;
    void AddLink(QString startName, QString endName);
    void initChildnum();
    int getChildNum(KnowledgeGraphWidgetItem* parentItem);
    void setItemsPosition(KnowledgeGraphWidgetItem* parentItem);
    void getChilds(KnowledgeGraphWidgetItem* parentItem, QList<KnowledgeGraphWidgetItem*>& childs);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::KnowledgeGraphWidget* ui;
    KnowledgeGraphWidgetItem* m_rootItem;
};

#endif // KNOWLEDGEGRAPHWIDGET_H
