#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

// BY EVAN

// Codes d’échappement ANSI.
// Définition de plusieurs caractères de couleur comme des macros
// qui seviront de caractères d'échappement pour changer de couleur.
//
// Exemple : pour avoir des lettres noires sur un fond blanc on utilisera \e[30;47m
//
// Lien pour les codes : https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define NB "\e[0;40m"          // terminal normal
#define RED "\e[0;31m"      // rouge
#define GRN "\e[0;32m"      // vert
#define CYAN "\e[0;36m"     // bleu clair
#define TITRE "\e[30;47m"   // noir fond blanc
// le \e est un caractère d’échappement ASCII. un caractère de parenthèse suivis de paramètres


// Exception pour gestion des erreurs dans la classe Board
class SetException : public std::exception {
private:
    std::string message;

public:
    SetException(const std::string& msg) : message(msg) {}
};


// Classe pour représenter une case sur le plateau
class BoardSpot {
private:
    std::pair<int, int> coordinates; // Paire d'entiers pour les coordonnées (x, y)

public:
    // Constructeur
    BoardSpot(int x, int y) : coordinates(x, y) {}

    std::pair<int, int> getCoordinates() const { return coordinates; }

    void setCoordinates(int x, int y) { coordinates = std::make_pair(x, y); }

    void print(std::ostream& f) const {
        f << "(" << coordinates.first << ", " << coordinates.second << ")";
    }
};

// Classe pour gérer le plateau de jeu
class Board {
private:
    BoardSpot** board_spots = nullptr;
    size_t nb = 0;
    size_t nbMax = 0;

public:
    Board() = default;

    //  ajouter une case au plateau
    void addSpot(int x, int y);

    // accéder à une case spécifique par coordonnées
    const BoardSpot* getSpot(int x, int y) const;

    //  modifier une case spécifique par coordonnées
    void modifySpot(int oldX, int oldY, int newX, int newY);

    // afficher toutes les cases du plateau
    void print(std::ostream& f) const;

    // Suppression d'un spot du plateau
    void deleteSpot(int x, int y);

    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);

    void terminal() const;
};

#endif
