#include "reportpage.h"

ReportPage::ReportPage(QObject* parent) : QObject(parent)
{
    m_drawObj = new DrawObject(this);

}

void ReportPage::addTitle(int top, int height, QString text)
{

}

void ReportPage::draw(QPainter& painter)
{
    for (int i = 0; i < cells.count(); i++)
    {
        painter.save();
        ReportCell* cell = cells.at(i);


        QFont font = painter.font();
        font.setPointSize(16);
        painter.setFont(font);
        QPen pen = painter.pen();
        pen.setWidth(m_factor);
        painter.setPen(pen);
        QRect rc(cell->left()*m_factor, cell->top()*m_factor,
                 cell->width() * m_factor, cell->height() * m_factor);
        m_drawObj->drawRect(painter, rc, true, true, true, true);
        painter.drawText(rc, Qt::AlignCenter, cell->text());

        painter.restore();
    }

}

double ReportPage::factor() const
{
    return m_factor;
}

void ReportPage::setFactor(double newFactor)
{
    m_factor = newFactor;
}

void ReportPage::addCell(ReportCell* cell)
{
    cell->setParent(this);
    cells << cell;
}

ReportCell* ReportPage::addCellAtRight(ReportCell* leftCell, int width, QString text)
{
    ReportCell* cell = new ReportCell(this);
    cell->setLeft(leftCell->right());
    cell->setTop(leftCell->top());
    cell->setHeight(leftCell->height());
    cell->setWidth(width);
    cell->setText(text);
    cells << cell;
    return cell;
}
