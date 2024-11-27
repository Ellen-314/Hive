#include "grasshopper.h"
#include "../Board.h"

const unsigned int Grasshopper::Max =3;
unsigned int Grasshopper::poseBlanc = 0;
unsigned int Grasshopper::poseNoir = 0;


std::vector<const BoardSpot*> Grasshopper::moov(int x, int y, const Board& board)
{
    std::vector<const BoardSpot*> possibleMoves;
    const BoardSpot* currentSpot = board.getSpot(x, y);

    std::pair<int, int> directions[] = {
        {1, 0},   // (x + 1, y)
        {1, 1},   // (x + 1, y + 1)
        {0, 1},   // (x, y + 1)
        {-1, 0},  // (x - 1, y)
        {-1, -1}, // (x - 1, y - 1)
        {0, -1}   // (x, y - 1)
    };

    // Parcours des directions
    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        const BoardSpot* nextSpot = currentSpot;


        // Avancer dans la direction tant que la case suivante contient un insecte
        while (nextSpot) {
            nextSpot = board.getSpot(nextSpot->getCoordinates().first + newX,
                                    nextSpot->getCoordinates().second + newY);

            // Arr�te si la case est vide ou invalide (en dehors des limites)
            if (!nextSpot || !nextSpot->hasInsect()) {
                break;
            }
        }

        // Si une case vide est trouv�e, elle est ajout�e aux mouvements possibles
        if (nextSpot && !nextSpot->hasInsect()) {
            possibleMoves.push_back(nextSpot);
        }
    }
    return possibleMoves;

}
