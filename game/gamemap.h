#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "gameobject.h"
#include "gamescence.h"
#include <QImage>
#include <QObject>
#include <QPixmap>
class GameObject;
class GameScence;
class GameMap : public QObject {
    Q_OBJECT
public:
    explicit GameMap(QObject* parent = nullptr);

    int cols() const;
    void setCols(int cols);

    int rows() const;
    void setRows(int rows);

    int step() const;
    void setStep(int step);
    virtual QImage drawScence();
    virtual bool play();
    QList<GameObject*> gameObjects;
    void addGameObject(GameObject* obj);
    bool hasObjectInPostion(GameObject* selObj, int x, int y, int n = 0);
    bool isOverLap(const QRect& rc1, const QRect& rc2, int n = 0);
    GameObject* hero() const;
    void setHero(GameObject* hero);

    bool isStop() const;
    void setIsStop(bool isStop);

    GameScence* scence() const;
    void setScence(GameScence* scence);

    GameObject* exitDoor() const;
    void setExitDoor(GameObject* exitDoor);
    virtual void initGame();
    virtual void startGame();

signals:
    void onSuccessed(int ret);
    void onFailed(int ret);

private:
    int m_cols;
    int m_rows;
    int m_step;
    QPoint m_focusPoint;
    GameObject* m_hero;
    GameScence* m_scence;
    GameObject* m_exitDoor;
    bool m_isStop;
};

#endif // GAMEMAP_H
