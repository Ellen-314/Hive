#include "QueenBee.h"
#include "C:\Users\combl\Documents\GI01\L021\Hive\Board.h"



const unsigned int QueenBee::Max =1;
unsigned int QueenBee::poseBlanc = 0;
unsigned int QueenBee::poseNoir = 0;
void QueenBee::moov(int x, int y, const Board& board){
std::vector <const BoardSpot*> voisinsNuls = board.voisinsNull(x, y);
    for (size_t i =0; i< voisinsNuls.size(); i++){
     std::pair<int, int> coord = voisinsNuls[i]->getCoordinates();
        std::cout << "(" << coord.first << "-" << coord.second << ")" << "\n";
 }}
