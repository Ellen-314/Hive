#include <algorithm> // pour la fonction std::find

bool Board::isConnexe() const {

    // Collecter toutes les cases avec des insectes
    std::vector<const BoardSpot*> insectSpots;
    for (size_t i = 0; i < nb; ++i) {
        if (board_spots[i]->hasInsect()) {
            insectSpots.push_back(board_spots[i]);
        }
    }

    // Si aucune case n'a d'insecte, on considère le plateau comme connexe
    if (insectSpots.empty()) return true;


    std::vector<const BoardSpot*> visited; // Pour stocker les cases visitées
    std::vector<const BoardSpot*> toVisit; // Pile pour les voisins à explorer

    // Commencer par la première case avec un insecte
    toVisit.push_back(insectSpots[0]);

    while (!toVisit.empty()) {
        const BoardSpot* current = toVisit.back();
        toVisit.pop_back();

        // Si non visité, ajouter aux visités
        if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
            visited.push_back(current);

            // Ajouter les voisins avec des insectes à la pile
            std::vector<const BoardSpot*> voisins = trouverVoisins(
                current->getCoordinates().first,
                current->getCoordinates().second
            );
            for (const auto& voisin : voisins) {
                if (voisin->hasInsect() &&
                    std::find(visited.begin(), visited.end(), voisin) == visited.end()) {
                    toVisit.push_back(voisin);
                }
            }
        }
    }

    // Vérifier que toutes les cases avec des insectes ont été visitées
    return visited.size() == insectSpots.size();
}
