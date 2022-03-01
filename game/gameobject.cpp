#include "gameobject.h"

GameObject::GameObject(QObject* parent)
    : QObject(parent)
{
    int n[3] = { -1, 0, 1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QPoint pt(n[i], n[j]);
            m_directions << pt;
        }
    }
    QPoint pt = m_directions.at(qrand() % m_directions.size());
    m_moveX = pt.x();
    m_moveY = pt.y();
    m_orientation = Ot_Down;
    m_pixIndex = 0;
}

QPixmap GameObject::image() const
{
    return m_image;
}

void GameObject::setImage(const QPixmap& image)
{
    m_image = image;
    m_defaultPix = image;
}

QRect GameObject::rect() const
{
    return m_rect;
}

void GameObject::setRect(const QRect& rect)
{
    m_rect = rect;
}

QString GameObject::gameObjectType() const
{
    return m_gameObjectType;
}

void GameObject::setGameObjectType(const QString& gameObjectType)
{
    m_gameObjectType = gameObjectType;
}

int GameObject::x() const
{
    return m_x;
}

void GameObject::setX(int x)
{
    m_x = x;
}

int GameObject::y() const
{
    return m_y;
}

void GameObject::setY(int y)
{
    m_y = y;
}

void GameObject::radomMove()
{
    int x = m_x + m_moveX;
    int y = m_y + m_moveY;
    bool f = this->m_map->hasObjectInPostion(this, x, y);
    if ((f == true) || ((m_moveX == 0) && (m_moveY == 0))) {
        randomDirections();
        for (int i = 0; i < m_directions.count(); i++) {
            QPoint pt = m_directions.at(i);
            m_moveX = pt.x();
            m_moveY = pt.y();
            x = m_x + m_moveX;
            y = m_y + m_moveY;
            f = this->m_map->hasObjectInPostion(this, x, y);
            if (f == false) {
                break;
            }
        }
    }

    m_x = x;
    m_y = y;
    resetRect();
}

GameMap* GameObject::map() const
{
    return m_map;
}

void GameObject::setMap(GameMap* map)
{
    m_map = map;
}

void GameObject::resetRect()
{
    m_rect.setRect(m_x, m_y, 48, 48);
}

void GameObject::randomDirections()
{
    for (int i = 0; i < m_directions.count(); i++) {
        int j = qrand() % m_directions.count();
        m_directions.swap(i, j);
    }
}

void GameObject::moveRight()
{
    if (m_map->isStop()) {
        return;
    }
    int x = m_x + 5;
    int y = m_y;
    if (m_map->hasObjectInPostion(this, x, y, 5) == true) {
        return;
    }
    if (m_orientation != Ot_Right) {
        m_orientation = Ot_Right;
        m_pixIndex = 0;

    } else {
        if ((m_pixIndex + 1) < rightImage.count()) {
            m_pixIndex++;
        } else {
            m_pixIndex = 0;
        }
    }
    m_image = rightImage.at(m_pixIndex);

    m_x = x;
    m_y = y;
    resetRect();
}

void GameObject::moveLeft()
{
    if (m_map->isStop()) {
        return;
    }
    int x = m_x - 5;
    int y = m_y;
    if (m_map->hasObjectInPostion(this, x, y, 5) == true) {
        return;
    }
    if (m_orientation != Ot_Left) {
        m_orientation = Ot_Left;
        m_pixIndex = 0;

    } else {
        if ((m_pixIndex + 1) < leftImage.count()) {
            m_pixIndex++;
        } else {
            m_pixIndex = 0;
        }
    }
    m_image = leftImage.at(m_pixIndex);
    m_x = x;
    m_y = y;
    resetRect();
}

void GameObject::moveUp()
{
    if (m_map->isStop()) {
        return;
    }
    int x = m_x;
    int y = m_y - 5;
    if (m_map->hasObjectInPostion(this, x, y, 5) == true) {
        return;
    }
    if (m_orientation != Ot_Up) {
        m_orientation = Ot_Up;
        m_pixIndex = 0;

    } else {
        if ((m_pixIndex + 1) < downImage.count()) {
            m_pixIndex++;
        } else {
            m_pixIndex = 0;
        }
    }
    m_image = upImage.at(m_pixIndex);
    m_x = x;
    m_y = y;
    resetRect();
}

void GameObject::moveDown()
{
    if (m_map->isStop()) {
        return;
    }
    int x = m_x;
    int y = m_y + 5;
    if (m_map->hasObjectInPostion(this, x, y, 5) == true) {
        return;
    }
    if (m_orientation != Ot_Down) {
        m_orientation = Ot_Down;
        m_pixIndex = 0;

    } else {
        if ((m_pixIndex + 1) < downImage.count()) {
            m_pixIndex++;
        } else {
            m_pixIndex = 0;
        }
    }
    m_image = downImage.at(m_pixIndex);
    m_x = x;
    m_y = y;
    resetRect();
}

Orientation GameObject::orientation() const
{
    return m_orientation;
}

void GameObject::setOrientation(const Orientation& orientation)
{
    m_orientation = orientation;
}

bool GameObject::CaOtherGameObject(GameObject* other)
{
    QRect rc;
    rc.setRect(m_x - 100, m_y - 100, 200, 200);
    if (rc.contains(QPoint(other->x(), other->y()))) {

        if (m_x > other->x()) {
            m_moveX = -1;
        } else {
            m_moveX = 1;
        }
        if (m_y > other->y()) {
            m_moveY = -1;
        } else {
            m_moveY = 1;
        }
        return true;
    } else {
        return false;
    }
}

bool GameObject::isHitOther(GameObject* other)
{
    QRect rc1 = m_rect;
    QRect rc2 = other->rect();
    QPoint pt1 = rc1.center();
    QPoint pt2 = rc2.center();
    double l = sqrt((pt1.x() - pt2.x()) * (pt1.x() - pt2.x()) + (pt1.y() - pt2.y()) * (pt1.y() - pt2.y()));
    return l < 10;
}
