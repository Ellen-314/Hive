#include "grasshopper.h"
#include "../Board.h"

const unsigned int Grasshopper::Max =3;
unsigned int Grasshopper::poseBlanc = 0;
unsigned int Grasshopper::poseNoir = 0;


std::vector<const BoardSpot*> Grasshopper::moov(int x, int y, const Board& board)const
{
    std::vector<const BoardSpot*> possibilite;

    std::pair<int, int> directions[] = {
        {1, 0},   // (x + 1, y)
        {1, 1},   // (x + 1, y + 1)
        {0, 1},   // (x, y + 1)
        {-1, 0},  // (x - 1, y)
        {-1, -1}, // (x - 1, y - 1)
        {0, -1}   // (x, y - 1)
    };

    //On parcourt chaque direction
    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        const BoardSpot* nextSpot = board.getSpot(newX, newY);
        //si dans cette direction il y a un insecte on va au plus loin jusqu'à ue case sans insecte
        if(nextSpot->hasInsect()){
            do {newX = nextSpot->getCoordinates().first + dir.first;
                newY =nextSpot->getCoordinates().second + dir.second;
                nextSpot = board.getSpot(newX, newY);}while(nextSpot->hasInsect());
            possibilite.push_back(nextSpot);
        }}
    return possibilite;

}

bool Grasshopper::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
