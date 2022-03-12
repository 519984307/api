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
        font.setPointSize(cell->fontSize());
        font.setFamily(cell->fontName());
        painter.setFont(font);
        QPen pen = painter.pen();
        pen.setWidth(m_factor);
        painter.setPen(pen);

        QRect rc(cell->left()*m_factor, cell->top()*m_factor,
                 cell->width() * m_factor, cell->height() * m_factor);
        m_drawObj->drawRect(painter, rc, cell->drawLeft(),
                            cell->drawTop(), cell->drawRight(), cell->drawBottom());
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

double ReportPage::addHorCells(double left, double top, double height, QStringList& values, QList<double>& widths)
{
    double l = left;
    for (int i = 0; i < values.count(); i++)
    {
        ReportCell* cell = new ReportCell(this);
        cell->setText(values[i]);
        cell->setLeft(l);
        cell->setTop(top);
        cell->setWidth(widths[i]);
        cell->setHeight(height);
        cell->drawAllBorder(true);
        cells << cell;
        l += widths[i];
    }
    return l;
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

void ReportPage::addCellsFromJson(QString fileName)
{

}
