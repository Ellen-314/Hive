#include "QueenBee.h"


const unsigned int QueenBee::Max =1;
unsigned int QueenBee::poseBlanc = 0;
unsigned int QueenBee::poseNoir = 0;
std::vector<const BoardSpot*> QueenBee::moov(int x, int y, const Board& board)const{

    std::vector <const BoardSpot*> possibilite = board.voisinsNull(x, y);

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
