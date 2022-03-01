#ifndef QUICKSELECTOR_H
#define QUICKSELECTOR_H

#include <QWidget>
#include "quickselectorbutton.h"
#include <QPainter>
#include "../base/widgethelper.h"
#include <QWheelEvent>

namespace Ui
{
class QuickSelector;
}

class QuickSelector : public QWidget
{
    Q_OBJECT

public:
    explicit QuickSelector(QWidget* parent = nullptr);
    ~QuickSelector();
    bool showButton() const;
    void setShowButton(bool showButton);
    QList<QuickSelectorButton*> buttons;
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    Ui::QuickSelector* ui;

    WidgetHelper* m_helper;
    bool m_showButton;
    QuickSelectorButton* m_selectButton;
    void init();
    void initStartPoses();
};

#endif // QUICKSELECTOR_H
