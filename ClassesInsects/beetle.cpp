#include "beetle.h"
#include "../Board.h"

const unsigned int Beetle::Max = 2;
unsigned int Beetle::poseBlanc = 0;
unsigned int Beetle::poseNoir = 0;

std::vector<const BoardSpot*> Beetle::moov(int x, int y, const Board& board)const
{
    std::vector<const BoardSpot*> possibilite = board.trouverVoisins(x, y); // prends toutes les cases voisines avec ou sans intecte(s)
    return possibilite;
}

bool Beetle::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}

