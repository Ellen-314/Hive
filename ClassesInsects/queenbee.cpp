#include "QueenBee.h"


const unsigned int QueenBee::Max =1;
unsigned int QueenBee::poseBlanc = 0;
unsigned int QueenBee::poseNoir = 0;
std::vector<const BoardSpot*> QueenBee::moov(int x, int y, const Board& board)const{
    // la reine se déplace tel un glisseur autour d'elle
    std::vector <const BoardSpot*> possibilite = board.trouverVoisinsGlisseur(x, y);
    return possibilite;
 }

bool QueenBee::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
