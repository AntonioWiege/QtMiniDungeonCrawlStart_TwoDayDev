#ifndef TILE_H
#define TILE_H

#include <QLabel>

class tile
{
private:
    bool isShowing;
public:
    tile(QWidget *parent);
    bool getShowingState();
    void togglingShowing(bool value);
    ///ordered by depth for rendering
    QLabel* tileStack[16];
};

#endif // TILE_H
