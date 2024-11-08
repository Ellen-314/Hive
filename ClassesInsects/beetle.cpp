#include "beetle.h"
#include "Board.h"

const unsigned int Beetle::Max = 2;
unsigned int Beetle::poseBlanc = 0;
unsigned int Beetle::poseNoir = 0;

std::vector<const BoardSpot*> Beetle::moov(int x, int y, const Board& board)
{
    std::vector<const BoardSpot*> possibilite = board.trouverVoisins(x, y);
    return possibilite;
}
