#ifndef FLATTAB_H
#define FLATTAB_H

#include <QWidget>
#include "parenttab.h"

namespace Ui
{
class FlatTab;
}

class FlatTab : public ParentTab
{
    Q_OBJECT

public:
    explicit FlatTab(QWidget* parent = nullptr);
    ~FlatTab();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::FlatTab* ui;
};

#endif // FLATTAB_H
