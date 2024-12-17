#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <QList>
#include "Hex.h"
#include "Board.h"
class HexBoard{
public:
    // constructeurs
    HexBoard();

    // getter
    QList<Hex*> getHexes();

    void placeHexes(int x, int y, int cols, int rows);
    void hexHighlight(QPoint coordonnes);
    void eraseHighlighted();
    void addHighlightedHex(Hex* hex, std::string couleur);
    bool inHighlighted(Hex* hexToFind);
    Hex& getHex(QPoint coordonnes);
    void afficherBoardQt();

private:
    void createHexColumn(int x, int y, int numOfRows,int numOfcols);
    QList<Hex*> hexes;
    QList<Hex*> hexesHighligted;
    Board board;
};

#endif // HEXBOARD_H
