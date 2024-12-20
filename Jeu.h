#ifndef Jeu_H
#define Jeu_H
#include <stack>
#include <iostream>
#include <stack>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "Board.h"
#include "Insect.h"


class Controleur;

// Exception pour gestion des erreurs dans la classe Jeu
class JeuException : public std::exception {
private:
    std::string message;

public:
    JeuException(const std::string& msg) : message(msg) {}
    std::string getMessage() const { return message; }
};

class Jeu {
private:
    int nbRetoursEnArriere=0;
    int hasbot=0;
    Board board;
    // Vecteurs des insectes restant a poser
    std::vector<Insect*> insectsBlanc;
    std::vector<Insect*> insectsNoir;

    std::string joueurblanc;
    std::string joueurnoir;

    //liste contenant tout les types d'insects et leur nombre max
    std::vector<std::pair< std::function<Insect*()>, unsigned int>> insectTypes;
    std::stack<Board> historyStack;
    static unsigned int compteurDeToursBlanc;
    static unsigned int compteurDeToursNoir;
    // Méthode pour afficher le menu principal avec les différentes actions disponibles
    void afficherMenu() const;

    // Méthode pour obtenir de la part l'utilisateur des coordonnées de la case où une action doit être effectuée
    std::pair<int, int> demanderCoordonnees() const;
    friend Controleur;

public:
    // Accesseurs pour bot
    int getHasbot() const { return hasbot; }
    void setHasbot(int value) { hasbot = value; }

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

    //Méthode pour free les insects
    void freeListeInsect(std::vector<Insect*>& liste_i);

    //Méthode pour créer les listes avec tous les insects
    std::vector<Insect*> createInsectsB();
    std::vector<Insect*> createInsectsN();

    // Accesseurs et setters pour les noms de joueurs
    std::string& getJoueurBlanc(){ return joueurblanc; }
    const std::string& getJoueurBlanc() const { return joueurblanc; }
    void setJoueurBlanc(const std::string& nom){ joueurblanc = nom; }
    std::string& getJoueurNoir(){ return joueurnoir; }
    const std::string& getJoueurNoir() const { return joueurnoir; }
    void setJoueurNoir(const std::string& nom){ joueurnoir = nom; }

    const std::vector<Insect*> getInsectBlanc()const{return insectsBlanc;}
    std::vector<Insect*> getInsectBlancMod(){return insectsBlanc;}
    const std::vector<Insect*> getInsectNoir()const{return insectsNoir;}
    std::vector<Insect*> getInsectNoirMod(){return insectsNoir;}

    //Méthode pour ajouter les types d'insects à la liste de types.
    void addType( std::function<Insect*()> cree, int maximum){insectTypes.push_back(std::make_pair(cree, maximum));}
    // méthode qui cree tout les insects sur le plateau
    void createInsects();
    const std::vector<std::pair< std::function<Insect*()>, unsigned int>> getInsectTypes()const{return insectTypes;}

    //Méthode qui free la liste de tous les instects restants et refait la liste du début
    //cherche si l'insecte est sur le board, si oui l'enlève de la liste
    void majListeInsect(Board& board);

    //Méthode qui reset le compteur
    void resetInsectCount();

    //Methodes liées
    const int getnbRetoursEnArriere() const {return nbRetoursEnArriere;}
    void setnbRetoursEnArriere(int n) {nbRetoursEnArriere=n;}
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

    void setNbRetoursEnArriere(int n){
        if(n<0){
            std::cout << "Le nombre maximal de retours en arrière doit être positif";
            while(n<0){
                std::cout << "Nombre maximal de retours en arrière : ";
                std::cin >> n;
            }
        }
        nbRetoursEnArriere = n;
    }

    void afficherPartie(std::vector<const BoardSpot*>* ptpossibilite = nullptr);

    // Constructeur sans argument
    Jeu()=default;

    const Board& getPlateau() const { return board; }
    Board& getPlateau() { return board; }

    //======================== METHODES DU BOT ==============================//
    void botIsPlayingToWin();
    void botMoveInsect();
    //======================================================================//

    // Pour pouvoir incrémenter le compteur d'insecte en fonction de son type et de sa couleur
    std::unordered_map<std::string, std::function<void(int)>> insectCountUpdate = {
        {"queenbee", [](int color) { color == 1 ? QueenBee::ajouterBlanc() : QueenBee::ajouterNoir(); }},
        {"ant", [](int color) { color == 1 ? Ant::ajouterBlanc() : Ant::ajouterNoir(); }},
        {"spider", [](int color) { color == 1 ? Spider::ajouterBlanc() : Spider::ajouterNoir(); }},
        {"grasshopper", [](int color) { color == 1 ? Grasshopper::ajouterBlanc() : Grasshopper::ajouterNoir(); }},
        {"beetle", [](int color) { color == 1 ? Beetle::ajouterBlanc() : Beetle::ajouterNoir(); }},
        {"ladybug", [](int color) { color == 1 ? Ladybug::ajouterBlanc() : Ladybug::ajouterNoir(); }},
        {"mosquito", [](int color) { color == 1 ? Mosquito::ajouterBlanc() : Mosquito::ajouterNoir(); }}
    };

    // Destructeur
    ~Jeu()=default;
};

int demanderChoix ();
#endif // Jeu_H
