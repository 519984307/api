#ifndef NEWSELECTCARDWIDGETWINDOW_H
#define NEWSELECTCARDWIDGETWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui
{
class NewSelectCardWidgetWindow;
}

class NewSelectCardWidgetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewSelectCardWidgetWindow(QWidget* parent = nullptr);
    ~NewSelectCardWidgetWindow();


    QWidget* widget() const;
    void setWidget(QWidget* widget);

private:
    Ui::NewSelectCardWidgetWindow* ui;
    QWidget* m_widget;
};

#endif // NEWSELECTCARDWIDGETWINDOW_H
