#ifndef VERNAVBAR_H
#define VERNAVBAR_H

#include "../selectionitem.h"
#include <QPainter>
#include <QWidget>

namespace Ui {
class VerNavBar;
}

class VerNavBar : public QWidget {
    Q_OBJECT

public:
    explicit VerNavBar(QWidget* parent = nullptr);
    ~VerNavBar();
    void addItems(QStringList& captions);
    SelectionItem* getItem(const QString& caption);
signals:
    void onClickItem(SelectionItem* item);

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::VerNavBar* ui;
    QList<SelectionItem*> m_items;
    SelectionItem* m_seletedItem;
};

#endif // VERNAVBAR_H
