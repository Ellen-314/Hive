#include "HexBoard.h"
#include "N_game.h"
#include <QDebug>
#include "ClassesInsects/ant.h"
#include "ColorDictionnary.h"
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
        createHexColumn(x+X_SHIFT*i,y+Y_SHIFT,rows,i);

    }

}

void HexBoard::createHexColumn(int x, int y, int numOfRows,int numOfcols){
    // création de colonnes de Hexes à un endroit spécifique
    // nb de lignes
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Hex* hex = new Hex();
        hex->setPos(x,y+41*i);
        hex->setCoord(-((i-numOfcols/2)-4),numOfcols-7);
        QString coord = QStringLiteral("(%1,%2)").arg(hex->getCoord().x()).arg(hex->getCoord().y());
        hex->setInsectType(coord);
        hexes.append(hex);
        game->scene->addItem(hex);

        // initialisation
        hex->setOwner(QString("NOONE"));
        hex->setIsPlaced(true);
        hex->setIsEmpty(true);
    }
}



void HexBoard::hexHighlight(QPoint coordonnes, QColor color){
    //chercher dans hexes là où hexes[i]->coords == coordonnes
    //si on trouve hex on met setColor(red)

    for (int i=0; i<hexes.size(); i++){
        if (hexes[i]->getCoord()==coordonnes){
            hexes[i]->setColor(color);
        }
    }
}

void HexBoard::eraseHighlight(QPoint coordonnes){
    //chercher dans hexes là où hexes[i]->coords == coordonnes
    //si on trouve hex on met setColor(red)

    for (int i=0; i<hexes.size(); i++){
        if (hexes[i]->getCoord()==coordonnes){
            hexes[i]->unSetColor();
        }
    }
}



void HexBoard::afficherBoardQt(){
    for (int i=0; i<hexes.size(); i++){
        for (int j=0; j<hexes.size(); j++){
            if (i!=j && hexes[i]==hexes[j]) qDebug() << hexes[i]->getCoord() <<"\n";
        }

    }

}
Hex& HexBoard::getHex(QPoint coordonnes){
    for (int i=0; i<hexes.size(); i++){
        if (hexes[i]->getCoord()==coordonnes){
            return *hexes[i];}
    }

}

void HexBoard::eraseHighlighted(){

    for(const auto& hex : hexesHighligted) {
        eraseHighlight(hex->getCoord());
    }
    hexesHighligted.clear();
}

void HexBoard::addHighlightedHex(Hex* hex, std::string couleur){
    QColor color = ColorDictionary::getColor(couleur);
    hexHighlight(hex->getCoord(), color);
    hexesHighligted.append(hex);

}

bool HexBoard::inHighlighted(Hex* hexToFind){
    for(const auto& hex : hexesHighligted) {
        if(hexToFind->getCoord() == hex->getCoord()){
            return true;
        }
    }
    return false;

}

void HexBoard::eraseColor(){
    for (int i=0; i<hexes.size(); i++){
        hexes[i]->unSetColor();
    }
    qDebug()<<"unset color";
}
