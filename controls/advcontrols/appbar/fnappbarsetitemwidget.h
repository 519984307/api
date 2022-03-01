#ifndef FNAPPBARSETITEMWIDGET_H
#define FNAPPBARSETITEMWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include "../../base/basewidget.h"

namespace Ui {
class FnAppBarSetItemWidget;
}

class FnAppBarSetItemWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit FnAppBarSetItemWidget(QWidget *parent = nullptr);
    ~FnAppBarSetItemWidget();

    const QString &caption();
    void setCaption(const QString &newCaption);

    const QString &path() ;
    void setPath(const QString &newPath);

private slots:
    void on_btnOpen_clicked();

private:
    Ui::FnAppBarSetItemWidget *ui;
    QString m_caption;
    QString m_path;
};

#endif // FNAPPBARSETITEMWIDGET_H
