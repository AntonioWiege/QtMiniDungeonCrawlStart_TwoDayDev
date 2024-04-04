#include "enemy.h"

enemy::enemy(QWidget *parent) {
    setParent(parent);
    last = QPoint(0,0);
    next = QPoint(0,0);
}

void enemy::setSpriteByID(int id)
{
    QPixmap pixmap;
    switch(id){
    case 1:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/19_EnemyTopLeft.png"   ).scaled(242,300);
        break;
    case 2:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/20_EnemyTopRight.png"  ).scaled(242,300);
        break;
    case 3:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/21_EnemyBottomRight.png").scaled(242,300);
        break;
    default:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/18_EnemyBottomLeft.png").scaled(242,300);
        break;
    }

    setPixmap(pixmap);
    setMask(pixmap.mask());

    show();
}

void enemy::updateSlow(map* level)
{
    switch(rand()%4){
    case 0:
        if(parentYid>0){
            if(parentYid%2==1){
                if(parentXid<level->mapSize-1)
                    parentXid++;
            }
            parentYid--;
            setSpriteByID(2);
        }
        break;
    case 1:
        if(parentYid>0){
            if(parentYid%2==0){
                if(parentXid>0)
                    parentXid--;
            }
            parentYid--;
            setSpriteByID(1);
        }
        break;
    case 2:
            if(parentYid<level->mapSize-1){
                if(parentYid%2==0){
                    if(parentXid>0)
                        parentXid--;
                }
                parentYid++;
                setSpriteByID(0);
            }
        break;
    default:
        if(parentYid<level->mapSize-1){
            if(parentYid%2==1){
                if(parentXid<level->mapSize-1)
                    parentXid++;
            }
            parentYid++;
            setSpriteByID(3);
        }
        break;
    }

    last = next;
    ///get pixel position from some sprite of the tile at updated parent position
    next = level->tiles[parentXid][parentYid]->tileStack[13]->pos();
    if(next.y()>last.y())
    ///correct rendering depth
    stackUnder(level->tiles[parentXid][parentYid]->tileStack[14]);
}
///percentage is 0-1 in between slow update ticks
void enemy::updateFast(float percentage,map* level)
{
    QPoint interpolatedPos = last*(1.0-percentage)+next*percentage;
    setGeometry(interpolatedPos.x(),interpolatedPos.y(),242,300);
    if(percentage>=0.5){
        ///correct rendering depth
        stackUnder(level->tiles[parentXid][parentYid]->tileStack[14]);
    }
    ///clamp against errors
    if(percentage<=0){
        setGeometry(last.x(),last.y(),242,300);
    }
    if(percentage>=0.95){
        setGeometry(next.x(),next.y(),242,300);
    }
}
