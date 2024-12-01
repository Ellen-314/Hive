#include "Board.h"
#include "Insect.h"
<<<<<<< Updated upstream

#include "Controleur.h"
#include <iostream>
#include "test.h"

int main() {
=======
#include "Jeu.h"
#include "Controleur.h"
#include <cstdio>
#include <windows.h>

#pragma execution_character_set("utf-8")

int main() {
    SetConsoleOutputCP( 65001 );

/*
    std::cout << "Pour l'instant tout va bien";

>>>>>>> Stashed changes
    Board board;

    //test();


    // Ajout de cases au plateau
    std::cout << "Ajout de cases au plateau" << std::endl;
    board.addSpot(1, 2);
    board.addSpot(3, 4);
    board.print(std::cout);

    // Ajout d'insectes aux cases
    std::cout << "\nAjout d'insectes aux cases" << std::endl;
    QueenBee* insect1 = new QueenBee();
    Ant* insect2 = new Ant();
    board.addInsectToSpot(1, 2, insect1); // Ajoute insect1 à la case (1, 2)
    board.addInsectToSpot(3, 4, insect2); // Ajoute insect2 à la case (3, 4)
    board.print(std::cout);

    // Suppression de l'insecte de la case (1, 2)
    std::cout << "\nSuppression de l'insecte de la case (1, 2)" << std::endl;
    board.deleteInsectFromSpot(1, 2);
    board.print(std::cout);

    Controleur controleur;
    controleur.demarrerPartie();



    return 0;
}
