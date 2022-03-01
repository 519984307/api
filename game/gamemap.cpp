#include "gamemap.h"

GameMap::GameMap(QObject* parent)
    : QObject(parent)
{
    m_step = 48;
    m_cols = 20;
    m_rows = 20;
    m_hero = nullptr;
    m_isStop = true;
    m_scence = nullptr;
    m_exitDoor = nullptr;
}

int GameMap::cols() const
{
    return m_cols;
}

void GameMap::setCols(int cols)
{
    m_cols = cols;
}

int GameMap::rows() const
{
    return m_rows;
}

void GameMap::setRows(int rows)
{
    m_rows = rows;
}

int GameMap::step() const
{
    return m_step;
}

void GameMap::setStep(int step)
{
    m_step = step;
}

QImage GameMap::drawScence()
{
    return QImage();
}

bool GameMap::play()
{
    return true;
}

void GameMap::addGameObject(GameObject* obj)
{
    gameObjects << obj;
    obj->setMap(this);
}

bool GameMap::hasObjectInPostion(GameObject* selObj, int x, int y, int n)
{

    bool ret = false;
    for (int i = 0; i < gameObjects.count(); i++) {
        GameObject* obj = gameObjects.at(i);
        if (obj == selObj) {
            continue;
        }
        if (selObj == hero()) {
            if (obj->gameObjectType() != "墙壁") {
                continue;
            }
        } else {
            if ((obj->gameObjectType() != "墙壁") && (obj->gameObjectType() != "门")) {
                continue;
            }
        }

        QRect rc(x, y, 48, 48);
        if (isOverLap(obj->rect(), rc, n)) {
            qDebug() << obj->rect();
            qDebug() << rc;
            qDebug() << obj->gameObjectType();
            qDebug() << "----";
            ret = true;
            return ret;
        }
    }

    return ret;
}

bool GameMap::isOverLap(const QRect& rc1, const QRect& rc2, int n)
{
    QList<int> lst1;
    lst1 << rc1.left();
    lst1 << rc1.right();
    lst1 << rc2.left();
    lst1 << rc2.right();
    qSort(lst1);

    QList<int> lst2;
    lst2 << rc1.top();
    lst2 << rc1.bottom();
    lst2 << rc2.top();
    lst2 << rc2.bottom();
    qSort(lst2);
    int w = lst1.at(3) - lst1.at(0) + 1 + n;
    int h = lst2.at(3) - lst2.at(0) + 1 + n;

    if ((w < (rc1.width() + rc2.width())) && (h < (rc1.height() + rc2.height()))) {
        qDebug() << w;
        qDebug() << h;
        qDebug() << rc1.width() + rc2.width();
        qDebug() << rc1.height() + rc2.height();
        return true;
    } else {
        return false;
    }
}

GameObject* GameMap::hero() const
{
    return m_hero;
}

void GameMap::setHero(GameObject* hero)
{
    m_hero = hero;
}

bool GameMap::isStop() const
{
    return m_isStop;
}

void GameMap::setIsStop(bool isStop)
{
    m_isStop = isStop;
}

GameScence* GameMap::scence() const
{
    return m_scence;
}

void GameMap::setScence(GameScence* scence)
{
    m_scence = scence;
}

GameObject* GameMap::exitDoor() const
{
    return m_exitDoor;
}

void GameMap::setExitDoor(GameObject* exitDoor)
{
    m_exitDoor = exitDoor;
}

void GameMap::initGame()
{
    qDeleteAll(gameObjects);
    gameObjects.clear();
    m_isStop = false;
}

void GameMap::startGame()
{
    setIsStop(false);
    scence()->startTimer();
}
