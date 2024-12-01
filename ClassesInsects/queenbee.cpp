#include "QueenBee.h"


const unsigned int QueenBee::Max =1;
unsigned int QueenBee::poseBlanc = 0;
unsigned int QueenBee::poseNoir = 0;
std::vector<const BoardSpot*> QueenBee::moov(int x, int y, const Board& board)const{
    //std::cout<<"\n=========\nDEBUG : dans le moov de la reine \n=========\n\n";
    std::vector <const BoardSpot*> possibilite = board.voisinsNull(x, y);
    //std::cout<<"\n=========\nDEBUG : affichage dans le moov \n=========\n\n";
    //board.afficherpossibilite(possibilite);
    return possibilite;
 }

bool QueenBee::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
