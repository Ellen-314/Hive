#include "QueenBee.h"


const unsigned int QueenBee::Max =1;
unsigned int QueenBee::poseBlanc = 0;
unsigned int QueenBee::poseNoir = 0;
std::vector<const BoardSpot*> QueenBee::moov(int x, int y, const Board& board)const{
    std::cout<<"dans le moov de la reine \n";
    std::vector <const BoardSpot*> possibilite = board.voisinsNull(x, y);
    std::cout<<"affichage dans le moov  \n";
    board.afficherpossibilite(possibilite);
    return possibilite;
 }

bool QueenBee::estPasAuMax(bool couleur){
        if (couleur)
        {
            return getPoseNoir()< getMax();

        }
    else{
        return getPoseBlanc()< getMax();

    }
     }
