#include "fngrid.h"
#include "ui_fngrid.h"

FnGrid::FnGrid(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnGrid)
{
    ui->setupUi(this);
    m_gridEdit = new FnGridCellEdit(this);
    m_gridEdit->setHidden(true);
    connect(m_gridEdit, &FnGridCellEdit::returnPressed, this, &FnGrid::onGridEditReturnPressed);
    m_selectedCell = nullptr;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(0);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    m_isEditOnClick = true;
    setMouseTracking(true);
}

FnGrid::~FnGrid()
{
    delete ui;
}

FnGridRow* FnGrid::appendRow(int rowHeight)
{
    FnGridRow* rowData = new FnGridRow(this);
    gridRows << rowData;
    rowData->setGrid(this);
    rowData->setHeight(rowHeight);
    return rowData;
}

FnGridRow* FnGrid::appendChildRow(FnGridRow* parentRow, int rowHeight)
{
    FnGridRow* curRow = getLastChildRow(parentRow);
    return insertRowAfterCurRow(curRow);
}

FnGridRow* FnGrid::getLastChildRow(FnGridRow* parentRow)
{
    FnGridRow* row = parentRow;
    for (int i = 0; i < gridRows.count(); i++)
    {
        FnGridRow* r = gridRows.at(i);
        if (r->headerRow() == parentRow)
        {
            row = r;
        }
    }


    return row;
}

void FnGrid::getSelectedCell()
{

    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < gridRows.count(); i++)
    {
        FnGridRow* rowData = gridRows.at(i);
        for (int j = 0; j < rowData->rowCells.count(); j++)
        {
            FnGridCell* cell = rowData->rowCells.at(j);
            if (cell->textRect().contains(pt))
            {
                if (m_selectedCell != cell)
                {
                    if (m_gridEdit->isHidden() == false)
                    {
                        m_selectedCell->setValue(m_gridEdit->text());
                    }
                    m_selectedCell = cell;
                }
                break;
            }


        }
    }
}

void FnGrid::setNextCells()
{
    FnGridCell* preCell = nullptr;
    for (int i = 0; i < gridRows.count() - 1; i++)
    {
        FnGridRow* rowData = gridRows.at(i);
        for (int j = 0; j < rowData->rowCells.count(); j++)
        {
            FnGridCell* cell = rowData->rowCells.at(j);
            if (cell->readOnly())
            {
                continue;
            }
            if (preCell == nullptr)
            {
                preCell = cell;
            }
            else
            {
                preCell->setNextCell(cell);
                preCell = cell;
            }
        }
    }
}

void FnGrid::loadFromJson(QString pathName)
{
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jdocObj = jdoc.object();
    QJsonArray jRows = jdocObj["rows"].toArray();

    for (int i = 0; i < jRows.count(); i++)
    {
        QJsonObject JCellsObj = jRows.at(i).toObject();
        QJsonArray jCells = JCellsObj["cells"].toArray();
        int rowHeight = 32;
        if (!JCellsObj["height"].isNull())
        {
            rowHeight = JCellsObj["height"].toInt();
        }

        FnGridRow* GrdRow = appendRow(rowHeight);

        if (!JCellsObj["tag"].isNull())
        {
            GrdRow->setTag(JCellsObj["tag"].toString());
        }
        if (!JCellsObj["code"].isNull())
        {
            GrdRow->setCode(JCellsObj["code"].toString());
        }
        int l = 100;
        for (int j = 0; j < jCells.count(); j++)
        {
            QJsonObject jcellObj = jCells.at(j).toObject();
            FnGridCell* cell = GrdRow->addCell();
            cell->setReadOnly(jcellObj["readOnly"].toBool());
            cell->setWidth(jcellObj["width"].toInt());
            cell->setLeft(l);
            cell->setValue(jcellObj["value"].toString());

            if (!jcellObj["extraHeight"].isNull())
            {
                cell->setExtraHeight(jcellObj["extraHeight"].toInt());
            }

            if (!jcellObj["extraLeft"].isNull())
            {
                cell->setExtraLeft(jcellObj["extraLeft"].toInt());
            }

            if (!jcellObj["extraTop"].isNull())
            {
                cell->setExtraTop(jcellObj["extraTop"].toInt());
            }



            l += cell->width();

        }
    }
    update();
}

FnGridRow* FnGrid::insertRowAfterCurRow(FnGridRow* curRow, int rowHeight)
{
    int i = gridRows.indexOf(curRow);
    if (i == (gridRows.count() - 1))
    {
        return appendRow(rowHeight);
    }
    else
    {
        FnGridRow* rowData = new FnGridRow(this);
        gridRows.insert(i + 1, rowData);
        rowData->setHeight(rowHeight);
        rowData->setGrid(this);
        return rowData;
    }
}

FnGridRow* FnGrid::insertRowBeforeCurRow(FnGridRow* curRow, int rowHeight)
{
    int i = gridRows.indexOf(curRow);
    FnGridRow* rowData = new FnGridRow(this);
    gridRows.insert(i, rowData);
    rowData->setHeight(rowHeight);
    rowData->setGrid(this);
    return rowData;
}

void FnGrid::setCellFocus(FnGridCell* cell)
{
    if (cell->readOnly())
    {
        return;
    }
    m_selectedCell = cell;
    m_gridEdit->setHidden(false);
    m_gridEdit->setText(m_selectedCell->value());
    m_gridEdit->setFocus();
    setNextCells();

}

FnGridRow* FnGrid::getNextRow(FnGridCell* cell)
{
    FnGridRow* rowData = cell->rowData();
    int i = gridRows.indexOf(rowData);
    if (i == (gridRows.count() - 1))
    {
        return nullptr;
    }
    else
    {
        return gridRows.at(i + 1);
    }

}

FnGridRow* FnGrid::getRowByCode(QString code)
{
    for (int i = 0; i < gridRows.count(); i++)
    {
        FnGridRow* row = gridRows.at(i);
        if (row->code() == code)
        {
            return row;
        }
    }

    return nullptr;

}

void FnGrid::onGridEditReturnPressed()
{
    qDebug() << "ok";
    if (m_selectedCell == nullptr)
    {
        return;
    }
    qDebug() << m_selectedCell->fieldName();
    emit selectCellKeyPress(m_selectedCell);
    FnGridCell* nextCell = m_selectedCell->nextCell();
    if (nextCell == nullptr)
    {
        return;
    }
    m_selectedCell->setValue(m_gridEdit->text());
    m_selectedCell = nextCell;
    qDebug() << nextCell->textRect() << height();
    if (nextCell->textRect().bottom() > height())
    {
        qDebug() << nextCell->textRect() << height();
        m_helper->setItemsTop(m_helper->itemsTop() - nextCell->textRect().height());
        QApplication::processEvents();
    }

    if (!m_selectedCell->readOnly())
    {
        m_gridEdit->setHidden(false);
        m_gridEdit->setText(m_selectedCell->value());
        m_gridEdit->setFocus();
    }
    else
    {
        m_gridEdit->setHidden(true);
    }


    update();
}

void FnGrid::paintEvent(QPaintEvent* event)
{
    int t = m_helper->itemsTop();
    QPainter painter;
    painter.begin(this);
    for (int i = 0; i < gridRows.count(); i++)
    {
        FnGridRow* rowData = gridRows.at(i);
        for (int j = 0; j < rowData->rowCells.count(); j++)
        {
            FnGridCell* cell = rowData->rowCells.at(j);

            QRect textRc(cell->left() + cell->extraLeft(), t + cell->extraTop(), cell->width(), rowData->height() + cell->extraHeight());
            cell->setTextRect(textRc);
            if (cell == m_selectedCell)
            {
                if (m_gridEdit->isHidden() == false)
                {
                    m_gridEdit->setGeometry(m_helper->innerRect(textRc));
                }
            }
            painter.fillRect(textRc, QBrush(cell->backColor()));
            if (cell->topLine()->isDraw())
            {
                painter.drawLine(textRc.left(), textRc.top(), textRc.right(), textRc.top());
            }
            if (cell->leftLine()->isDraw())
            {
                painter.drawLine(textRc.left(), textRc.top(), textRc.left(), textRc.bottom());
            }
            if (cell->rightLine()->isDraw())
            {
                painter.drawLine(textRc.right() + 1, textRc.top(), textRc.right() + 1, textRc.bottom());
            }
            if (cell->bottomLine()->isDraw())
            {
                painter.drawLine(textRc.left(), textRc.bottom() + 1, textRc.right(), textRc.bottom() + 1);
            }
            if ((cell->readOnly() == true) && (cell == m_selectedCell))
            {
                painter.fillRect(textRc, QBrush(QColor(203, 203, 203)));
            }
            else  if ((cell->readOnly() == false) && (cell == m_selectedCell))
            {
                QRect innerTextRc(textRc.left() + 1, textRc.top() + 1, textRc.width() - 2, textRc.height() - 2);
                painter.fillRect(innerTextRc, QBrush(QColor(255, 255, 255)));
            }
            painter.drawText(textRc, Qt::AlignCenter, cell->value());
        }
        t += rowData->height();

    }
    painter.end();
}

void FnGrid::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        getSelectedCell();
        if (m_selectedCell == nullptr)
        {
            update();
            return;
        }
        setNextCells();
        m_gridEdit->setHidden(true);

        update();
        if (m_selectedCell != nullptr)
        {
            emit rightClickCell(this, m_selectedCell);

        }
        update();
        return;
    }
    if (m_isEditOnClick)
    {
        editCell();
    }

}

void FnGrid::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (!isEditOnClick())
    {
        editCell();
    }
}

void FnGrid::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    m_helper->setItemsTop(m_helper->itemsTop() + y);


}

void FnGrid::keyPressEvent(QKeyEvent* event)
{
    if (m_selectedCell != nullptr)
    {
        if ((event->key() == Qt::Key_Return) ||
            (event->key() == Qt::Key_Enter))
        {
            if (m_selectedCell->readOnly())
            {
                emit selectCellKeyPress(m_selectedCell);
            }

        }
    }
}

void FnGrid::leaveEvent(QEvent* event)
{
    if (m_selectedCell != nullptr)
    {
        if (m_gridEdit != nullptr)
        {
            if (!m_gridEdit->isHidden())
            {
                m_selectedCell->setValue(m_gridEdit->text());
            }
        }

    }
}

bool FnGrid::isEditOnClick() const
{
    return m_isEditOnClick;
}

void FnGrid::setIsEditOnClick(bool newIsEditOnClick)
{
    m_isEditOnClick = newIsEditOnClick;
}

void FnGrid::removeRow(FnGridRow* row)
{
    if (row->rowCells.indexOf(m_selectedCell) >= 0)
    {
        m_selectedCell = nullptr;
    }
    gridRows.removeOne(row);
    delete row;
    update();
}

FnGridCell* FnGrid::selectedCell()
{
    return m_selectedCell;
}

void FnGrid::setHeaderChildsOrder(FnGridRow* headerRow, int col)
{
    int n = 1;
    for (int i = 0; i < gridRows.count(); i++)
    {
        FnGridRow* row = gridRows.at(i);
        if (row->headerRow() == headerRow)
        {
            row->cellAt(0)->setValue(QString("%1").arg(n));
            n++;
        }
    }
}

void FnGrid::editCell()
{
    getSelectedCell();
    if (m_selectedCell == nullptr)
    {
        update();
        return;
    }
    setNextCells();
    if (!m_selectedCell->readOnly())
    {
        m_gridEdit->setHidden(false);
        m_gridEdit->setText(m_selectedCell->value());
        m_gridEdit->setFocus();
    }
    else
    {
        m_gridEdit->setHidden(true);
        emit clickCell(m_selectedCell);
    }

    update();

}


