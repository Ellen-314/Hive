#include "HexBoard.h"
#include "Game.h"
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
    /*QPoint zero(0,0);
    hexHighlight(zero);
    hexHighlightErase(zero);
    zero.setX(1);
    zero.setY(0);
    hexHighlight(zero);*/
    Ant b;
    board.addSpot(1,0);
    board.addInsectToSpot(1,0,&b);
    //afficherBoardQt();
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
    }
}



void HexBoard::hexHighlight(QPoint coordonnes){
    //chercher dans hexes là où hexes[i]->coords == coordonnes
    //si on trouve hex on met setColor(red)

    for (int i=0; i<hexes.size(); i++){
        if (hexes[i]->getCoord()==coordonnes){
            hexes[i]->setColor(Qt::green);
        }
    }
}



void HexBoard::afficherBoardQt(){
    //Board board;

    board.addSpot(0,0);
    board.addSpot(0,1);
    BoardSpot temp(0,0);
    Ant a;
    board.addInsectToSpot(0,1,&a);
    for (int i = 0; i<board.getNb();i++){
        temp = board.getSpotIndex(i);
        if (temp.hasInsect()){
            int x=temp.getCoordinates().first;
            int y=temp.getCoordinates().second;
            qDebug() << "Spot" << i << ": (" << x << "," << y << ")";
            QPoint p;
            p.setX(x);
            p.setY(y);
            hexHighlight(p);
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
        hex->unSetColor();
    }
    hexesHighligted.clear();
}

void HexBoard::addHighlightedHex(Hex* hex, std::string couleur){
    QColor color = ColorDictionary::getColor(couleur);
    hex->setColor(color);
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

