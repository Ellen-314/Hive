#include "spider.h"
#include "Board.h"
#include <set>

const unsigned int Spider::Max =2;
unsigned int Spider::poseBlanc = 0;
unsigned int Spider::poseNoir = 0;

std::vector<const BoardSpot*> Spider::moov(int x, int y, const Board& board) {
    std::vector<const BoardSpot*> possibilite;
    std::queue<std::pair<const BoardSpot*, int>> Averifier; // queue avec distance pour chaque case
    std::set<const BoardSpot*> verifie;

    const BoardSpot* SpotArraignee = board.getSpot(x, y);

    Averifier.push({SpotArraignee, 0}); // Pousse la position de départ avec distance 0
    verifie.insert(SpotArraignee);

    while (!Averifier.empty()) {
        // On récupère la case actuelle et sa distance
        const BoardSpot* currentSpot = Averifier.front().first;
        int currentDistance = Averifier.front().second;
        Averifier.pop();

        // Si la distance est exactement 3, on ajoute la case à "possibilite"
        if (currentDistance == 3) {
            possibilite.push_back(currentSpot);
            continue; // Passe au prochain élément dans la queue sans ajouter de voisins
        }

        // Sinon, on continue d'explorer les voisins
        std::vector<const BoardSpot*> voisins = board.voisinsNull(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
        );

        // Spider est un insecte glisseur donc il ne peut pas avoir plus de 5 voisins
        // en réalité on prend pas en compte tous les moments où il ne pourrait pas glisser ...
        for (const auto& voisin : voisins) {
            if (verifie.find(voisin) == verifie.end()) {
                int surroundingInsects = board.trouverVoisinsInsects(
                    voisin->getCoordinates().first,
                    voisin->getCoordinates().second
                ).size();

                // Si le voisin est accessible (moins de 5 insectes autour)
                if (surroundingInsects < 5) {
                    // On ajoute le voisin avec distance + 1 dans la queue
                    Averifier.push({voisin, currentDistance + 1});
                    verifie.insert(voisin);
                }
            }
        }
    }
    return possibilite;
}
