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

    double factor = m_printer->resolution() / 96;

    m_printer->setPageMargins(6, 6, 6, 6, QPrinter::Millimeter);
    qDebug() << m_printer->resolution();
    QPainter painter;

    painter.begin(m_printer);


    for (int i = 0; i < pages.count(); i++)
    {
        ReportPage* page = pages.at(i);
        page->setFactor(factor);
        page->draw(painter);

        if (i != (pages.count() - 1))
        {
            m_printer->newPage();
        }
    }



    painter.end();

}
