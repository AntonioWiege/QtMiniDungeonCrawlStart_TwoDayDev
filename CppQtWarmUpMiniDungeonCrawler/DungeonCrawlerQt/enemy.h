#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"

#include <QLabel>

class enemy:QLabel
{
    Q_OBJECT
public:
    enemy(QWidget *parent);

    ///position in relative pixel space
    QPoint last,next;
    ///position in tile space
    int parentXid=0,parentYid=0;

    void setSpriteByID(int id=0);
    ///handles direction changes
    void updateSlow(map* level);
    ///handles movement interpolation
    void updateFast(float percentage,map* level);
};

#endif // ENEMY_H
