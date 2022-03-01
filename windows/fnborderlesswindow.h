#ifndef FNBORDERLESSWINDOW_H
#define FNBORDERLESSWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QDebug>
#include "../api/controls/titlebar/fntitlebar.h"
#include "../api/controls/base/widgethelper.h"
class FnBorderLessWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FnBorderLessWindow(QWidget* parent = nullptr);

signals:
protected:
    FnTitleBar* m_titleBar;
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
private:
    int boundaryWidth;
    QPoint clickPos;
    WidgetHelper* m_helper;

};

#endif // FNBORDERLESSWINDOW_H
