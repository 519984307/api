#ifndef COLOREDIT_H
#define COLOREDIT_H

#include <QColorDialog>
#include <QPainter>
#include <QWidget>

namespace Ui {
class ColorEdit;
}

class ColorEdit : public QWidget {
    Q_OBJECT

public:
    explicit ColorEdit(QWidget* parent = nullptr);
    ~ColorEdit();

    int r() const;
    void setR(int r);

    int g() const;
    void setG(int g);

    int b() const;
    void setB(int b);
    int a() const;
    void setA(int a);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::ColorEdit* ui;
    int m_r;
    int m_g;
    int m_b;
    int m_a;
};

#endif // COLOREDIT_H
