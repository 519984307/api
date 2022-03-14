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

    double factor = (double)(m_printer->resolution() / 96);
    qDebug() << factor;

    m_printer->setPageMargins(0, 0, 0, 0, QPrinter::Point);
    qDebug() << m_printer->resolution();
    QPainter painter;

    painter.begin(m_printer);
    qDebug() << painter.viewport();


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
