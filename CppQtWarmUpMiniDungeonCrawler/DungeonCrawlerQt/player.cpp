#include "player.h"
#include <iostream>

player::player(QWidget *parent) {
    setParent(parent);
    last = QPoint(0,0);
    next = QPoint(0,0);
}

void player::setSpriteByID(int id)
{
    QPixmap pixmap;
    switch(id){
    case 1:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/15_PlayerTopLeft.png").scaled(242,300);
        break;
    case 2:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/16_PlayerTopRight.png").scaled(242,300);
        break;
    case 3:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/17_PlayerBottomRight.png").scaled(242,300);
        break;
    default:
        pixmap = QPixmap(":/All_DepthIndexed/Sprites/14_PlayerBottomLeft.png").scaled(242,300);
        break;
    }

    setPixmap(pixmap);
    setMask(pixmap.mask());

    show();
}

void player::keyPressEvent(QKeyEvent *event)
{
    keyID=0;
    if (event->key() == Qt::Key_Up||event->key() == Qt::Key_W){
        keyID=1;
    }
    if (event->key() == Qt::Key_Left||event->key() == Qt::Key_A){
        keyID=2;
    }
    if (event->key() == Qt::Key_Down||event->key() == Qt::Key_S){
        keyID=3;
    }
    if (event->key() == Qt::Key_Right||event->key() == Qt::Key_D){
        keyID=4;
    }
}
/*
Orientation:
W - TopRight
A - TopLeft
S - BackLeft
D - BackRight
//3,7 lr 14-5
*/
void player::updateSlow(map* level)
{
    //commented out early attempt at wall blocking, because level is not yet in valid playable guarantee.
    ///needed for keyEvent register
    setFocus();
    if (keyID==1){
        //if(!level->tiles[parentXid][parentYid]->tileStack[7]->isVisible())
        if(parentYid>0){
            if(parentYid%2==1){
                if(parentXid<level->mapSize-1){
                    //if(!level->tiles[parentXid+1][parentYid-1]->tileStack[14]->isVisible()&&(level->tiles[parentXid+1][parentYid-1]->tileStack[0]->isVisible()||level->tiles[parentXid+1][parentYid-1]->tileStack[1]->isVisible()))
                    parentXid++;
                }
            }
            //if(!level->tiles[parentXid][parentYid-1]->tileStack[14]->isVisible()&&(level->tiles[parentXid][parentYid-1]->tileStack[0]->isVisible()||level->tiles[parentXid+1][parentYid-1]->tileStack[1]->isVisible()))
            parentYid--;
            setSpriteByID(2);
        }
    }
    if (keyID==2){
        //if(!level->tiles[parentXid][parentYid]->tileStack[3]->isVisible())
        if(parentYid>0){
            if(parentYid%2==0){
                if(parentXid>0){
                    //if(!level->tiles[parentXid-1][parentYid-1]->tileStack[15]->isVisible()&&(level->tiles[parentXid-1][parentYid-1]->tileStack[0]->isVisible()||level->tiles[parentXid-1][parentYid-1]->tileStack[1]->isVisible()))
                    parentXid--;
                }
            }
            //if(!level->tiles[parentXid][parentYid-1]->tileStack[15]->isVisible()&&(level->tiles[parentXid][parentYid-1]->tileStack[0]->isVisible()||level->tiles[parentXid][parentYid-1]->tileStack[1]->isVisible()))
            parentYid--;
            setSpriteByID(1);
        }
    }
    if (keyID==3){
        //if(!level->tiles[parentXid][parentYid]->tileStack[14]->isVisible())
        if(parentYid<level->mapSize-1){
            if(parentYid%2==0){
                if(parentXid>0){
                    //if(!level->tiles[parentXid-1][parentYid+1]->tileStack[7]->isVisible()&&(level->tiles[parentXid-1][parentYid+1]->tileStack[0]->isVisible()||level->tiles[parentXid-1][parentYid+1]->tileStack[1]->isVisible()))
                    parentXid--;
                }
            }
            //if(!level->tiles[parentXid][parentYid+1]->tileStack[7]->isVisible()&&(level->tiles[parentXid][parentYid+1]->tileStack[0]->isVisible()||level->tiles[parentXid][parentYid+1]->tileStack[1]->isVisible()))
            parentYid++;
            setSpriteByID(0);
        }
    }
    if (keyID==4){
        //if(!level->tiles[parentXid][parentYid]->tileStack[15]->isVisible())
        if(parentYid<level->mapSize-1){
            if(parentYid%2==1){
                if(parentXid<level->mapSize-1){
                    //if(!level->tiles[parentXid+1][parentYid+1]->tileStack[3]->isVisible()&&(level->tiles[parentXid+1][parentYid+1]->tileStack[0]->isVisible()||level->tiles[parentXid+1][parentYid+1]->tileStack[1]->isVisible()))
                    parentXid++;
                }
            }
            //if(!level->tiles[parentXid][parentYid+1]->tileStack[3]->isVisible()&&(level->tiles[parentXid][parentYid+1]->tileStack[0]->isVisible()||level->tiles[parentXid][parentYid+1]->tileStack[1]->isVisible()))
            parentYid++;
            setSpriteByID(3);
        }
    }

    last = next;
    ///get pixel position from some sprite of the tile at updated parent position
    next = level->tiles[parentXid][parentYid]->tileStack[13]->pos();
    if(next.y()>last.y())
    ///correct rendering depth
    stackUnder(level->tiles[parentXid][parentYid]->tileStack[14]);

    keyID=0;
}

void player::updateFast(float percentage,map* level)
{
    QPoint delta = last*(1.0-percentage)+next*percentage;
    setGeometry(delta.x(),delta.y(),242,300);
    if(percentage>=0.5){
        ///correct rendering depth
        stackUnder(level->tiles[parentXid][parentYid]->tileStack[14]);
    }
    ///clamp against errors
    if(percentage<=0){
        setGeometry(last.x(),last.y(),242,300);
    }
    if(percentage>=0.99){
        setGeometry(next.x(),next.y(),242,300);
    }
}
