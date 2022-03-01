#ifndef ROUNDEDBUTTONLIST_H
#define ROUNDEDBUTTONLIST_H

#include <QWidget>
#include "parentbuttonlist.h"
#include "../../draw/drawobject.h"

namespace Ui
{
class RoundedButtonList;
}

class RoundedButtonList : public ParentButtonList
{
    Q_OBJECT

public:
    explicit RoundedButtonList(QWidget* parent = nullptr);
    ~RoundedButtonList();
    int buttonsWidth(QPainter& painter);
    const QColor& buttonColor() const;
    void setButtonColor(const QColor& newButtonColor);

    const QColor& buttonDarkColor() const;
    void setButtonDarkColor(const QColor& newButtonDarkColor);

    const QColor& buttonLightColor() const;
    void setButtonLightColor(const QColor& newButtonLightColor);

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::RoundedButtonList* ui;
    DrawObject* m_drawObj;
    QColor m_buttonColor;
    QColor m_buttonDarkColor;
    QColor m_buttonLightColor;
};

#endif // ROUNDEDBUTTONLIST_H
