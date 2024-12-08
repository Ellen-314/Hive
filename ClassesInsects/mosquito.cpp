#include "mosquito.h"

const unsigned int Mosquito::Max =1;


std::vector<const BoardSpot*> Mosquito::moov(int x, int y, const Board& board)const
{
    std::vector <const BoardSpot*> possibilite;
    std::vector <const BoardSpot*> possibiliteInsect;
    std::vector <const BoardSpot*> voisins = board.trouverVoisinsInsects(x, y);

    for (const BoardSpot* voisin : voisins)
    {
        std::pair<int, int> voisinCoords = voisin->getCoordinates(); // R�cup�rer les coordonn�es du voisin

        int voisinX = voisinCoords.first;  // R�cup�rer la premi�re valeur
        int voisinY = voisinCoords.second; // R�cup�rer la deuxi�me valeur

//        switch(typeid(voisin->getInsect()).name)
//        {
//        case Ant :
//            possibiliteInsect = Ant::moov(voisinX, voisinY);
//            break;
//        case Beetle:
//            possibiliteInsect = Beetle::moov(voisinX, voisinY);
//        }



        possibilite.insert(possibilite.end(), possibiliteInsect.begin(), possibiliteInsect.end());

    }
    return possibilite;
}
