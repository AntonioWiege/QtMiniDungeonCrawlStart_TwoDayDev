#include "mainWindow.h"
#include "gamemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    ///everything relevant through bellow
    gameManager* gM = new gameManager(&w);

    w.show();

    return a.exec();
}
