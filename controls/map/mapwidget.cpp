#include "mapwidget.h"
#include "ui_mapwidget.h"
QMutex MapWidget::locker;
MapWidget::MapWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MapWidget)
{
    ui->setupUi(this);
    m_mapLeft = 0;
    m_mapTop = 0;
    m_helper.setControl(this);
    m_newMapObject = nullptr;
    setMouseTracking(true);
    m_movedMapObject = nullptr;
    m_selMapObject = nullptr;
    m_mapObjectsMoveEnabled = false;

}

MapWidget::~MapWidget()
{
    delete ui;
}

QString MapWidget::backgroundFilePath() const
{
    return m_backgroundFilePath;
}

void MapWidget::setBackgroundFilePath(const QString& backgroundFilePath)
{
    m_mapLeft = 0;
    m_mapTop = 0;
    m_backgroundFilePath = backgroundFilePath;
    m_backgroundImage = QPixmap(m_backgroundFilePath);
    update();
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QPoint curPt = m_helper.cursorPos();
    QRect clientRc = QRect(0, 0, width(), height());
    painter.fillRect(clientRc, QBrush(Qt::white));
    if (!m_backgroundImage.isNull())
    {
        QRect imgRc = QRect(m_mapLeft, m_mapTop, m_backgroundImage.width(), m_backgroundImage.height());
        painter.drawPixmap(imgRc, m_backgroundImage, m_backgroundImage.rect());

    }
    for (int i = 0; i < objects.count(); i++)
    {
        MapWidgetObject* mapObj = objects.at(i);
        QRect objRc = QRect(mapObj->left() + m_mapLeft, mapObj->top() + m_mapTop, 32, 32);
        QPixmap pix;
        if (mapObj->iconIndex() == 0)
        {
            pix = mapObj->icon();
        }
        else
        {
            pix = MapWidgetObject::icons[mapObj->iconIndex()];
        }
        painter.drawPixmap(objRc, pix, pix.rect());
        mapObj->setViewRect(objRc);
        if (mapObj == m_selMapObject)
        {
            painter.save();
            painter.setPen(QColor(0, 0, 0, 100));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(objRc);

            painter.restore();
        }
        QRect textRc = QRect(objRc.left() - 32, objRc.bottom(), 96, 24);
        if (mapObj->devState() == "")
        {
            painter.drawText(textRc, Qt::AlignCenter, mapObj->name());
        }
        else
        {
            painter.drawText(textRc, Qt::AlignCenter, mapObj->name() + "(" + mapObj->devState() + ")");
        }

    }
    if (m_newMapObject != nullptr)
    {
        QRect newObjRc = QRect(curPt.x() - m_newMapObject->width() / 2, curPt.y() - m_newMapObject->height() / 2, m_newMapObject->width(), m_newMapObject->height());
        painter.drawPixmap(newObjRc, m_newMapObject->icon(), m_newMapObject->icon().rect());
    }

    painter.end();
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
    m_helper.startMouseDown();
    m_selMapObject = nullptr;
    QPoint pt = m_helper.cursorPos();
    for (int i = 0; i < objects.count(); i++)
    {
        MapWidgetObject* obj = objects.at(i);
        if (obj->viewRect().contains(pt))
        {
            m_selMapObject = obj;
            break;
        }
    }
    update();
}

void MapWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper.startMouseUp();
    if (m_newMapObject != nullptr)
    {
        m_newMapObject->setCenterPoint(m_helper.cursorPos());
        emit onAddNewMapWidgetObject(this, m_newMapObject);
        delete  m_newMapObject;
        m_newMapObject = nullptr;

    }
    if (m_movedMapObject != nullptr)
    {
        emit onMoveMapWidgetObject(this, m_movedMapObject);
        m_movedMapObject = nullptr;
    }
    update();
}

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
    locker.lock();
    QPoint pt = m_helper.cursorPos();
    if (m_helper.mousedownFlag())
    {
        int x, y;
        m_helper.mouseMove(x, y);
        m_movedMapObject = nullptr;
        if (m_mapObjectsMoveEnabled)
        {
            for (int i = 0; i < objects.count(); i++)
            {
                MapWidgetObject* obj = objects.at(i);
                if (obj->viewRect().contains(pt))
                {
                    obj->setLeft(obj->left() + x);
                    obj->setTop(obj->top() + y);
                    m_movedMapObject = obj;
                    update();
                    locker.unlock();
                    return;
                }
            }
        }

        m_mapLeft += x;
        m_mapTop += y;

    }
    update();
    locker.unlock();
}

MapWidgetObject* MapWidget::selMapObject() const
{
    return m_selMapObject;
}

void MapWidget::setSelMapObject(MapWidgetObject* selMapObject)
{
    m_selMapObject = selMapObject;
}

void MapWidget::deleteSelectMapObject()
{
    if (m_selMapObject != nullptr)
    {
        objects.removeOne(m_selMapObject);
        delete m_selMapObject;
        m_selMapObject = nullptr;
    }
    update();
}

bool MapWidget::mapObjectsMoveEnabled() const
{
    return m_mapObjectsMoveEnabled;
}

void MapWidget::setMapObjectsMoveEnabled(bool mapObjectsMoveEnabled)
{
    m_mapObjectsMoveEnabled = mapObjectsMoveEnabled;
}

int MapWidget::mapTop() const
{
    return m_mapTop;
}

void MapWidget::setMapTop(int mapTop)
{
    m_mapTop = mapTop;
}

void MapWidget::clearObjects()
{
    m_mapLeft = 0;
    m_mapTop = 0;
    qDeleteAll(objects);
    objects.clear();
    update();
}

int MapWidget::mapLeft() const
{
    return m_mapLeft;
}

void MapWidget::setMapLeft(int mapLeft)
{
    m_mapLeft = mapLeft;
}

MapWidgetObject* MapWidget::newMapObject() const
{
    return m_newMapObject;
}

void MapWidget::setNewMapObject(MapWidgetObject* newMapObject)
{
    m_newMapObject = newMapObject;
    update();
}
