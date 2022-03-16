#include "basewidget.h"

BaseWidget::BaseWidget(QWidget* parent) : QWidget(parent)
{
    m_uuid = newNoDashUuid();
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);

}

const QString& BaseWidget::uuid() const
{
    return m_uuid;
}

void BaseWidget::setUuid(const QString& newUuid)
{
    m_uuid = newUuid;
}


