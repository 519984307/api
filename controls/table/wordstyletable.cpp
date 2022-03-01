#include "wordstyletable.h"
#include "ui_wordstyletable.h"

WordStyleTable::WordStyleTable(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::WordStyleTable)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
}

WordStyleTable::~WordStyleTable()
{
    delete ui;
}

void WordStyleTable::loadFromJson(QString pathName)
{
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jTableObj = jdoc.object();
    //默认
    QJsonObject jDefaultObj = jTableObj["default"].toObject();

    m_marginLeft = jDefaultObj["marginLeft"].toInt();
    m_marginTop = jDefaultObj["marginTop"].toInt();
    m_cellWidth = jDefaultObj["cellWidth"].toInt();
    m_cellHeight = jDefaultObj["cellHeight"].toInt();

    QJsonArray jCellsObj = jTableObj["cells"].toArray();
    m_fieldCellMaps.clear();
    for (int i = 0; i < jCellsObj.count(); i++)
    {
        QJsonObject jCellObj = jCellsObj.at(i).toObject();
        WordStyleTableCell* cell = new WordStyleTableCell(this);
        cell->setColIndex(jCellObj["colIndex"].toInt());
        cell->setRowIndex(jCellObj["rowIndex"].toInt());
        if (jCellObj["colSpan"].isNull())
        {
            cell->setColSpan(1);
        }
        else
        {
            cell->setColSpan(jCellObj["colSpan"].toInt());
        }

        if (jCellObj["rowSpan"].isNull())
        {
            cell->setRowSpan(1);
        }
        else
        {
            cell->setRowSpan(jCellObj["rowSpan"].toInt());
        }

        if (jCellObj["borderLeft"].isNull())
        {
            cell->setBorderLeft(true);
        }
        else
        {
            cell->setBorderLeft(jCellObj["borderLeft"].toBool());
        }
        if (jCellObj["borderRight"].isNull())
        {
            cell->setBorderRight(true);
        }
        else
        {
            cell->setBorderRight(jCellObj["borderRight"].toBool());
        }
        if (jCellObj["borderTop"].isNull())
        {
            cell->setBorderTop(true);
        }
        else
        {
            cell->setBorderTop(jCellObj["borderTop"].toBool());
        }
        if (jCellObj["borderBottom"].isNull())
        {
            cell->setBorderBottom(true);
        }
        else
        {
            cell->setBorderBottom(jCellObj["borderBottom"].toBool());
        }

        if (jCellObj["style"].isNull())
        {
            cell->setStyle("text");
        }
        else
        {
            cell->setStyle(jCellObj["style"].toString());
        }

        if (cell->style() == "edit")
        {
            cell->edit = new LabelEdit(this);
            cell->edit->setHidden(true);

        }

        if (jCellObj["value"].isNull())
        {
            cell->setValue("");
        }
        else
        {
            cell->setValue(jCellObj["value"].toString());
        }

        if (!jCellObj["extraWidth"].isNull())
        {
            cell->setExtraWidth(jCellObj["extraWidth"].toInt());
        }

        if (!jCellObj["extraLeft"].isNull())
        {
            cell->setExtraLeft(jCellObj["extraLeft"].toInt());
        }
        if (!jCellObj["fieldName"].isNull())
        {
            cell->setFieldName(jCellObj["fieldName"].toString());
            m_fieldCellMaps[cell->fieldName()] = cell;
        }
        m_cells << cell;
    }

    file.close();
    update();
}

QJsonArray WordStyleTable::dataToJsonArray()
{
    QJsonArray arr;
    for (int i = 0; i < m_cells.count() ; i++)
    {
        WordStyleTableCell* cell = m_cells.at(i);
        if (cell->fieldName() != "")
        {
            QJsonObject jobj;
            jobj["index"] = i;
            jobj["fieldName"] = cell->fieldName();
            jobj["value"] = cell->value();
            arr.append(jobj);
        }
    }

    return arr;
}

QJsonArray WordStyleTable::notNullDataToJsonArray()
{
    QJsonArray arr;
    for (int i = 0; i < m_cells.count() ; i++)
    {
        WordStyleTableCell* cell = m_cells.at(i);
        if (cell->fieldName() != "")
        {
            if (cell->value() != "")
            {
                QJsonObject jobj;
                jobj["index"] = i;
                jobj["fieldName"] = cell->fieldName();
                jobj["value"] = cell->value();
                arr.append(jobj);
            }

        }
    }

    return arr;

}

void WordStyleTable::loadDataFromArray(QJsonArray& arr)
{
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject jCellObj = arr.at(i).toObject();
        WordStyleTableCell* cell = m_fieldCellMaps.value(jCellObj["fieldName"].toString(), nullptr);
        if (cell != nullptr)
        {
            if (cell->style() == "edit")
            {
                cell->setValue(jCellObj["value"].toString());
            }
        }
    }

}

QString WordStyleTable::cellValue(QString fieldName)
{
    WordStyleTableCell* cell = m_fieldCellMaps.value(fieldName, nullptr);
    if (cell == nullptr)
    {
        return "";
    }
    return cell->value();

}

void WordStyleTable::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(Qt::white));
    for (int i = 0; i < m_cells.count(); i++)
    {
        WordStyleTableCell* cell = m_cells.at(i);
        QRect rc(m_marginLeft + cell->colIndex()*m_cellWidth + cell->extraLeft(),
                 m_marginTop + cell->rowIndex()*m_cellHeight,
                 m_cellWidth * cell->colSpan() + cell->extraWidth(),
                 m_cellHeight * cell->rowSpan());
        if (cell->borderLeft())
        {
            painter.drawLine(rc.left(), rc.top(), rc.left(), rc.bottom());
        }
        if (cell->borderTop())
        {
            painter.drawLine(rc.left(), rc.top(), rc.right(), rc.top());
        }
        if (cell->borderRight())
        {
            painter.drawLine(rc.right() + 1, rc.top(), rc.right() + 1, rc.bottom());
        }
        if (cell->borderBottom())
        {
            painter.drawLine(rc.left(), rc.bottom() + 1, rc.right(), rc.bottom() + 1);
        }
        if (cell->style() == "text")
        {
            painter.drawText(rc, Qt::AlignCenter, cell->value());
        }
        else if (cell->style() == "edit")
        {
            painter.drawText(rc, Qt::AlignCenter, cell->value());
        }
        cell->setRect(rc);


    }
    painter.end();
}

void WordStyleTable::mouseMoveEvent(QMouseEvent* event)
{
    update();
    for (int i = 0; i < m_cells.count(); i++)
    {
        WordStyleTableCell* cell = m_cells.at(i);
        if ((cell->style() == "edit") &&
            (cell->edit->isHidden()))
        {
            QRect edtRc(cell->rect().left() + 1,
                        cell->rect().top() + 1,
                        cell->rect().width() - 2,
                        cell->rect().height() - 2);
            cell->edit->showEdit(edtRc, cell->edit->text(), false);
        }
    }

}
