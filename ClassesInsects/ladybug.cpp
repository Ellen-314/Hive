#include "ladybug.h"
#include "../Board.h"

const unsigned int Ladybug::Max =1;

std::vector<const BoardSpot*> Ladybug::moov(int x, int y, const Board& board)const {
    std::vector<const BoardSpot*> possibilite;
    std::queue<std::pair<const BoardSpot*, int>> Averifier; // queue avec distance pour chaque case
    std::set<const BoardSpot*> verifie;

    const BoardSpot* SpotCoccinelle = board.getSpot(x, y);

    Averifier.push({SpotCoccinelle, 0}); // Pousse la position de d�part avec distance 0
    verifie.insert(SpotCoccinelle);

    while (!Averifier.empty()) {
        // On récupère la case actuelle et sa distance
        const BoardSpot* currentSpot = Averifier.front().first;
        int currentDistance = Averifier.front().second;
        Averifier.pop();

        // Si la distance est exactement 2, ne pas ajouter directement à "possibilite"
        if (currentDistance == 2) {
            // Explorer les voisinsInsectes pour trouver leurs voisinsNuls
            std::vector<const BoardSpot*> voisinsInsectes = board.trouverVoisinsInsects(
                currentSpot->getCoordinates().first,
                currentSpot->getCoordinates().second
            );

            for (const BoardSpot* voisinInsecte : voisinsInsectes) {
                // Récupérer les voisins nuls du voisinInsecte
                std::vector<const BoardSpot*> voisinsNuls = board.voisinsNull(
                    voisinInsecte->getCoordinates().first,
                    voisinInsecte->getCoordinates().second
                );

                // Ajouter ces voisins nuls dans "possibilite"
                for (const BoardSpot* voisinNull : voisinsNuls) {
                    possibilite.push_back(voisinNull);
                }
            }
            continue; // Passe au prochain élément dans la queue
        }

        // Sinon, on continue d'explorer les voisins
        std::vector<const BoardSpot*> voisins = board.trouverVoisinsInsects(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
        );

        for (const BoardSpot* voisin : voisins) {
            if (verifie.find(voisin) == verifie.end()) { // Si le voisin n'a pas encore été vérifié
                Averifier.push({voisin, currentDistance + 1}); // Ajoute le voisin avec une distance incrémentée
                verifie.insert(voisin); // Marque le voisin comme vérifié
            }
        }
    }
    return possibilite;
}

bool Ladybug::estPasAuMax(bool couleur){
   if (couleur==0){ return getPoseNoir()< getMax(); }
   else{ return getPoseBlanc()< getMax(); }
}