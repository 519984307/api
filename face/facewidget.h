#ifndef FACEWIDGET_H
#define FACEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <ctime>
#include <QThread>
#include <QTime>

namespace Ui
{
class FaceWidget;
}

class FaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FaceWidget(QWidget* parent = nullptr);
    ~FaceWidget();

    int faceOneSideWidth() const;
    void setFaceOneSideWidth(int faceOneSideWidth);

    int faceUpHeight() const;
    void setFaceUpHeight(int faceUpHeight);

    int faceDownHeight() const;
    void setFaceDownHeight(int faceDownHeight);
    void drawEye(QPainter& painter, QPoint pt,  int w, int h, int n);
    void drawMouse(QPainter& painter, QPoint pt, int r, int n);
    int eyeWidth() const;
    void setEyeWidth(int eyeWidth);

    int mouseWidth() const;
    void setMouseWidth(int mouseWidth);

protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::FaceWidget* ui;
    int m_faceOneSideWidth;
    int m_faceUpHeight;
    int m_faceDownHeight;
    int m_eyeWidth;
    int m_eyeHeight;
    int m_eyeSelect;
    int m_mouseHeight;
    int m_mouseWidth;
};

#endif // FACEWIDGET_H
