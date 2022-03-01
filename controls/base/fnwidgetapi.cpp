#include "fnwidgetapi.h"


void addWidgetToPage(QWidget* parent, QWidget* child)
{

    QHBoxLayout* lay = new QHBoxLayout();
    parent->setLayout(lay);
#if (QT_VERSION<QT_VERSION_CHECK(6,0,0))
    lay->setMargin(0);
#else
    lay->setContentsMargins(0, 0, 0, 0);
#endif
    lay->addWidget(child);

}
