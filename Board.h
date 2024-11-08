#ifndef BOARD_H
#define BOARD_H

#include "Insect.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>




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

    void setCoordinates(int x, int y) { coordinates = std::make_pair(x, y); }
    void setInsect(Insect* insect) { insect_pose = insect; }

    // V�rifier si un insecte est pr�sent sur la case
    bool hasInsect() const { return insect_pose != nullptr; }

    void print(std::ostream& f) const {
        f << "Coordonn�es: (" << coordinates.first << ", " << coordinates.second << ")";
        if (insect_pose) {
            f << " avec un insecte.";
        }
        else {
            f << " sans insecte.";
        }
    }

};

// Classe pour g�rer le plateau de jeu
class Board {
private:
    BoardSpot** board_spots = nullptr;
    size_t nb = 0;
    size_t nbMax = 0;

public:
    Board() = default;

    //  ajouter une case au plateau
    void addSpot(int x, int y);

    // acc�der � une case sp�cifique par coordonn�es
    const BoardSpot* getSpot(int x, int y) const;

    //  modifier une case sp�cifique par coordonn�es
    void modifySpot(int oldX, int oldY, int newX, int newY);

    void addInsectToSpot(int x, int y, Insect* insect);
    void deleteInsectFromSpot(int x, int y);


    // afficher toutes les cases du plateau
    void print(std::ostream& f) const;

    // Suppression d'un spot du plateau
    void deleteSpot(int x, int y);

    //trouve les voisins de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> trouverVoisins(int x, int y) const;
    //trouve les voisins sans insects de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> voisinsNull(int x, int y) const;
    //trouve les voisins avec insects de la pi�ce demand�e et les renvoies dans un vecteur;
    std::vector<const BoardSpot*> trouverVoisinsInsects(int x, int y) const;

    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);

    class BoardIterator {
    public:
        BoardIterator & operator++() { current++;  return *this; }
        BoardSpot& operator*() const { return **current; }
        bool operator!=(BoardIterator it) const { return current != it.current; }
    private:
        BoardIterator(BoardSpot** s) :current(s) {}
        friend class Board;
        BoardSpot** current = nullptr;
    };
    BoardIterator begin() const { return BoardIterator(board_spots); }
    BoardIterator end() const { return BoardIterator(board_spots+nb); }

    /*
    Exemple d'utilisation de l'itérateur

    for(auto it=board.begin();
         it!=board.end();
         ++it){
        (*it).print(std::cout);
        std::cout << "\n";
    }
    */

};

#endif
