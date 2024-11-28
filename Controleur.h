#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <stack>
#include <iostream>
#include <stack>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Board.h"
#include "Insect.h"


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
    int nbRetoursEnArriere;
    Board board;
    // Vecteurs des insectes restant a poser
    std::vector<Insect*> insectsBlanc;
    std::vector<Insect*> insectsNoir;
    std::stack<Board> historyStack;
    static unsigned int compteurDeToursBlanc;
    static unsigned int compteurDeToursNoir;
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

    //Méthode pour enregistrer le plateau
    void enregistrerBoard();

    //Méthode pour save une partie
    void saveGame(std::stack<Board> boardStack);

    //Méthode pour reload une partie
    std::stack<Board> reloadGame();

    //Methodes liées
    static unsigned int getCompteurDeToursBlanc(){return compteurDeToursBlanc;}
    static unsigned int getCompteurDeToursNoir(){return compteurDeToursNoir;}
    static void ajouterCompteurDeToursBlanc(){compteurDeToursBlanc++;}
    static void ajouterCompteurDeToursNoir(){compteurDeToursNoir++;}
    static void enleverCompteurDeToursBlanc(){compteurDeToursBlanc--;}
    static void enleverCompteurDeToursNoir(){compteurDeToursNoir--;}
    //fonction qui permet de mettre à jour le tour du joueur;
    void incCompteur(bool color);
    //fonction qui permet d'annuler le tour du joueur;
    void decCompteur();

    void printInsectsNoir(std::ostream& f);
    void printInsectsBlanc(std::ostream& f);

    //methode qui renvoit true si la reine de la couleur color est entouree
    bool isQueenSurrounded(bool color) const;

    // Constructeur
    Controleur();

    const Board& getPlateau() const { return board; }
    Board& getPlateau() { return board; }

    // Pour éviter la création de plusieurs controleurs
    Controleur(const Controleur& c) = delete;
    Controleur& operator=(const Controleur& c) = delete;

    // Destructeur
    ~Controleur()=default;
};

#endif // CONTROLEUR_H
