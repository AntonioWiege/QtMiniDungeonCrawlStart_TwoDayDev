#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "mainWindow.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "vector2.h"

#include "qtimer.h"
#include "QPoint"

class gameManager :QLabel
{
    Q_OBJECT
public:
    gameManager(mainWindow* w);

    mainWindow* mainW;
    ///for color only
    QLabel background;
    ///each level adds 2 more enemies to their count
    int level=0;
    std::vector<enemy*> enemies;
    /// this many times fast executes per slow time tick
    int timerRate=60;
    /// loops with the rate above
    int counter = 0;
    /// mostly for game-logic
    QTimer* timerSlow;
    /// mostly for graphics
    QTimer* timerFast;
    ///  player sprite to view center
    QPoint offsetForView;
    map* levelMap;
    player* playerInstance;
    ///in tile space
    Vector2 goal;

    void genNextStage();
public slots:
    void UpdateSlow();
    void UpdateFast();
};

#endif // GAMEMANAGER_H
