#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "Board.h"
#include "Insect.h"


#include <iostream>

// Exception pour gestion des erreurs dans la classe Controleur
class ControleurException : public std::exception {
private:
    std::string message;

public:
    ControleurException(const std::string& msg) : message(msg) {}
    std::string getMessage() const { return message; }
};

class Controleur {
private:
    Board board;

    // Méthode pour afficher le menu principal avec les différentes actions disponibles
    void afficherMenu() const;

    // Méthode pour obtenir de la part l'utilisateur des coordonnées de la case où une action doit être effectuée
    std::pair<int, int> demanderCoordonnees() const;

public:
    // Méthode principale pour lancer le jeu et gérer les interactions utilisateur durant la partie
    void demarrerPartie();

    // Méthode pour ajouter une case au plateau
    void ajouterCase();

    // Méthode pour ajouter un insecte à une case
    void ajouterInsecte();

    // Méthode pour déplacer un insecte, différent de moov dans Insect qui testera les différentes possibilités de déplacement
    void deplacerInsecte();

    // Méthode pour supprimer une case du plateau
    void supprimerCase();

    // Méthode pour annuler un coup
    void annulerCoup();



    // Constructeur
    Controleur()=default;

    const Board& getPlateau() const { return board; }
    Board& getPlateau() { return board; }

    // Pour éviter la création de plusieurs controleurs
    Controleur(const Controleur& c) = delete;
    Controleur& operator=(const Controleur& c) = delete;

    // Destructeur
    ~Controleur() {
        // pour l'instant on delete, mais il y aura certainement une manip à faire pour gérer les sauvegardes
        board.~Board();
    }
};

#endif // CONTROLEUR_H
