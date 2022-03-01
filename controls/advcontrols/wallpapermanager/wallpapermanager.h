#ifndef WALLPAPERMANAGER_H
#define WALLPAPERMANAGER_H

#include <QObject>
#include "windows.h"

class WallPaperManager : public QObject
{
    Q_OBJECT
public:
    explicit WallPaperManager(QObject* parent = nullptr);
public:
    void changeWallPaper(QString path);

signals:


};

#endif // WALLPAPERMANAGER_H
