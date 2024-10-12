#include "Board.h"
#include <iostream>

using namespace std;

// Ajout d'un spot sur le plateau
void Board::addSpot(int x, int y) {
    if (nb == nbMax) {
        auto newtab = new BoardSpot * [nbMax + 5];
        for (size_t i = 0; i < nb; i++) {
            newtab[i] = board_spots[i];
        }
        auto old = board_spots;
        board_spots = newtab;
        nbMax += 5;
        delete[] old;
    }
    board_spots[nb++] = new BoardSpot(x, y);
}

//  accéder à une case spécifique par coordonnées
const BoardSpot* Board::getSpot(int x, int y) const {
    for (size_t i = 0; i < nb; i++) {
        if (board_spots[i]->getCoordinates() == std::make_pair(x, y)) {
            return board_spots[i];
        }
    }
    return nullptr;
}

//  modifier une case spécifique par coordonnées
void Board::modifySpot(int oldX, int oldY, int newX, int newY) {
    for (size_t i = 0; i < nb; i++) {
        if (board_spots[i]->getCoordinates() == std::make_pair(oldX, oldY)) {
            board_spots[i]->setCoordinates(newX, newY);
            return;
        }
    }
    throw std::runtime_error("Case non trouvée pour modification");
}

// Affichage du plateau
void Board::print(ostream& f) const {
    f << "Le plateau contient " << nb << " spots." << endl;
    for (size_t i = 0; i < nb; i++) {
        board_spots[i]->print(f);
        f << " ";
    }
    f << endl;
}

void Board::deleteSpot(int x, int y) {
    size_t i = 0;
    while (i < nb && board_spots[i]->getCoordinates() != std::make_pair(x, y)) {
        i++;}
    if (i == nb) {
        throw SetException("Le spot avec les coordonnées fournies n'existe pas.");}
    delete board_spots[i];
    board_spots[i] = board_spots[--nb];  
}

// Constructeur par copie pour Board
Board::Board(const Board& other) {
    nb = other.nb;
    nbMax = other.nbMax;
    board_spots = new BoardSpot * [nbMax];
    for (size_t i = 0; i < nb; i++) {
        board_spots[i] = other.board_spots[i];
    }
}

// Opérateur d'affectation pour Board
Board& Board::operator=(const Board& other) {
    if (this == &other) return *this;

    delete[] board_spots;

    nb = other.nb;
    nbMax = other.nbMax;
    board_spots = new BoardSpot * [nbMax];
    for (size_t i = 0; i < nb; i++) {
        board_spots[i] = other.board_spots[i];
    }

    return *this;
}

// Destructeur pour Board
Board::~Board() {
    for (size_t i = 0; i < nb; i++) {
        delete board_spots[i];
    }
    delete[] board_spots;
}
