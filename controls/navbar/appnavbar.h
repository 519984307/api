#ifndef APPNAVBAR_H
#define APPNAVBAR_H

#include <QWidget>
#include <QPainter>
#include "../base/widgethelper.h"
#include "../../draw/drawobject.h"
#include "appnavbaroperateinfo.h"
#include <QStack>

namespace Ui
{
class AppNavBar;
}

class AppNavBar : public QWidget
{
    Q_OBJECT

public:
    explicit AppNavBar(QWidget* parent = nullptr);
    ~AppNavBar();

    const QString& caption() const;
    void setCaption(const QString& newCaption);
    AppNavBarOperateInfo* addOperateInfo(QString caption);
    AppNavBarOperateInfo* currentOperateInfo();
    void goBack();
signals:
    void backButtonClick(AppNavBarOperateInfo* info);
    void addButtonClick();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::AppNavBar* ui;
    QString m_caption;
    WidgetHelper* m_helper;
    DrawObject* m_drawObj;
    QRect m_backButtonRect;
    QRect m_addButtonRect;
    QStack<AppNavBarOperateInfo*> m_operateInfos;

};

#endif // APPNAVBAR_H
