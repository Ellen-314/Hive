#ifndef BOARD_H
#define BOARD_H

#include "Insect.h"
#include "ClassesInsects/ant.h"
#include "ClassesInsects/queenbee.h"
#include "ClassesInsects/spider.h"
#include "ClassesInsects/grasshopper.h"
#include "ClassesInsects/beetle.h"
#include "ClassesInsects/ladybug.h"
#include "ClassesInsects/mosquito.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm> // pour la fonction std::find

// Codes d’échappement ANSI.
// Définition de plusieurs caractères de couleur comme des macros
// qui seviront de caractères d'échappement pour changer de couleur.
//
// Exemple : pour avoir des lettres noires sur un fond blanc on utilisera \e[30;47m
//
// Lien pour les codes : https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// le \e est un caractère d’échappement ASCII. un caractère de parenthèse suivis de paramètres
#define WHITE "\e[30;47m"   // noir fond blanc
#define BLACK "\e[37;40m"   // blanc fond noir
#define RED "\e[31;40m"      // rouge
#define CYAN "\e[96;40m"     // bleu clair


// Exception pour gestion des erreurs dans la classe Board
class SetException : public std::exception {
private:
    std::string message;

public:
    SetException(const std::string& msg) : message(msg) {}
    std::string getMessage() const { return message; }
};


// Classe pour repr�senter une case sur le plateau
class BoardSpot {
private:
    std::pair<int, int> coordinates; // Paire d'entiers pour les coordonn�es (x, y)
    Insect* insect_pose;

public:
    // Constructeur
    BoardSpot(int x, int y) : coordinates(x, y), insect_pose(nullptr){}

    std::pair<int, int> getCoordinates() const { return coordinates; }
    Insect* getInsect() const { return insect_pose; }
    Insect* getInsectModify(){return insect_pose;}


    void setCoordinates(int x, int y) { coordinates = std::make_pair(x, y); }
    void setInsect( Insect* insect) { insect_pose = insect; }


    // V�rifier si un insecte est pr�sent sur la case
    bool hasInsect() const { return insect_pose != nullptr; }

    void print(std::ostream& f) const {
        f << "(" << coordinates.first << ", " << coordinates.second << ") ";
        if (insect_pose) {
            f << insect_pose->getType()<<" ";
            if (insect_pose->getColor()==0){ f << "noir."; }
            if (insect_pose->getColor()==1){ f << WHITE << "blanc" << BLACK <<"."; }
        }
        else { f << " sans insecte."; }
    }
};

// trier les cases dans l'ordre d'affichage sur le terminal
bool compBSco(const BoardSpot* a, const BoardSpot* b);

bool operator<(const BoardSpot& a, const BoardSpot& b);

// Classe pour g�rer le plateau de jeu
class Board {
private:
    BoardSpot** board_spots = nullptr;
    size_t nb = 0;
    size_t nbMax = 0;

public:
    Board() = default;
    // acceder à la taille max
    size_t getNb()const{return nb;}
    // ajouter une case au plateau
    void addSpot(int x, int y);

    // acc�der � une case sp�cifique par coordonn�es
    const BoardSpot* getSpot(int x, int y) const;

     BoardSpot* getSpotModify(int x, int y) ;
    //  modifier une case sp�cifique par coordonn�es
    void modifySpot(int oldX, int oldY, int newX, int newY);

    void addInsectToSpot(int x, int y, Insect* insect);
    void deleteInsectFromSpot(int x, int y);


    // afficher toutes les cases du plateau
    void print(std::ostream& f) const;

    // Suppression d'un spot du plateau
    void deleteSpot(int x, int y);

    // permet d'acceder au boardspot par son index
    const BoardSpot& getSpotIndex(size_t index) const ;
    //trouve les voisins de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> trouverVoisins(int x, int y) const;
    // trouve les voisins sans insects de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> voisinsNull(int x, int y) const;
    // trouve les voisins avec insects de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> trouverVoisinsInsects(int x, int y) const;
    std::vector<const BoardSpot*>possibleplacer(bool couleur)const;

     // trouver les voisins sans insectes sans saut de la piece demandée et les renovies dans un vecteur;
    std::vector<const BoardSpot*> trouverVoisinsGlisseur(int x, int y) const;

    // affiche chaque element d'une liste de possibilités
    void afficherpossibilite (std::vector <const BoardSpot*> possibilite)const;
    //revoie true si le spot est dans les possibilités et false sinon
    bool est_dans_possibilite (const BoardSpot* spot, std::vector <const BoardSpot* > possibilite)const;
    //ajouter les cases null autour d'une pièce
    void addNullSpot(int x, int y);
    //renvoyer toutes les pièces posées par un joueur
    std::vector<const BoardSpot*> piecejoueur(bool couleur) const;
    //verifie si le tableau est toujours en un morceau;
    bool isConnexe() const;

    //permet de deplacer un insect d'une case à une autre
    void moovInsect (int oldX, int oldY, int newX, int newY);

    //la fonction permet de supprimer les voisins nuls qui ne sont plus en contact avec des insects
    void deleteNullSpot(int oldX, int oldY);

    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);


};

#endif
