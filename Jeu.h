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

    //liste contenant tout les types d'insects et leur nombre max
    std::vector<std::pair< std::function<Insect*()>, unsigned int>> insectTypes;
    std::stack<Board> historyStack;
    static unsigned int compteurDeToursBlanc;
    static unsigned int compteurDeToursNoir;
    // M�thode pour afficher le menu principal avec les diff�rentes actions disponibles
    void afficherMenu() const;

    // M�thode pour obtenir de la part l'utilisateur des coordonn�es de la case o� une action doit �tre effectu�e
    std::pair<int, int> demanderCoordonnees() const;
    friend Controleur;


public:
    // Accesseurs pour bot
    int getHasbot() const { return hasbot; }
    void setHasbot(int value) { hasbot = value; }

    // M�thode principale pour lancer le jeu et g�rer les interactions utilisateur durant la partie
    void demarrerPartie();

    // M�thode pour ajouter une case au plateau
    void ajouterCase();

    // M�thode pour ajouter un insecte � une case
    void ajouterInsecte();

    // M�thode pour d�placer un insecte, diff�rent de moov dans Insect qui testera les diff�rentes possibilit�s de d�placement
    void deplacerInsecte();

    // M�thode pour supprimer une case du plateau
    void supprimerCase();

    // M�thode pour annuler un coup
    void annulerCoup();

    //M�thode pour enregistrer le plateau
    void enregistrerBoard();

    //M�thode pour save une partie
    void saveGame(std::stack<Board> boardStack);

    //M�thode pour reload une partie
    std::stack<Board> reloadGame();

    //M�thode pour free les insects
    void freeListeInsect(std::vector<Insect*>& liste_i);

    //M�thode pour cr�er les listes avec tous les insects
    std::vector<Insect*> createInsectsB();
    std::vector<Insect*> createInsectsN();

    const std::vector<Insect*> getInsectBlanc()const{return insectsBlanc;}
    std::vector<Insect*> getInsectBlancMod(){return insectsBlanc;}
    const std::vector<Insect*> getInsectNoir()const{return insectsNoir;}
    std::vector<Insect*> getInsectNoirMod(){return insectsNoir;}

    //M�thode pour ajouter les types d'insects � la liste de types.
    void addType( std::function<Insect*()> cree, int maximum){insectTypes.push_back(std::make_pair(cree, maximum));}
    // m�thode qui cree tout les insects sur le plateau
    void createInsects();
    const std::vector<std::pair< std::function<Insect*()>, unsigned int>> getInsectTypes()const{return insectTypes;}

    //M�thode qui free la liste de tous les instects restants et refait la liste du d�but
    //cherche si l'insecte est sur le board, si oui l'enl�ve de la liste
    void majListeInsect(Board& board);

    //M�thode qui reset le compteur
    void resetInsectCount();

    //Methodes li�es
    const int getnbRetoursEnArriere() const {return nbRetoursEnArriere;}
    void setnbRetoursEnArriere(int n) {nbRetoursEnArriere=n;}
    static unsigned int getCompteurDeToursBlanc(){return compteurDeToursBlanc;}
    static unsigned int getCompteurDeToursNoir(){return compteurDeToursNoir;}
    static void ajouterCompteurDeToursBlanc(){compteurDeToursBlanc++;}
    static void ajouterCompteurDeToursNoir(){compteurDeToursNoir++;}
    static void enleverCompteurDeToursBlanc(){compteurDeToursBlanc--;}
    static void enleverCompteurDeToursNoir(){compteurDeToursNoir--;}
    //fonction qui permet de mettre � jour le tour du joueur;
    void incCompteur(bool color);
    //fonction qui permet d'annuler le tour du joueur;
    void decCompteur();

    void printInsectsNoir(std::ostream& f);
    void printInsectsBlanc(std::ostream& f);

    //methode qui renvoit true si la reine de la couleur color est entouree
    bool isQueenSurrounded(bool color) const;

    void setNbRetoursEnArriere(int n){
        if(n<0){
            std::cout << "Le nombre maximal de retours en arri�re doit �tre positif";
            while(n<0){
                std::cout << "Nombre maximal de retours en arri�re : ";
                std::cin >> n;
            }
        }
        nbRetoursEnArriere = n;
    }

    // Constructeur sans argument
    Jeu()=default;

    const Board& getPlateau() const { return board; }
    Board& getPlateau() { return board; }

    //======================== METHODES DU BOT ==============================//
    void botIsPlayingToWin();
    void botMoveInsect();
    //======================================================================//
    
    // Destructeur
    ~Jeu()=default;
};

int demanderChoix ();
#endif // Jeu_H

