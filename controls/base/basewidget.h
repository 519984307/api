#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "../../global/globaldata.h"
#include "widgethelper.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget* parent = nullptr);
    QString m_uuid;

    const QString& uuid() const;
    void setUuid(const QString& newUuid);

signals:
protected:
    WidgetHelper* m_helper;

};

#endif // BASEWIDGET_H
