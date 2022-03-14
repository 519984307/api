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
        font.setBold(cell->bold());
        painter.setFont(font);
        QPen pen = painter.pen();
        pen.setWidth(m_factor);
        painter.setPen(pen);

        QRectF rc(cell->left()*m_factor, cell->top()*m_factor,
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
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jobj = jdoc.object();
    QJsonArray jcells = jobj["cells"].toArray();
    for (int i = 0; i < jcells.count(); i++)
    {
        ReportCell* cell = new ReportCell(this);
        QJsonObject jcell = jcells.at(i).toObject();
        cell->fromJObject(jcell);
        cells << cell;
    }

    file.close();

}

void ReportPage::addCellsFromJson(QString fileName, QStringList& values, double& cellsHeight)
{
    double t = 0;
    double b = 0;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jobj = jdoc.object();
    QJsonArray jcells = jobj["cells"].toArray();
    for (int i = 0; i < jcells.count(); i++)
    {
        ReportCell* cell = new ReportCell(this);
        QJsonObject jcell = jcells.at(i).toObject();
        cell->fromJObject(jcell);
        if (i <= (values.count() - 1))
        {
            cell->setText(values[i]);
        }
        if (i == 0)
        {
            t = cell->top();
            b = cell->bottom();
        }
        else
        {
            if (cell->top() < t)
            {
                t = cell->top();
            }
            if (cell->bottom() > b)
            {
                b = cell->bottom();
            }
        }
        cellsHeight = b - t;
        cells << cell;
    }

    file.close();
}

void ReportPage::appendCellsFromJson(QString fileName, QStringList& values, double& cellsHeight, double topMargin)
{
    double t = 0;
    double b = 0;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jobj = jdoc.object();
    QJsonArray jcells = jobj["cells"].toArray();
    for (int i = 0; i < jcells.count(); i++)
    {
        ReportCell* cell = new ReportCell(this);
        QJsonObject jcell = jcells.at(i).toObject();
        cell->fromJObject(jcell);
        if (i <= (values.count() - 1))
        {
            cell->setText(values[i]);
        }
        if (i == 0)
        {
            t = cell->top();
            b = cell->bottom();
        }
        else
        {
            if (cell->top() < t)
            {
                t = cell->top();
            }
            if (cell->bottom() > b)
            {
                b = cell->bottom();
            }
        }
        cellsHeight = b - t;
        cell->setTop(cell->top() + topMargin);
        cells << cell;
    }

    file.close();
}
