#include "map3ddisgnviewer.h"
#include "ui_map3ddisgnviewer.h"

Map3dDisgnViewer::Map3dDisgnViewer(QWidget* parent) :
    BaseWidget(parent),
    ui(new Ui::Map3dDisgnViewer)
{
    ui->setupUi(this);
    m_operation = OP_NONE;
    setMouseTracking(true);
    m_draw = new DrawObject(this);
    m_originPoint = QPoint(0, 0);
    m_baseMap = QPixmap();
    m_showBasemap = true;
}

Map3dDisgnViewer::~Map3dDisgnViewer()
{
    delete ui;
}

void Map3dDisgnViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QPoint curPt = m_helper->cursorPos();
    QRect clientRc = m_helper->clientRect();
    painter.begin(this);
    if (m_showBasemap)
    {
        if (!m_baseMap.isNull())
        {
            painter.drawPixmap(m_baseMap.rect(), m_baseMap, m_baseMap.rect());
        }
    }



    if (m_operation == OP_SET_ORIGIN_POINT)
    {
        m_draw->drawOriginCross(painter, curPt, clientRc);
    }
    else
    {
        m_draw->drawOriginCross(painter, m_originPoint, clientRc);
    }

    for (int i = 0; i < m_objects.count(); i++)
    {
        Map3dObject* obj = m_objects.at(i);
        m_draw->drawLines(painter, obj->points);
        painter.drawPoint(obj->centerPoint());
        if (obj->selected())
        {
            painter.setBrush(Qt::red);

        }
        else
        {
            painter.setBrush(obj->color());
        }
        painter.drawPolygon(obj->polygon());


    }



    QPoint pt1, pt2, pt0;
    for (int i = 0; i < m_addPoints.count(); i++)
    {
        if (i == 0)
        {
            pt1 = m_addPoints.at(i);
            pt0 = m_addPoints.at(i);
            pt2 = pt1;
        }
        else
        {
            pt2 = m_addPoints.at(i);
            painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt2.y());
            pt1 = pt2;
        }
    }
    if (m_operation == OP_ADD_OBJECT)
    {
        if (m_addPoints.count() > 0)
        {
            if (curPt == m_addPoints.at(0))
            {
                painter.setPen(Qt::green);
            }
            else
            {
                painter.setPen(Qt::black);
            }
            painter.drawLine(pt2.x(), pt2.y(), curPt.x(), curPt.y());
        }

    }
    else if ((m_operation == OP_ADD_RECT_OBJECT) && (m_helper->mousedownFlag()))
    {
        QPoint pt1 = m_helper->mousedownPoint();
        m_draw->drawRect(painter, pt1, curPt);
    }


    painter.end();
}

ControlOperation Map3dDisgnViewer::operation() const
{
    return m_operation;
}

void Map3dDisgnViewer::setOperation(ControlOperation newOperation)
{
    m_operation = newOperation;
}

void Map3dDisgnViewer::addBaseMap(QString fileName)
{
    m_baseMap = QPixmap(fileName);
}

void Map3dDisgnViewer::deleteSelectedObjects()
{
    for (int i = m_objects.count() - 1; i >= 0; i--)
    {
        Map3dObject* obj = m_objects.at(i);
        if (obj->selected())
        {
            m_objects.removeAt(i);
            delete  obj;
        }
    }
    update();
}

void Map3dDisgnViewer::moveSelectedObjectToBottom()
{
    Map3dObject* selObj = nullptr;
    int selIndex = -1;

    for (int i = 0; i < m_objects.count(); i++)
    {
        if (m_objects.at(i)->selected())
        {
            selObj = m_objects[i];
            selIndex = i;
            break;
        }
    }

    if (selObj == nullptr)
    {
        return;
    }
    m_objects.takeAt(selIndex);
    m_objects.insert(0, selObj);
    update();
}

void Map3dDisgnViewer::setSelectedObject()
{
    for (Map3dObject* obj : qAsConst(m_objects))
    {
        obj->setSelected(false);
    }
    QList<Map3dObject*> selObjs;


    QPoint curPt = m_helper->cursorPos();
    for (Map3dObject* obj : qAsConst(m_objects))
    {

        QPainterPath path;
        path.addPolygon(obj->polygon());
        if (path.contains(curPt))
        {
            selObjs << obj;
        }

    }
    if (selObjs.count() > 0)
    {
        qSort(selObjs.begin(), selObjs.end(), [](Map3dObject * obj1, Map3dObject * obj2)
        {
            QSize sz1 = obj1->polygon().boundingRect().size();
            QSize sz2 = obj2->polygon().boundingRect().size();
            return sz1.width() * sz1.height() < sz2.width() * sz2.height();
        });
        selObjs.last()->setSelected(true);

    }

    update();
}

Map3dObject* Map3dDisgnViewer::selectedObject()
{
    for (Map3dObject* obj : qAsConst(m_objects))
    {
        if (obj->selected())
        {
            return obj;
        }
    }

    return nullptr;
}

void Map3dDisgnViewer::cloneSelectedObject()
{
    Map3dObject* obj = selectedObject();
    if (obj == nullptr)
    {
        return;
    }
    Map3dObject* newObj = new Map3dObject(this);
    for (int i = 0; i < obj->points.count(); i++)
    {
        newObj->points << QPoint(obj->points.at(i).x() + 50, obj->points.at(i).y() + 50);
    }
    newObj->setName(obj->name());
    newObj->setHeight(obj->height());
    newObj->setColor(obj->color());
    m_objects << newObj;
    obj->setSelected(false);
    newObj->setSelected(true);
    update();

}


void Map3dDisgnViewer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        if (m_operation == OP_ADD_OBJECT)
        {


            Map3dObject* obj = new Map3dObject(this);
            obj->points << m_addPoints;

            m_objects << obj;
            m_addPoints.clear();
            m_operation = OP_NONE;
            update();
            return;

        }
    }

    QPoint curPt = m_helper->cursorPos();

    if (m_operation == OP_ADD_OBJECT)
    {
        m_addPoints << curPt;

    }
    else if (m_operation == OP_ADD_RECT_OBJECT)
    {
        m_helper->startMouseDown();
    }
    else if (m_operation == OP_MOVE_OBJECT)
    {
        m_helper->startMouseDown();
        setSelectedObject();
    }
    else if (m_operation == OP_SET_ORIGIN_POINT)
    {
        m_originPoint = curPt;
        m_operation = OP_NONE;
    }
    else
    {


        setSelectedObject();
    }
    update();
}

void Map3dDisgnViewer::mouseMoveEvent(QMouseEvent* event)
{
    if ((m_operation == OP_MOVE_OBJECT) && (m_helper->mousedownFlag()))
    {
        Map3dObject* obj = selectedObject();
        if (obj == nullptr)
        {
            return;
        }
        int x, y;
        m_helper->mouseMove(x, y);
        obj->moveBy(x, y);
    }
    update();
}

void Map3dDisgnViewer::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    if (m_operation == OP_ADD_OBJECT)
    {
        m_addPoints << curPt;

        Map3dObject* obj = new Map3dObject(this);
        obj->points << m_addPoints;

        m_objects << obj;
        m_addPoints.clear();
        m_operation = OP_NONE;

    }
    else
    {
        for (int i = 0; i < m_objects.count(); i++)
        {



            Map3dObject* obj = m_objects.at(i);
            if (obj->selected())
            {
                showMap3dObjectPropertyDialog(obj);
            }
        }

    }
    update();
}

void Map3dDisgnViewer::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_operation == OP_ADD_RECT_OBJECT)
    {
        QPoint pt1 = m_helper->mouseMovePoint();
        QPoint pt2 = m_helper->cursorPos();
        m_draw->reSetPoints(pt1, pt2);

        Map3dObject* obj = new Map3dObject(this);
        obj->points << pt1;
        obj->points << QPoint(pt2.x(), pt1.y());
        obj->points << pt2;
        obj->points << QPoint(pt1.x(), pt2.y());
        obj->points << pt1;
        m_objects << obj;
        m_operation = OP_NONE;
        m_helper->startMouseUp();

    }
    if (m_operation == OP_MOVE_OBJECT)
    {
        m_helper->startMouseUp();

    }

    update();
}

bool Map3dDisgnViewer::showBasemap() const
{
    return m_showBasemap;
}

void Map3dDisgnViewer::setShowBasemap(bool newShowBasemap)
{
    m_showBasemap = newShowBasemap;
    update();
}

void Map3dDisgnViewer::saveToFile(QString fileName)
{
    m_fileName = fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QJsonDocument jdoc;
    QJsonObject jobj;
    QJsonArray jarr;
    for (int i = 0; i < m_objects.count(); i++)
    {
        Map3dObject* obj = m_objects.at(i);
        jarr.append(obj->toJsonObject());
    }
    jobj["objects"] = jarr;

    jdoc.setObject(jobj);
    QByteArray data = jdoc.toJson();

    file.write(data);
    file.close();

}

void Map3dDisgnViewer::save()
{
    if (m_fileName == "")
    {

    }
    else
    {
        saveToFile(m_fileName);
    }

}

void Map3dDisgnViewer::saveAs()
{
    QString path = QFileDialog::getSaveFileName();
    if (path == "")
    {
        return;
    }
    saveToFile(path);

}

void Map3dDisgnViewer::loadFromFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jobj = jdoc.object();
    QJsonArray jarr = jobj["objects"].toArray();
    for (int i = 0; i < jarr.count(); i++)
    {
        Map3dObject* obj = new Map3dObject(this);
        QJsonObject jdata = jarr.at(i).toObject();
        obj->fromJsonObject(jdata);
        m_objects << obj;
    }

    file.close();
    update();
}

void Map3dDisgnViewer::exportToFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QJsonDocument jdoc;
    QJsonObject jobj;
    QJsonArray jarr;
    for (int i = 0; i < m_objects.count(); i++)
    {
        Map3dObject* obj = m_objects.at(i);
        QPoint pt = obj->centerPoint();
        obj->setExportPosition(QPoint(pt.x() - m_originPoint.x(), pt.y() - m_originPoint.y()));
        jarr.append(obj->toExportJsonObject());
    }
    jobj["objects"] = jarr;

    jdoc.setObject(jobj);
    QByteArray data = jdoc.toJson();

    file.write(data);
    file.close();
}


