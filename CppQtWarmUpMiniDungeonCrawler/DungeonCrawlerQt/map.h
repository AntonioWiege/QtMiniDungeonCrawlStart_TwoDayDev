#ifndef MAP_H
#define MAP_H

#include "tile.h"

#include <random>

class map
{
public:
    map(QWidget *parent);

    static const int mapSize = 15;
    tile* tiles[mapSize][mapSize];
    void regenerateMap();
};

#endif // MAP_H
