#include "spider.h"
#include "../Board.h"
#include <set>

const unsigned int Spider::Max =2;
unsigned int Spider::poseBlanc = 0;
unsigned int Spider::poseNoir = 0;

std::vector<const BoardSpot*> Spider::moov(int x, int y, const Board& board)const {
    std::vector<const BoardSpot*> possibilite;
    std::queue<std::pair<const BoardSpot*, int>> Averifier; // queue avec distance pour chaque case
    std::set<const BoardSpot*> verifie;

    const BoardSpot* SpotArraignee = board.getSpot(x, y);

    Averifier.push({SpotArraignee, 0}); // Pousse la position de d�part avec distance 0
    verifie.insert(SpotArraignee);

    while (!Averifier.empty()) {
        // On r�cup�re la case actuelle et sa distance
        const BoardSpot* currentSpot = Averifier.front().first;
        int currentDistance = Averifier.front().second;
        Averifier.pop();

        // Si la distance est exactement 3, on ajoute la case � "possibilite"
        if (currentDistance == 3) {
            possibilite.push_back(currentSpot);
            continue; // Passe au prochain �l�ment dans la queue sans ajouter de voisins
        }

        // Sinon, on continue d'explorer les voisins
        std::vector<const BoardSpot*> voisins = board.trouverVoisinsGlisseur(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
        );

    }
    return possibilite;
}

bool Spider::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}

