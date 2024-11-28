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
    // Deep copy of the board_spots array
    if (other.board_spots) {
        board_spots = new BoardSpot*[nbMax];
        for (size_t i = 0; i < nb; ++i) {
            board_spots[i] = new BoardSpot(*other.board_spots[i]); // Deep copy of each spot
        }
    } else {
        board_spots = nullptr;
    }
}

// Op�rateur d'affectation pour Board
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Clean up existing resources
        if (board_spots) {
            for (size_t i = 0; i < nb; ++i) {
                delete board_spots[i];
            }
            delete[] board_spots;
        }

        // Copy scalar fields
        nb = other.nb;
        nbMax = other.nbMax;

        // Deep copy of the board_spots array
        if (other.board_spots) {
            board_spots = new BoardSpot*[nbMax];
            for (size_t i = 0; i < nb; ++i) {
                board_spots[i] = new BoardSpot(*other.board_spots[i]);
            }
        } else {
            board_spots = nullptr;
        }
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
         std::cout<<"je suis dans touverVoisins\n";
         std::cout<<"x:"<<x<<"y:"<<y;

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

            std::cout<<"nexx:"<<newX<<"newy:"<<newY <<"\n";
            const BoardSpot* spot = getSpot(newX, newY);
            if (spot) {
                std::cout<<"j'ajoute à voisins\n";
                voisins.push_back(spot); //on ajoute les voisins existants au vecteur
            }
            else{ std::cout<<"je n'ajoute PAS à voisins\n";}
        }
        afficherpossibilite(voisins);
        return voisins;} //on retourne le vecteur


    //fonction trouver voisins nulls qui renvoie le vecteur compos� de toutes les coordonn�es des cases qui n'ont pas d'insects affect�s
    std::vector<const BoardSpot*> Board::voisinsNull(int x, int y) const {
    std::vector<const BoardSpot*> voisins = trouverVoisins(x, y); //on r�cup�re les voisins � l'aide de la methode trouver voisins.
    std::vector<const BoardSpot*> voisinsNuls;
    std::cout<<"je suis dans touverVoisinsNuls\n";
    afficherpossibilite(voisins);
    for (size_t i = 0; i < voisins.size(); i++) {

        if (!voisins[i]->hasInsect()) { //on appele la methode cr�e pour savoir si il y a un insect attribu�
            std::cout << "Voisin sans insecte trouvé: ";
            std::pair<int, int> coords = voisins[i]->getCoordinates();
            std::cout << "{" << coords.first << ";" << coords.second << "}\n";
            voisinsNuls.push_back(voisins[i]); // on ajoute � VoisinsNuls
        }
    }
    afficherpossibilite(voisinsNuls);
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

std::vector<const BoardSpot*> Board::possibleplacer(bool couleur)const
{

    std::vector<const BoardSpot*> possibilite;


    for (size_t i= 0; i< this->getNb(); i++ )
    {
        if(getSpotIndex(i).hasInsect() && getSpotIndex(i).getInsect()->getColor()== couleur)


                {std::pair<int, int> coords = getSpotIndex(i).getCoordinates();
                 std::vector<const BoardSpot*> voisins = voisinsNull(coords.first, coords.second);

                 for (size_t y = 0; y <voisins.size(); y++)
                 {   const BoardSpot* voisin2 = voisins[y];
                    if (!voisin2->hasInsect()){
                         std::pair<int, int> coords2 = voisin2->getCoordinates();
                         std::vector<const BoardSpot*> voisinsdevoisins = trouverVoisins(coords2.first, coords2.second);
                        bool enContactAdverse= false;


                            for (size_t z = 0; z<voisinsdevoisins.size(); z++)
                            {
                                if( voisinsdevoisins[z]->hasInsect() && voisinsdevoisins[z]->getInsect()->getColor()== !couleur)
                                    {enContactAdverse= true;
                                break;}
                            }
                             if (!enContactAdverse &&
                        !this->est_dans_possibilite(voisin2, possibilite)) {
                        possibilite.push_back(voisin2);
                        }
                    }
                     }
                 }

        }


    afficherpossibilite(possibilite);
    return possibilite;
}



void Board::afficherpossibilite (std::vector <const BoardSpot*> possibilite)const{
    size_t taille = possibilite.size();
     if (taille == 0) {
        std::cout << "Aucune possibilité à afficher.\n"; // Débogage si le vecteur est vide
    }else{
    for (size_t i = 0; i< taille; i++)
        {   std::pair<int, int> coords = possibilite[i]->getCoordinates();
            if (!possibilite[i]->hasInsect())
            {

                std::cout <<"{"<<coords.first<<";"<<coords.second<<"}vide;";
            }else{
                std::cout <<"{"<<coords.first<<";"<<coords.second<<"}"<<possibilite[i]->getInsect()-> getType()<<"  ;";
            }
        }
    }}

bool Board::est_dans_possibilite (const BoardSpot* spot, std::vector <const BoardSpot* > possibilite)const{

    for (size_t i = 0; i< possibilite.size(); i++)
        {
           if (spot->getCoordinates() == possibilite[i]->getCoordinates())
           {

               return true;
           }

        }
    return false;
    }
void Board::addNullSpot(int x, int y)
{ std::pair<int, int> directions[] = {
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
            if (!spot) {
                addSpot(newX, newY); //on ajoute les voisins existants au vecteur
            }

}}

std::vector<const BoardSpot*> Board::piecejoueur(bool couleur) const{
    std::vector<const BoardSpot*> piece;


    for (size_t i= 0; i< this->getNb(); i++ ){
        if(getSpotIndex(i).hasInsect() && getSpotIndex(i).getInsect()->getColor()  == couleur)
        { const BoardSpot* piece2 = &getSpotIndex(i);
            piece.push_back(piece2);
        }
    }
    return piece;
}
