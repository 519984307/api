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
    else if (m_operation == OP_SET_ORIGIN_POINT)
    {
        m_originPoint = curPt;
        m_operation = OP_NONE;
    }
    update();
}

void Map3dDisgnViewer::mouseMoveEvent(QMouseEvent* event)
{
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
        jarr.append(obj->toExportJsonObject());
    }
    jobj["objects"] = jarr;

    jdoc.setObject(jobj);
    QByteArray data = jdoc.toJson();

    file.write(data);
    file.close();
}


