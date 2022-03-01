#ifndef MARKDOWNWIDGET_H
#define MARKDOWNWIDGET_H

#include <QWidget>

namespace Ui {
class MarkDownWidget;
}

class MarkDownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MarkDownWidget(QWidget *parent = nullptr);
    ~MarkDownWidget();

private:
    Ui::MarkDownWidget *ui;
};

#endif // MARKDOWNWIDGET_H
