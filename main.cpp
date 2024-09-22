#include <iostream>
#include "Joueur.h"

using namespace std;

int main()
{
    // Création d'un joueur avec la couleur true (blanc)
    Joueur joueur1(true);

    // Vérification et affichage de la couleur du joueur
    if (joueur1.getCouleur()) {
        std::cout << "Le joueur a la couleur: blanc" << std::endl;
    } else {
        std::cout << "Le joueur a la couleur: noir" << std::endl;
    }

    return 0;
}
