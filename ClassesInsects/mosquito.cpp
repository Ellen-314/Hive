#include "mosquito.h"
#include "../Board.h"

const unsigned int Mosquito::Max =1;


std::vector<const BoardSpot*> Mosquito::moov(int x, int y, const Board& board)const
{
    std::vector <const BoardSpot*> possibilite;
    std::vector <const BoardSpot*> possibiliteInsect;
    std::vector <const BoardSpot*> voisins = board.trouverVoisinsInsects(x, y);

    for (const BoardSpot* voisin : voisins)
    {

        int voisinX = voisin->getCoordinates().first;  // R�cup�rer la premi�re valeur
        int voisinY = voisin->getCoordinates().second; // R�cup�rer la deuxi�me valeur

        Insect* insect = voisin->getInsect();
        possibiliteInsect = insect->moov(voisinX, voisinY, board);

        possibilite.insert(possibilite.end(), possibiliteInsect.begin(), possibiliteInsect.end());

    }
    return possibilite;
}

bool Mosquito::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}