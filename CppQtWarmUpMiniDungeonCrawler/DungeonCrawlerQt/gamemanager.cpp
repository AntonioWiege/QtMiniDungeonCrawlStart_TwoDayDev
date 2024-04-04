#include "gamemanager.h"
#include <iostream>

gameManager::gameManager(mainWindow* w) {
    mainW=w;
    background.setParent(w->window());
    background.setGeometry(0,0,19000,10000);
    background.setStyleSheet("QLabel { background-color : black; color : black; }");

    setGeometry(0,0,19000,10000);
    setParent(w->window());
    show();

    levelMap = new map(this);

    playerInstance = new player(this);

    for(int i = 0; i < (levelMap->mapSize*levelMap->mapSize)/25; i++){
        enemies.push_back(new enemy(this));
        enemies.back()->setSpriteByID();
    }

    genNextStage();

    timerSlow = new QTimer(this);
    connect(timerSlow, SIGNAL(timeout()), this, SLOT(UpdateSlow()));
    timerSlow->start(600);

    timerFast = new QTimer(this);
    connect(timerFast, SIGNAL(timeout()), this, SLOT(UpdateFast()));
    timerFast->start(600/timerRate);
}

void gameManager::genNextStage()
{
    level++;
    levelMap->regenerateMap();
    ///reset player to center
    playerInstance->setSpriteByID();
    playerInstance->parentXid=levelMap->mapSize/2;
    playerInstance->parentYid=levelMap->mapSize/2;
    playerInstance->last=QPoint(levelMap->tiles[playerInstance->parentXid][playerInstance->parentYid]->tileStack[0]->pos());
    playerInstance->next=QPoint(levelMap->tiles[playerInstance->parentXid][playerInstance->parentYid]->tileStack[0]->pos());
    ///extend & reset enemies
    for(int i = 0; i < 2; i++){
        enemies.push_back(new enemy(this));
        enemies.back()->setSpriteByID();
    }
    for(int i = 0; i < (levelMap->mapSize*levelMap->mapSize)/25; i++){
        enemies[i]->parentXid=rand()%levelMap->mapSize;
        enemies[i]->parentYid=rand()%levelMap->mapSize;
        enemies[i]->last=QPoint(levelMap->tiles[enemies[i]->parentXid][enemies[i]->parentYid]->tileStack[0]->pos());
        enemies[i]->next=QPoint(levelMap->tiles[enemies[i]->parentXid][enemies[i]->parentYid]->tileStack[0]->pos());
    }

    levelMap->tiles[(int)goal.x][(int)goal.y]->tileStack[13]->hide();
    ///set goal (stairs) to one of the map corners
    switch(rand()%4){
    case 1:
        levelMap->tiles[0][0]->tileStack[13]->show();
        goal = Vector2(0,0);
        break;
    case 2:
        levelMap->tiles[0][levelMap->mapSize-1]->tileStack[13]->show();
        goal = Vector2(0,levelMap->mapSize-1);
        break;
    case 3:
        levelMap->tiles[levelMap->mapSize-1][0]->tileStack[13]->show();
        goal = Vector2(levelMap->mapSize-1,0);
        break;
    default:
        levelMap->tiles[levelMap->mapSize-1][levelMap->mapSize-1]->tileStack[13]->show();
        goal = Vector2(levelMap->mapSize-1,levelMap->mapSize-1);
        break;
    }

    ///calc offset for camera following player
    setGeometry(0,0,19000,10000);
    playerInstance->setGeometry(0,0,242,300);
    playerInstance->setFocus();
    offsetForView = QPoint(850,500-300/2)-playerInstance->pos();
    setGeometry(offsetForView.x(),offsetForView.y(),19000,10000);
}



void gameManager::UpdateSlow()
{
    /*
    Call AIs
    */
    counter=0;
    playerInstance->updateSlow(levelMap);
    for (const auto e : enemies) {
        e->updateSlow(levelMap);
    }
    if(playerInstance->parentXid == goal.x&&playerInstance->parentYid == goal.y){
        genNextStage();
    }
}

void gameManager::UpdateFast()
{
    ///had some lagging behind, chose sharp overshoot over it
    counter+=2;
    if(counter>timerRate)counter=timerRate;
    auto percentage = (float)counter/(float)(timerRate);
    //std::cout<<percentage<<std::endl;
    playerInstance->updateFast(percentage,levelMap);
    for (const auto e : enemies) {
        e->updateFast(percentage,levelMap);
    }
    setGeometry(offsetForView.x()-playerInstance->pos().x(),offsetForView.y()-playerInstance->pos().y(),19000,10000);
}
