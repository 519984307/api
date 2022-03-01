#ifndef GAMESCENCE_H
#define GAMESCENCE_H

#include "gamemap.h"
#include <QAudioInput>
#include <QDir>
#include <QKeyEvent>
#include <QPainter>
#include <QSettings>
#include <QSound>
#include <QSoundEffect>
#include <QStandardPaths>
#include <QTimer>
#include <QWidget>
#include <QtDebug>

namespace Ui {
class GameScence;
}
enum MoveDirection {
    MvLeft,
    MvRight,
    MvUp,
    MvDown
};

class GameMap;
class GameScence : public QWidget {
    Q_OBJECT

public:
    explicit GameScence(QWidget* parent = nullptr);
    ~GameScence();

    GameMap* gameMap() const;
    void setGameMap(GameMap* gameMap);
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    QSoundEffect* backgroundMusic() const;
    void setBackgroundMusic(QSoundEffect* backgroundMusic);

    QSoundEffect* failedMusic() const;
    void setFailedMusic(QSoundEffect* failedMusic);

    QSoundEffect* successedMusic() const;
    void setSuccessedMusic(QSoundEffect* successedMusic);
    void startTimer();
    int level();
    void setLevel(int level);

    QPixmap buttonPix() const;
    void setButtonPix(const QPixmap& buttonPix);

    QPixmap buttonDownPix() const;
    void setButtonDownPix(const QPixmap& buttonDownPix);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
public slots:
    void timeout();

private:
    Ui::GameScence* ui;
    GameMap* m_gameMap;
    QTimer* m_tmr;
    QSoundEffect* m_backgroundMusic;
    QSoundEffect* m_failedMusic;
    QSoundEffect* m_successedMusic;
    int m_level;
    QRect m_leftRect;
    QRect m_upRect;
    QRect m_rightRect;
    QRect m_downRect;
    QPixmap m_buttonPix;
    QPixmap m_buttonDownPix;
    bool m_buttondownFlag;
};

#endif // GAMESCENCE_H
