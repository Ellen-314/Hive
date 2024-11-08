#include "Board.h"
#include "Insect.h"
#include "Ant.h"
#include "Spider.h"
#include <iostream>

int main() {
    Board board;

    // Ajout de cases au plateau
    std::cout << "Ajout de cases au plateau" << std::endl;
    board.addSpot(1, 2);
    board.addSpot(3, 4);
    board.print(std::cout);

    // Ajout d'insectes aux cases
    std::cout << "\nAjout d'insectes aux cases" << std::endl;
    Insect* ant1 = new Ant();
    Insect* ant2 = new Ant();
    board.addInsectToSpot(1, 2, ant1); // Ajoute insect1 à la case (1, 2)
    board.addInsectToSpot(3, 4, ant2); // Ajoute insect2 à la case (3, 4)
    board.print(std::cout);

    // Suppression de l'insecte de la case (1, 2)
    std::cout << "\nSuppression de l'insecte de la case (1, 2)" << std::endl;
    board.deleteInsectFromSpot(1, 2);
    board.print(std::cout);

    // Essaye de la méthode moov pour Spider

    // Créer un objet Spider
    Spider spider;

    // Position initiale de l'araignée
    int startX = 5;
    int startY = 5;

    // Calculer les mouvements possibles
    std::vector<const BoardSpot*> moves = spider.moov(startX, startY, board);

    // Afficher les mouvements possibles
    std::cout << "Mouvements possibles pour Spider depuis (" << startX << ", " << startY << "):" << std::endl;
    for (const BoardSpot* spot : moves) {
        std::cout << "(" << spot->getCoordinates().first << ", " << spot->getCoordinates().second << ")" << std::endl;
    }

    return 0;
}
