#include <iostream>
#include "Joueur.h"
#include "Insect.h"

using namespace std;

int main()
{
    // Création d'un joueur avec la couleur true (blanc)
    Player joueur1(true);

    // Vérification et affichage de la couleur du joueur
    if (joueur1.getColor()) {
        cout << "Le joueur a la couleur: blanc" << endl;
    } else {
        cout << "Le joueur a la couleur: noir" << endl;
    }

    // Création de plusieurs insectes
    Insect insect1;
    Insect insect2;
    Insect insect3;
    Insect insect4;

    // Configuration des voisins pour insect1
    insect1.setNeighborTop(&insect2);      // insect2 est au-dessus de insect1
    insect1.setNeighborBottom(&insect3);   // insect3 est en-dessous de insect1
    insect1.setNeighborTopRight(&insect4); // insect4 est en haut à droite de insect1

    // Définir l'attribut "covered" et "color" pour insect1
    insect1.setCovered(true);
    insect1.setColor(true); // insect1 est blanc

    // Afficher l'état de insect1
    cout << "Insect1 est-il couvert ? " << (insect1.isCovered() ? "Oui" : "Non") << endl;
    cout << "Insect1 est de quelle couleur ? " << (insect1.getColor() ? "Blanc" : "Noir") << endl;

    // Tester la méthode moov()
    insect1.moov();

    // Tester l'accès aux voisins
    if (insect1.getNeighborTop() != nullptr) {
        cout << "Insect1 a un voisin au dessus." << endl;
    }

    if (insect1.getNeighborBottom() != nullptr) {
        cout << "Insect1 a un voisin en dessous." << endl;
    }

    if (insect1.getNeighborTopRight() != nullptr) {
        cout << "Insect1 a un voisin en haut à droite." << endl;
    }

    if (insect1.getNeighborBottom() == nullptr) {
        cout << "Insect1 à un voisin en bas." << endl;
    }

    return 0;
}
