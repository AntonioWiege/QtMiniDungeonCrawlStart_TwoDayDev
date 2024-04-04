#include "map.h"
#include "vector2.h"
#include <iostream>

map::map(QWidget *parent) {
    //instantiate all tiles of empty map.
    for(int y = 0; y < mapSize; y++){
        for(int x = mapSize-1; x > -1; x--){
            tiles[x][y]= new tile(parent);
            for(int i = 0; i < 16; i++){
                tiles[x][y]->tileStack[i]->setGeometry(234*x+117*(y%2),83*y,242,300);
            }
        }
    }
}

void map::regenerateMap()
{
    srand(time(0));

    //reset tiles to random showing state
    for(int y = 0; y < mapSize; y++){
        for(int x = 0; x < mapSize; x++){
            tiles[x][y]->togglingShowing(false);
            ///first false to disable all sprites, true only enables some of them
            if(rand()%2==0)
            tiles[x][y]->togglingShowing(true);
        }
    }

    ///setup points for cellular noise
    int pointCount=rand()%(mapSize/5)+(mapSize/5);
    Vector2* points[pointCount];
    for(int i = 0; i < pointCount; i++){
        points[i] = new Vector2((float)(rand()%mapSize),
                                (float)(rand()%mapSize));
    }
//*
    ///if distance to some two of the points is similar within tollerance, set tile to show
    for(int y = 0; y < mapSize; y++){
        for(int x = 0; x < mapSize; x++){
            for(int i = 0; i < pointCount; i++){
                for(int o = i+1; o < pointCount; o++){
                    Vector2* tilePos = new Vector2((float)x,(float)y);
                    float d = Vector2::manhattan(tilePos,points[i])-Vector2::manhattan(tilePos,points[o]);
                    if(d<0)d=-d;
                    if(d<1){
                        tiles[x][y]->togglingShowing(true);
                    }
                    delete tilePos;
                }
            }
        }
    }//*/
    //room like paths pattern
    for(int y = 0; y < mapSize/5; y++){
        for(int x = 0; x < mapSize/5; x++){
            for(int i = 0; i < 5; i++){
                int idx = x*5+i;
                int idy = y*5+i*2+(i%2);
                if(idy<mapSize&&idy>-1){
                    if(idx<mapSize&&idx>-1){
                        tiles[idx][idy]->togglingShowing(true);
                    }
                }
                idy = y*5+i*2+(i%2)-1;
                if(idy<mapSize&&idy>-1){
                    if(idx<mapSize&&idx>-1){
                        tiles[idx][idy]->togglingShowing(true);
                    }
                }
            }
        }
    }

    //border gen
    for(int i = 0; i < mapSize; i++){
        tiles[i][0]->tileStack[3]->show();
        tiles[i][0]->tileStack[7]->show();
    }
    for(int i = 0; i < mapSize/2; i++){
        tiles[0][i*2]->tileStack[3]->show();
        tiles[0][i*2]->tileStack[14]->show();
        tiles[mapSize-1][i*2]->tileStack[7]->show();
        tiles[mapSize-1][i*2]->tileStack[15]->show();
    }
}

