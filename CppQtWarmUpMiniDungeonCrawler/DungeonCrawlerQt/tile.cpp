#include "tile.h"

tile::tile(QWidget *parent) {
    isShowing=false;
    ///create all sprite objects that could be in any given tile
    for(int i = 0; i < 16; i++){
        tileStack[i]= new QLabel(parent);
    }
    tileStack[0]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/0_FloorBroken.png").scaled(242,300));
    tileStack[1]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/1_Floor.png").scaled(242,300));
    tileStack[2]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/2_Coin.png").scaled(242,300));
    tileStack[3]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/3_WallBackLeft.png").scaled(242,300));
    tileStack[4]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/4_FloorGrass.png").scaled(242,300));
    tileStack[5]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/5_FloorRocks.png").scaled(242,300));
    tileStack[6]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/6_WallLightLeft.png").scaled(242,300));
    tileStack[7]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/7_WallBackRight.png").scaled(242,300));
    tileStack[8]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/8_WallLightRight.png").scaled(242,300));
    tileStack[9]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/9_ManaPotion.png").scaled(242,300));
    tileStack[10]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/10_LifePotion.png").scaled(242,300));
    tileStack[11]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/11_Plant.png").scaled(242,300));
    tileStack[12]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/12_Shop.png").scaled(242,300));
    tileStack[13]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/13_GoalStairs.png").scaled(242,300));
    tileStack[14]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/22_WallFrontLeft.png").scaled(242,300));
    tileStack[15]->setPixmap(QPixmap(":/All_DepthIndexed/Sprites/23_WallFrontRight.png").scaled(242,300));
    for(int i = 0; i < 16; i++){
        tileStack[i]->setMask(tileStack[i]->pixmap().mask());
        tileStack[i]->hide();
    }
}

bool tile::getShowingState()
{
    return isShowing;
}
///This is a good example of very bad naming, mixed code that shouldn't be here and just plain upsetting code.
void tile::togglingShowing(bool value)
{
    if(value){
        //stuff happening
        if(rand()%4>0){
            if(rand()%2>0){
                tileStack[0]->show();
            }else{
                tileStack[1]->show();
            }

            if(rand()%86>1){
                if(rand()%39>28){
                    tileStack[2]->show();
                }
                if(rand()%33>31){
                    tileStack[9]->show();
                }
                if(rand()%33>31){
                    tileStack[10]->show();
                }
                if(rand()%5>3){
                    tileStack[11]->show();
                }
                if(rand()%2>0){
                    tileStack[4]->show();
                }
                if(rand()%2>0){
                    tileStack[5]->show();
                }
            }else if(rand()%4>2){
                tileStack[12]->show();
            }else{
             //   tileStack[13]->show();
            }

            if(rand()%4>2){
                tileStack[3]->show();
            if(rand()%6>4)
                tileStack[6]->show();
            }
            if(rand()%4>2){
                tileStack[7]->show();
            if(rand()%6>4)
                tileStack[8]->show();
            }
            if(rand()%18>16){
                tileStack[14]->show();
            }
            if(rand()%18>16){
                tileStack[15]->show();
            }
        }
    }else{
        for(int i = 0; i < 16; i++){
            tileStack[i]->hide();
        }
    }
    isShowing=value;
}
