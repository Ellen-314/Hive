#include "mosquito.h"
#include "../Board.h"

const unsigned int Mosquito::Max =1;
unsigned int Mosquito::poseBlanc=0;
unsigned int Mosquito::poseNoir=0;


std::vector<const BoardSpot*> Mosquito::moov(int x, int y, const Board& board)const
{
    std::vector <const BoardSpot*> possibilite;
    std::vector <const BoardSpot*> possibiliteInsect;
    std::vector <const BoardSpot*> voisins = board.trouverVoisinsInsects(x, y);

    for (const BoardSpot* voisin : voisins)
    {

        Insect* insect = voisin->getInsect();
        possibiliteInsect = insect->moov(x, y, board); // on utilise la méthode moov de ses insectes voisins.

        possibilite.insert(possibilite.end(), possibiliteInsect.begin(), possibiliteInsect.end());

    }
    return possibilite;
}

bool Mosquito::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
