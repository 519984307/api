#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "gamemap.h"
#include <QObject>
#include <QPixmap>
#include <QtDebug>
#include <math.h>
enum Orientation {
    Ot_Left,
    Ot_Right,
    Ot_Up,
    Ot_Down
};

class GameMap;
class GameObject : public QObject {
    Q_OBJECT
public:
    explicit GameObject(QObject* parent = nullptr);

    QPixmap image() const;
    void setImage(const QPixmap& image);

    QRect rect() const;
    void setRect(const QRect& rect);

    QString gameObjectType() const;
    void setGameObjectType(const QString& gameObjectType);

    int x() const;
    void setX(int x);
    QList<QPixmap> downImage;
    QList<QPixmap> rightImage;
    QList<QPixmap> leftImage;
    QList<QPixmap> upImage;
    int y() const;
    void setY(int y);
    void radomMove();

    GameMap* map() const;
    void setMap(GameMap* map);
    void resetRect();
    void randomDirections();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    Orientation orientation() const;
    void setOrientation(const Orientation& orientation);
    bool CaOtherGameObject(GameObject* other);
    bool isHitOther(GameObject* other);

signals:

private:
    QPixmap m_image;
    QRect m_rect;
    QString m_gameObjectType;
    int m_x;
    int m_y;
    GameMap* m_map;
    int m_moveX;
    int m_moveY;
    int m_pixIndex;
    QList<QPoint> m_directions;
    Orientation m_orientation;
    QPixmap m_defaultPix;
};

#endif // GAMEOBJECT_H
