#include "reportprinter.h"

ReportPrinter::ReportPrinter(QObject* parent) : AbstractPrinter(parent)
{
    m_printer = new QPrinter(QPrinter::HighResolution);

}

void ReportPrinter::print()
{
    if (pages.count() == 0)
    {
        return;
    }


    m_printer->setPageSize(QPrinter::A4);

    double f = m_printer->resolution() / 96;

    m_printer->setPageMargins(6, 6, 6, 6, QPrinter::Millimeter);
    qDebug() << m_printer->resolution();
    QPainter painter;

    painter.begin(m_printer);

    QRect printRc = painter.viewport();
    qDebug() << printRc;
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);
    QPen pen = painter.pen();
    pen.setWidth(f);
    painter.setPen(pen);
    QRect rc(0, 0, 100 * f, 200 * f);
    painter.drawRect(rc);
    painter.drawText(rc, Qt::AlignCenter, "test");
    rc = QRect(100 * f, 0, 100 * f, 200 * f);
    painter.drawRect(rc);
    painter.end();

}
