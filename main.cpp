#include <iostream>
#include "Joueur.h"

using namespace std;

int main()
{
    // Cr�ation d'un joueur avec la couleur true (blanc)
    Joueur joueur1(true);

    // V�rification et affichage de la couleur du joueur
    if (joueur1.getCouleur()) {
        std::cout << "Le joueur a la couleur: blanc" << std::endl;
    } else {
        std::cout << "Le joueur a la couleur: noir" << std::endl;
    }

    return 0;
}
