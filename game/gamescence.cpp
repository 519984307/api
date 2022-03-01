#include "gamescence.h"
#include "ui_gamescence.h"

GameScence::GameScence(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::GameScence)
{
    ui->setupUi(this);
    m_gameMap = nullptr;
    m_tmr = nullptr;

    setMouseTracking(true);
    m_backgroundMusic = new QSoundEffect(this);
    m_failedMusic = new QSoundEffect(this);
    m_successedMusic = new QSoundEffect(this);
    QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];
    QSettings ini(path + "/set.ini", QSettings::IniFormat);
    ini.beginGroup("set");
    m_level = ini.value("level", 1).toInt();
    ini.endGroup();
    m_buttondownFlag = false;
}

GameScence::~GameScence()
{
    delete ui;
}

GameMap* GameScence::gameMap() const
{
    return m_gameMap;
}

void GameScence::setGameMap(GameMap* gameMap)
{
    m_gameMap = gameMap;
}

void GameScence::paintEvent(QPaintEvent* event)
{

    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    if (m_gameMap != nullptr) {

        QImage img = m_gameMap->drawScence();
        QPixmap pix = QPixmap::fromImage(img);
        QPoint pt = m_gameMap->hero()->rect().center();
        QRect rc;
        rc.setRect(pt.x() - width() / 2, pt.y() - height() / 2, width(), height());
        painter.drawPixmap(rect(), pix, rc);
    }
    QPoint pt = mapFromGlobal(cursor().pos());
    m_leftRect.setRect(64, height() - 192, 64, 64);
    if ((m_leftRect.contains(pt)) && (m_buttondownFlag == true)) {
        painter.drawPixmap(m_leftRect, m_buttonDownPix, m_buttonDownPix.rect());
    } else {
        painter.drawPixmap(m_leftRect, m_buttonPix, m_buttonPix.rect());
    }

    m_rightRect.setRect(192, height() - 192, 64, 64);
    if ((m_rightRect.contains(pt)) && (m_buttondownFlag == true)) {
        painter.drawPixmap(m_rightRect, m_buttonDownPix, m_buttonDownPix.rect());
    } else {
        painter.drawPixmap(m_rightRect, m_buttonPix, m_buttonPix.rect());
    }

    m_upRect.setRect(128, height() - 256, 64, 64);
    if ((m_upRect.contains(pt)) && (m_buttondownFlag == true)) {
        painter.drawPixmap(m_upRect, m_buttonDownPix, m_buttonDownPix.rect());
    } else {
        painter.drawPixmap(m_upRect, m_buttonPix, m_buttonPix.rect());
    }

    m_downRect.setRect(128, height() - 128, 64, 64);
    if ((m_downRect.contains(pt)) && (m_buttondownFlag == true)) {
        painter.drawPixmap(m_downRect, m_buttonDownPix, m_buttonDownPix.rect());
    } else {
        painter.drawPixmap(m_downRect, m_buttonPix, m_buttonPix.rect());
    }

    painter.end();
}

void GameScence::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Right) {
        m_gameMap->hero()->moveRight();
    }
    if (event->key() == Qt::Key_Left) {
        m_gameMap->hero()->moveLeft();
    } else if (event->key() == Qt::Key_Up) {
        m_gameMap->hero()->moveUp();
    } else if (event->key() == Qt::Key_Down) {
        m_gameMap->hero()->moveDown();
    }
    update();
}

void GameScence::mouseMoveEvent(QMouseEvent* event)
{
}

void GameScence::timeout()
{
    qDebug() << "play";
    bool ret = true;
    if (m_gameMap != nullptr) {
        ret = m_gameMap->play();
        update();
    }

    //        if (ret == false) {
    //            m_tmr->stop();
    //        }
}

QPixmap GameScence::buttonDownPix() const
{
    return m_buttonDownPix;
}

void GameScence::setButtonDownPix(const QPixmap& buttonDownPix)
{
    m_buttonDownPix = buttonDownPix;
}

void GameScence::mousePressEvent(QMouseEvent* event)
{
    m_buttondownFlag = true;

    QPoint pt = mapFromGlobal(cursor().pos());
    if (m_leftRect.contains(pt)) {
        m_gameMap->hero()->moveLeft();
    }
    if (m_rightRect.contains(pt)) {
        m_gameMap->hero()->moveRight();
    }
    if (m_upRect.contains(pt)) {
        m_gameMap->hero()->moveUp();
    }
    if (m_downRect.contains(pt)) {
        m_gameMap->hero()->moveDown();
    }
    update();
}

void GameScence::mouseReleaseEvent(QMouseEvent* event)
{
    m_buttondownFlag = false;
    update();
}

QPixmap GameScence::buttonPix() const
{
    return m_buttonPix;
}

void GameScence::setButtonPix(const QPixmap& buttonPix)
{
    m_buttonPix = buttonPix;
}

int GameScence::level()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];
    QDir dir;
    dir.mkpath(path);
    QSettings ini(path + "/set.ini", QSettings::IniFormat);
    qDebug() << path + "/set.ini";
    ini.beginGroup("set");
    m_level = ini.value("level", 1).toInt();
    ini.endGroup();
    return m_level;
}

void GameScence::setLevel(int level)
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];
    QSettings ini(path + "/set.ini", QSettings::IniFormat);
    qDebug() << path + "/set.ini";
    ini.beginGroup("set");
    ini.setValue("level", level);
    ini.endGroup();
    m_level = level;
}

QSoundEffect* GameScence::successedMusic() const
{
    return m_successedMusic;
}

void GameScence::setSuccessedMusic(QSoundEffect* successedMusic)
{
    m_successedMusic = successedMusic;
}

void GameScence::startTimer()
{
    if (m_tmr != nullptr) {
        delete m_tmr;
    }
    m_tmr = new QTimer(this);
    connect(m_tmr, &QTimer::timeout, this, &GameScence::timeout);
    m_tmr->setInterval(10);
    m_tmr->start();
    m_backgroundMusic->setVolume(1);
    m_backgroundMusic->play();

    setFocus();
}

QSoundEffect* GameScence::failedMusic() const
{
    return m_failedMusic;
}

void GameScence::setFailedMusic(QSoundEffect* failedMusic)
{
    m_failedMusic = failedMusic;
}

QSoundEffect* GameScence::backgroundMusic() const
{
    return m_backgroundMusic;
}

void GameScence::setBackgroundMusic(QSoundEffect* backgroundMusic)
{
    m_backgroundMusic = backgroundMusic;
}
