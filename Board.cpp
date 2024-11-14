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

// Associe l'insecte � la case trouv�e
void Board::addInsectToSpot(int x, int y, Insect* insect) {
    for (size_t i = 0; i < nb; ++i) { // Parcourt les spots jusqu'� nb
        if (board_spots[i]->getCoordinates() == std::make_pair(x, y)) {
            board_spots[i]->setInsect(insect); // Associe l'insecte � cette case
            return;
        }
    }
    throw SetException("Coordonn�es introuvables sur le plateau.");
}

void Board::deleteInsectFromSpot(int x, int y) {
    for (size_t i = 0; i < nb; ++i) { // Parcourt les cases jusqu'� nb
        if (board_spots[i]->getCoordinates() == std::make_pair(x, y)) {
            if (board_spots[i]->hasInsect()) {
                // Cette ligne n'a pas lieu d'être ????
                //delete board_spots[i]->getInsect(); // Supprime l'insecte de la m�moire
                board_spots[i]->setInsect(nullptr); // Met le pointeur � nullptr
                return;
            }
            else {
                throw SetException("Aucun insecte � supprimer sur la case.");
            }
        }
    }
    throw SetException("Coordonn�es introuvables sur le plateau.");
}

//  modifier une case sp�cifique par coordonn�es
void Board::modifySpot(int oldX, int oldY, int newX, int newY) {
    for (size_t i = 0; i < nb; i++) {
        if (board_spots[i]->getCoordinates() == std::make_pair(oldX, oldY)) {
            board_spots[i]->setCoordinates(newX, newY);
            return;
        }
    }
    throw SetException("Case non trouv�e pour modification");
}

//  acc�der � une case sp�cifique par coordonn�es
const BoardSpot* Board::getSpot(int x, int y) const {
    for (size_t i = 0; i < nb; i++) {
        if (board_spots[i]->getCoordinates() == std::make_pair(x, y)) {
            return board_spots[i];
        }
    }
    return nullptr;
}


// Affichage du plateau
void Board::print(ostream& f) const {
    f << "Le plateau contient " << nb << " spots." << endl;
    for (size_t i = 0; i < nb; i++) {
        f << "\t";
        board_spots[i]->print(f);
        f << "\n";
    }
    f << endl;
}

void Board::deleteSpot(int x, int y) {
    size_t i = 0;
    while (i < nb && board_spots[i]->getCoordinates() != std::make_pair(x, y)) {
        i++;
    }
    if (i == nb) {
        throw SetException("Le spot avec les coordonn�es fournies n'existe pas.");
    }
    delete board_spots[i];
    board_spots[i] = board_spots[--nb];
}

const BoardSpot& Board::getSpotIndex(size_t index) const {

    if (index >= getNb()) {
        throw SetException("Index hors limites dans getSpotIndex.");
    }
    return *board_spots[index];
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

// Op�rateur d'affectation pour Board
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



//fonction trouver voisins qui renvoie le vecteur compos� de toutes les coordonn�es d'une liste
std::vector<const BoardSpot*> Board::trouverVoisins(int x, int y) const {

        std::vector<const BoardSpot*> voisins;
        //cr�ation de la liste de pair des coordon�es de tout les voisins
        std::pair<int, int> directions[] = {
            {1, 0},   // (x + 1, y)
            {1, 1},   // (x + 1, y + 1)
            {0, 1},   // (x, y + 1)
            {-1, 0},  // (x - 1, y)
            {-1, -1}, // (x - 1, y - 1)
            {0, -1}   // (x, y - 1)
        };

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;


            const BoardSpot* spot = getSpot(newX, newY);
            if (spot) {
                voisins.push_back(spot); //on ajoute les voisins existants au vecteur
            }
        }

        return voisins;} //on retourne le vecteur


    //fonction trouver voisins nulls qui renvoie le vecteur compos� de toutes les coordonn�es des cases qui n'ont pas d'insects affect�s
    std::vector<const BoardSpot*> Board::voisinsNull(int x, int y) const {
    std::vector<const BoardSpot*> voisins = trouverVoisins(x, y); //on r�cup�re les voisins � l'aide de la methode trouver voisins.
    std::vector<const BoardSpot*> voisinsNuls;

    for (size_t i = 0; i < voisins.size(); i++) {

        if (!voisins[i]->hasInsect()) { //on appele la methode cr�e pour savoir si il y a un insect attribu�
            voisinsNuls.push_back(voisins[i]); // on ajoute � VoisinsNuls
        }
    }

    return voisinsNuls; //on retourne le vecteur
}

std::vector<const BoardSpot*> Board::trouverVoisinsInsects(int x, int y) const {
    std::vector<const BoardSpot*> voisins = trouverVoisins(x, y); //on r�cup�re les voisins � l'aide de la methode trouver voisins.
    std::vector<const BoardSpot*> voisinsNuls;

    for (size_t i = 0; i < voisins.size(); i++) {

        if (voisins[i]->hasInsect()) { //on appele la methode cr�e pour savoir si il y a un insect attribu�
            voisinsNuls.push_back(voisins[i]); // on ajoute � VoisinsNuls
        }
    }

    return voisinsNuls; //on retourne le vecteur
}

std::vector<const BoardSpot*> Board::possibleplacer(bool couleur)
{
    std::vector<const BoardSpot*> possibilite;

    for (size_t i= 0; i< this->getNb(); i++ )
    {
        if(getSpotIndex(i).hasInsect())
        {
            if(getSpotIndex(i).getInsect()->getColor()== true )
                {std::pair<int, int> coords = getSpotIndex(i).getCoordinates();
                 std::vector<const BoardSpot*> voisins = voisinsNull(coords.first, coords.second);
                 for (size_t y = 0; y <voisins.size(); y++)
                 {   std::pair<int, int> coords2 = voisins[y]->getCoordinates();
                     std::vector<const BoardSpot*> voisinsdevoisins = trouverVoisins(coords2.first, coords2.second);
                     int couleurok = 0;
                     for (size_t z ; z < voisinsdevoisins.size(); z++)
                     {
                         if(voisinsdevoisins[z]->hasInsect())
                            {
                                if(voisinsdevoisins[z]->getInsect()->getColor()== false )
                                    ++couleurok;
                            }
                        if(couleurok == 0 && !this->est_dans_possibilite(voisinsdevoisins[z], possibilite))
                        {
                            possibilite.push_back(voisinsdevoisins[z]);
                        }
                     }
                 }
                }
        }
    }
    return possibilite;
}



void Board::afficherpossibilite (std::vector <const BoardSpot*> possibilite){
    size_t taille = possibilite.size();
    for (size_t i = 0; i< taille; i++)
        {   std::pair<int, int> coords = possibilite[i]->getCoordinates();
            if (!possibilite[i]->hasInsect())
            {

                std::cout <<"{"<<coords.first<<";"<<coords.second<<"}vide;";
            }else{
                std::cout <<"{"<<coords.first<<";"<<coords.second<<"}"<<possibilite[i]->getInsect()<<"  ;";
            }
        }
    }

bool Board::est_dans_possibilite (const BoardSpot* spot, std::vector <const BoardSpot* > possibilite){

    for (size_t i = 0; i< possibilite.size(); i++)
        {
           if (spot->getCoordinates() == possibilite[i]->getCoordinates())
           {

               return true;
           }

        }
    return false;
    }

