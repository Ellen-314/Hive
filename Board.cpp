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
void Board::addInsectToSpot(int x, int y,Insect* insect) {
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

//acceder à une case par coordonnée et modifiable
BoardSpot* Board::getSpotModify(int x, int y) {
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
        // Pour n'afficher que les spots où il y a des insectes
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
    }
    else {
        board_spots = nullptr;
    }
}

// Op�rateur d'affectation pour Board
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Nettoyer les ressources existantes
        if (board_spots) {
            for (size_t i = 0; i < nb; ++i) {
                delete board_spots[i];
            }
            delete[] board_spots;
        }
        // Copier les champs scalaires
        nb = other.nb;
        nbMax = other.nbMax;

        // Copie profonde du tableau board_spots
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
            else{
            }
        }
        return voisins; //on retourne le vecteur
}

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

// trouver les voisins sans insectes sans saut de la piece demandée et les renovies dans un vecteur; (pas fait)
std::vector<const BoardSpot*> Board::trouverVoisinsGlisseur(int x, int y) const{

    std::vector<const BoardSpot*> tousVoisins = trouverVoisins(x, y);

    // afficherpossibilite(tousVoisins);
    std::vector<const BoardSpot*> voisinsPossibles;
    for(auto voisin : trouverVoisins(x,y))
    {
        if(!(voisin->hasInsect())){

        std::pair<int, int> coords = voisin->getCoordinates();

        std::vector <const BoardSpot*> voisinVoisin = trouverVoisins(coords.first, coords.second);

        std::vector <const BoardSpot*> voisinCommun;
        // boucle qui met en commun les cases qui sont voisines avec la case qu'on est en train de parcourir et notre case
        for(auto voisin2 : voisinVoisin)
        {
            if (std::find(tousVoisins.begin(), tousVoisins.end(), voisin2) != tousVoisins.end()){
                voisinCommun.push_back(voisin2);
            }
        }
        if(voisinCommun.size()>= 2){

                // si on a 2 voisins en commun, on voit si les 2 ont un insecte pour l'enlever de la liste des possibilités
                if(!(voisinCommun[0]->hasInsect() && voisinCommun[1]->hasInsect())){
                     voisinsPossibles.push_back(voisin);
                 }
            }
        else{voisinsPossibles.push_back(voisin);}
        }
    }
    return voisinsPossibles;
}

std::vector<const BoardSpot*> Board::possibleplacer(bool couleur)const{

    std::vector<const BoardSpot*> possibilite;

    for (size_t i= 0; i< this->getNb(); i++ )
    {
        if(getSpotIndex(i).hasInsect() && getSpotIndex(i).getInsect()->getColor()== couleur){
                 std::pair<int, int> coords = getSpotIndex(i).getCoordinates();
                 std::vector<const BoardSpot*> voisins = voisinsNull(coords.first, coords.second);

                for (size_t y = 0; y <voisins.size(); y++){
                    const BoardSpot* voisin2 = voisins[y];
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

    return possibilite;
}


// méthode utilisée pour le debogage. Elle permet d'afficher tous les BoardSpot qui sant la liste mis en paramètre
void Board::afficherpossibilite (std::vector <const BoardSpot*> possibilite)const{
    size_t taille = possibilite.size();
     if (taille == 0) {
        std::cout << "Aucune possibilité à afficher.\n"; // Débogage si le vecteur est vide
    }
    else{
        for (size_t i = 0; i< taille; i++)
            {   std::pair<int, int> coords = possibilite[i]->getCoordinates();
                if (!possibilite[i]->hasInsect())
                {
                    std::cout <<"("<<coords.first<<","<<coords.second<<") vide;\n";
                }else{
                    std::cout <<"("<<coords.first<<","<<coords.second<<") "<<possibilite[i]->getInsect()->getType()<<";\n";
                }
            }
    }
}

bool Board::est_dans_possibilite (const BoardSpot* spot, std::vector <const BoardSpot* > possibilite)const{
    if (spot == nullptr){ return false; }
    for (size_t i = 0; i< possibilite.size(); i++)
        {
           if (spot->getCoordinates() == possibilite[i]->getCoordinates())
           {
               return true;
           }
        }
    return false;
}

void Board::addNullSpot(int x, int y){
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
            if (!spot) {
                addSpot(newX, newY); //on ajoute les voisins existants au vecteur
            }
        }
}

// Méthode qui retourne toutes les pièces posées par un joueur
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

bool Board::isConnexe() const {

    // Collecter toutes les cases avec des insectes
    std::vector<const BoardSpot*> insectSpots;
    for (size_t i = 0; i < nb; ++i) {
        if (board_spots[i]->hasInsect()) {
            insectSpots.push_back(board_spots[i]);
        }
    }

    // Si aucune case n'a d'insecte, on considère le plateau comme connexe
    if (insectSpots.empty()) return true;


    std::vector<const BoardSpot*> visited; // Pour stocker les cases visitées
    std::vector<const BoardSpot*> toVisit; // Pile pour les voisins à explorer

    // Commencer par la première case avec un insecte
    toVisit.push_back(insectSpots[0]);

    while (!toVisit.empty()) {
        const BoardSpot* current = toVisit.back();
        toVisit.pop_back();

        // Si non visité, ajouter aux visités
        if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
            visited.push_back(current);

            // Ajouter les voisins avec des insectes à la pile
            std::vector<const BoardSpot*> voisins = trouverVoisins(
                current->getCoordinates().first,
                current->getCoordinates().second
            );
            for (const auto& voisin : voisins) {
                if (voisin->hasInsect() &&
                    std::find(visited.begin(), visited.end(), voisin) == visited.end()) {
                    toVisit.push_back(voisin);
                }
            }
        }
    }

    // Vérifier que toutes les cases avec des insectes ont été visitées
    return visited.size() == insectSpots.size();
}

void Board::moovInsect(int oldX, int oldY, int newX, int newY) {
    if (getSpotModify(oldX, oldY)->getInsectModify()->getType() == "beetle") {
        Beetle* beetle = dynamic_cast<Beetle*>(getSpot(oldX, oldY)->getInsect());
        getSpotModify(oldX, oldY)->setInsect(beetle->getcouvertModify());

        beetle->setInsectUnder(getSpot(newX, newY)->getInsect());
        getSpotModify(newX, newY)->setInsect(beetle);

    } else if (getSpotModify(oldX, oldY)->getInsectModify()->getType() == "mosquito") {
        Mosquito* mosquito = dynamic_cast<Mosquito*>(getSpot(oldX, oldY)->getInsect());
        getSpotModify(oldX, oldY)->setInsect(mosquito->getcouvertModify());

        mosquito->setInsectUnder(getSpot(newX, newY)->getInsect());
        getSpotModify(newX, newY)->setInsect(mosquito);

    } else {
        getSpotModify(newX, newY)->setInsect(getSpot(oldX, oldY)->getInsect());
        deleteInsectFromSpot(oldX, oldY);
    }
    return;
}

void Board::deleteNullSpot(int oldX, int oldY){
        std::vector<const BoardSpot*> voisins= voisinsNull(oldX,oldY);
        for (auto& voisin:voisins){
            std::pair<int,int> coord = voisin-> getCoordinates();
            if (trouverVoisinsInsects(coord.first, coord.second).size()<1){
                deleteSpot(coord.first, coord.second);}
        }}



bool compBSco(const BoardSpot* a, const BoardSpot* b){

    return *a < *b;
}

bool operator<(const BoardSpot& a, const BoardSpot& b){
    int xa = a.getCoordinates().first;
    int ya = a.getCoordinates().second;
    int xb = b.getCoordinates().first;
    int yb = b.getCoordinates().second;
    if (2 * ya - xa < 2 * yb - xb) return true;
    else if (2 * ya - xa > 2 * yb - xb) return false;
    else if (xa > xb) return true;
    else return false;
}
