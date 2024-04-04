#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

#include <QLabel>
#include <QKeyEvent>

class player:public QLabel
{
    Q_OBJECT
public:
    player(QWidget *parent);
    ///position in relative pixel space
    QPoint last,next;
    int keyID=0;
    ///position in tile space
    int parentXid=0,parentYid=0;
    void setSpriteByID(int id=0);
    void keyPressEvent(QKeyEvent * event);
    ///handles direction changes
    void updateSlow(map* level);
    ///handles movement interpolation
    void updateFast(float percentage,map* level);
};

#endif // PLAYER_H
