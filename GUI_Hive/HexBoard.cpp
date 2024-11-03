#include "HexBoard.h"
#include "Game.h"

extern Game* game;

HexBoard::HexBoard(){

}

QList<Hex *> HexBoard::getHexes(){
    return hexes;
}

void HexBoard::placeHexes(int x, int y, int cols, int rows){
    int X_SHIFT = 41;
    int Y_SHIFT = 20.5;

    for (size_t i = 0, n = cols; i < n; i++){
        if (i % 2 == 0){ // colonnes paires
            Y_SHIFT = 0;
        }
        else{ // colonnes impaires
            Y_SHIFT = 20.5;
        }
        createHexColumn(x+X_SHIFT*i,y+Y_SHIFT,rows);
    }
}

void HexBoard::createHexColumn(int x, int y, int numOfRows){
    // création de colonnes de Hexes à un endroit spécifique
    // nb de lignes
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Hex* hex = new Hex();
        hex->setPos(x,y+41*i);
        hexes.append(hex);
        game->scene->addItem(hex);

        // initialisation
        hex->setOwner(QString("NOONE"));
        hex->setIsPlaced(true);
    }
}
