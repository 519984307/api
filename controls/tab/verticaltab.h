#ifndef VERTICALTAB_H
#define VERTICALTAB_H

#include <QWidget>
#include "parenttab.h"
#include <QMouseEvent>
#include <QMenu>


namespace Ui
{
class VerticalTab;
}

class VerticalTab : public ParentTab
{
    Q_OBJECT

public:
    explicit VerticalTab(QWidget* parent = nullptr);
    ~VerticalTab();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::VerticalTab* ui;

};

#endif // VERTICALTAB_H
