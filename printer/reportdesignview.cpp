#include "reportdesignview.h"
#include "ui_reportdesignview.h"

ReportDesignView::ReportDesignView(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ReportDesignView)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_pageLeft = 48;
    m_pageTop = 12;
    m_operation = ControlOperation::OP_NONE;
    m_drawObj = new DrawObject(this);
    setMouseTracking(true);
}

ReportDesignView::~ReportDesignView()
{
    delete ui;
}

void ReportDesignView::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setViewTransformEnabled(true);
    painter.setMatrixEnabled(true);



    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, Qt::white);

    QMatrix matrix = painter.matrix();
    matrix.translate(m_pageLeft, m_pageTop);
    painter.setMatrix(matrix);

    painter.setPen(QColor(203, 203, 223));
    painter.drawRect(QRect(0, 0, 793, 1123));
    painter.setPen(Qt::black);
    for (int i = 0; i < cells.count(); i++)
    {
        ReportCell* cell = cells.at(i);
        painter.save();
        QFont font = painter.font();
        font.setFamily(cell->fontName());
        font.setPointSize(cell->fontSize());
        font.setBold(cell->bold());
        painter.setFont(font);

        QRectF rc = cell->rectF();
        painter.setPen(cell->selected() ? Qt::red : Qt::black);
        m_drawObj->drawRect(painter, rc, cell->drawLeft(), cell->drawTop(), cell->drawRight(), cell->drawBottom());
        painter.drawText(rc, Qt::AlignCenter, cell->text());
        painter.restore();
    }

    if ((m_operation == OP_SELECT) && (m_helper->mousedownFlag()))
    {
        QPoint pt1 = m_helper->mousedownPoint();
        QPoint pt2 = m_helper->mouseMovePoint();
        m_drawObj->drawRect(painter, pt1, pt2);
    }

    painter.end();



}

void ReportDesignView::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPoint = m_helper->virtualCurPos(-m_pageLeft, -m_pageTop);
    if (m_operation == OP_SELECT)
    {
        m_helper->setMouseMovePoint(curPoint);
    }
    else
    {
        if (m_helper->mousedownFlag())
        {
            int dx = curPoint.x() - m_helper->mouseMovePoint().x();
            int dy = curPoint.y() - m_helper->mouseMovePoint().y();
            for (int i = 0; i < cells.count(); i++)
            {
                ReportCell* cell = cells.at(i);


                if (qApp->keyboardModifiers() == Qt::ControlModifier)
                {
                    if (cell->selected())
                    {
                        cell->movePositionBy(dx, dy);
                    }
                }
                else
                {
                    if ((cell->rect().contains(curPoint)) && (cell->selected()))
                    {

                        cell->movePositionBy(dx, dy);
                    }
                }



            }
            m_helper->setMouseMovePoint(curPoint);

        }

    }
    update();
    qDebug() << curPoint;
}

void ReportDesignView::mousePressEvent(QMouseEvent* event)
{
    QPoint curPoint = m_helper->virtualCurPos(-m_pageLeft, -m_pageTop);
    if (m_operation == OP_ADD_OBJECT)
    {

        ReportCell* cell = new ReportCell(this);
        cell->setLeft(curPoint.x());
        cell->setTop(curPoint.y());
        cell->setWidth(100);
        cell->setHeight(30);
        cell->setText("窗口");
        cell->drawAllBorder(true);
        cells << cell;
        m_operation = OP_NONE;
    }
    else if (m_operation == OP_SELECT)
    {
        m_helper->setMousedownPoint(curPoint);
        m_helper->setMousedownFlag(true);

    }
    else if (m_operation == OP_PASTE_SELECT_OBJECTS)
    {
        for (int i = 0; i < copyCells.count(); i++)
        {
            ReportCell* cell = copyCells.at(i);
            ReportCell* newCell = new ReportCell(this);
            newCell->setLeft(cell->left());
            newCell->setTop(curPoint.y());
            newCell->setWidth(cell->width());
            newCell->setHeight(cell->height());
            newCell->setText(cell->text());
            cells << newCell;
        }
        m_operation = OP_NONE;

    }
    else
    {
        if (qApp->keyboardModifiers() != Qt::ControlModifier)
        {
            deselectAll();
        }
        for (int i = 0; i < cells.count(); i++)
        {
            ReportCell* cell = cells.at(i);
            if (cell->rect().contains(curPoint))
            {
                cell->setSelected(true);
            }
        }
        m_helper->setMousedownPoint(curPoint);
        m_helper->setMouseMovePoint(curPoint);
        m_helper->setMousedownFlag(true);
        if (m_operation == OP_NONE)
        {
            if (getSelectCellsCount() == 0)
            {
                m_operation = OP_SELECT;
            }
        }
    }
    update();
}

void ReportDesignView::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint curPoint = m_helper->virtualCurPos(-m_pageLeft, -m_pageTop);
    m_helper->setMousedownFlag(false);
    if (m_operation == OP_SELECT)
    {
        QRect selRc = m_drawObj->getRect(m_helper->mousedownPoint(), curPoint);

        for (int i = 0; i < cells.count(); i++)
        {
            ReportCell* cell = cells.at(i);
            if (!selRc.intersected(cell->rect()).isEmpty())
            {
                cell->setSelected(true);

            }
        }
    }
    m_operation = OP_NONE;
    update();
}

const QString& ReportDesignView::fileName() const
{
    return m_fileName;
}

void ReportDesignView::setFileName(const QString& newFileName)
{
    m_fileName = newFileName;
}

void ReportDesignView::saveToFile(QString fileName)
{
    m_fileName = fileName;
    QJsonDocument jdoc;
    QJsonObject jobj;
    QJsonArray jcells;
    for (int i = 0; i < cells.count(); i++)
    {
        ReportCell* cell = cells.at(i);
        jcells.append(cell->toJsonObject());
    }
    jobj["cells"] = jcells;

    jdoc.setObject(jobj);
    QFile file(m_fileName);
    file.open(QIODevice::WriteOnly);
    file.write(jdoc.toJson());
    file.close();

}

void ReportDesignView::loadFromFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);

    QJsonObject jobj = jdoc.object();
    QJsonArray jcells = jdoc["cells"].toArray();
    for (int i = 0; i < jcells.count(); i++)
    {
        ReportCell* cell = new ReportCell();
        QJsonObject jcell = jcells.at(i).toObject();
        cell->fromJObject(jcell);
        cells << cell;
    }


    file.close();
    update();

}

void ReportDesignView::processSelectCells(std::function<void(ReportCell* cell)>  processCell)
{
    for (int i = 0; i < cells.count(); i++)
    {

        ReportCell* cell = cells.at(i);
        if (cell->selected())
        {
            processCell(cell);
        }
    }
    update();

}

ReportCell* ReportDesignView::getFirstSelectCell()
{

    for (int i = 0; i < cells.count(); i++)
    {
        ReportCell* cell = cells.at(i);
        if (cell->selected())
        {
            return cell;
        }
    }

    return nullptr;
}

QPoint ReportDesignView::getCursorPoint()
{

    return m_helper->virtualCurPos(-m_pageLeft, -m_pageTop);
}

int ReportDesignView::getSelectCellsCount()
{
    int n = 0;
    for (int i = 0; i < cells.count(); i++)
    {

        ReportCell* cell = cells.at(i);
        if (cell->selected())
        {
            n++;
        }
    }

    return n;

}

void ReportDesignView::showCellPropertyDialog(ReportCell* cell)
{
    if (cell == nullptr)
    {
        return;
    }
    ReportCellPropertyDialog* dlg = new ReportCellPropertyDialog();
    dlg->setCell(cell);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        update();
    }
    delete dlg;

}

void ReportDesignView::fitToMaxHeight()
{
    QList<ReportCell*> selCells;
    getSelectCells(selCells);
    double h = 0;
    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        if (i == 0)
        {
            h = cell->height();
        }
        else
        {
            if (cell->height() > h)
            {
                h = cell->height();
            }
        }
    }
    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        cell->setHeight(h);
    }
    update();
}

double ReportDesignView::calSelectCellsSumWidth()
{
    double d = 0;

    QList<ReportCell*> selCells;
    getSelectCells(selCells);

    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        d += cell->width();
    }


    return d;
}

void ReportDesignView::resetSelectCellsHeightByFactor(double factor)
{
    processSelectCells([&](ReportCell * cell)
    {
        cell->setHeight(cell->height()*factor);
    });

}

void ReportDesignView::deleteSelectCells()
{
    for (int i = cells.count() - 1; i >= 0; i--)
    {
        ReportCell* cell = cells.at(i);
        if (cell->selected())
        {
            cells.removeAt(i);
            delete cell;

        }
    }
    update();

}

ControlOperation ReportDesignView::operation() const
{
    return m_operation;
}

void ReportDesignView::setOperation(ControlOperation newOperation)
{
    m_operation = newOperation;
}

void ReportDesignView::deselectAll()
{
    for (int i = 0; i < cells.count(); i++)
    {
        ReportCell* cell = cells.at(i);
        cell->setSelected(false);
    }
    update();
}

void ReportDesignView::setSelectCellsHorTile()
{

    double t;
    QList<ReportCell*> selCells;
    getSelectCells(selCells);
    if (selCells.count() == 0)
    {
        return;
    }
    double l;
    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        if (i == 0)
        {
            t = cell->top();
            l = cell->right();
        }
        else
        {
            cell->setTop(t);
            cell->setLeft(l);
            l = cell->right();
        }
    }
    update();
}

void ReportDesignView::setSelectCellsVerTile()
{
    double t;
    QList<ReportCell*> selCells;
    getSelectCells(selCells);
    if (selCells.count() == 0)
    {
        return;
    }
    double l;
    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        if (i == 0)
        {
            t = cell->bottom();
            l = cell->left();
        }
        else
        {
            cell->setTop(t);
            cell->setLeft(l);
            t = cell->bottom();
        }
    }
    update();

}

void ReportDesignView::getSelectCells(QList<ReportCell*>& selCells)
{
    for (int i = 0; i < cells.count(); i++)
    {
        ReportCell* cell = cells.at(i);
        if (cell->selected())
        {
            selCells << cell;
        }
    }

}

void ReportDesignView::copySelectCells()
{
    qDeleteAll(copyCells);
    copyCells.clear();
    QList<ReportCell*> selCells;
    getSelectCells(selCells);
    for (int i = 0; i < selCells.count(); i++)
    {
        ReportCell* cell = selCells.at(i);
        ReportCell* newCell = new ReportCell(this);

        newCell->setWidth(cell->width());
        newCell->setHeight(cell->height());
        newCell->setLeft(cell->left());
        newCell->setTop(cell->top());
        newCell->setText(cell->text());
        copyCells << newCell;

    }
}
