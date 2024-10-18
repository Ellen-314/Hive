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

void Board::terminal() const
{
    /*
    printf(RED "BY EVAN - Note" NB
               ": Mine de rien ca va quand meme etre galere, je pense que pour faciliter le placement des pieces dans le termminal, il vaudra mieux qu'elles aient toutes des coordonnees, comme ca on print d'abord celles qui sont le plus en haut etc.\n");
    cout << TITRE "eho\n" NB "yo\n" RED "ca dit quoi\n" GRN "MAIS NAN\n" CYAN "chokbar\n" NB;
    cout << NB "\n-----------\n\n" TITRE "VERSION GRAND (1 piece fait 10 caracteres de large et 5 lignes)" NB "\n";
    */
    cout << "ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvxyz\n";
    cout << "  ______          ______\n";
    cout << " /      \\        /      \\\n";
    cout << "/   " CYAN "S1" NB "   \\______/   A2   \\\n";
    cout << "\\        /      \\        /\n";
    cout << " \\______/   QU   \\" CYAN "______" NB "/\n";
    cout << "        \\        " CYAN "/      \\" NB "\n";
    cout << "         \\______" CYAN "/   qu   \\" NB "\n";
    cout << "                " CYAN "\\   1    /" NB "\n";
    cout << "                 " CYAN "\\______/" NB "\n";
    cout<<"\n-------------------\n";


    /*

    cout << TITRE "eho\n" NB "yo\n" RED "ca dit quoi\n" GRN "MAIS NAN\n" CYAN "chokbar\n" NB;
    cout << NB "\n-----------\n\n" TITRE "VERSION PETIT (1 piece fait 6 caracteres de large et 3 lignes)" NB "\n";
    cout << " ____      ____\n";
    cout << "/ " CYAN "S1" NB " \\____/ A2 \\\n";
    cout << "\\____/ QU \\" CYAN "____" NB "/\n";
    cout << "     \\____" CYAN "/ qu \\" NB "\n";
    cout << "          " CYAN "\\_1__/" NB "\n";

    */

    // Initialisation du x le plus petit, càd le x du spot le plus à gauche
    int min_all_x = board_spots[0]->getCoordinates().first;
    // Initialisation du x le plus grand, càd le x du spot le plus à droite
    int max_all_x = board_spots[0]->getCoordinates().first;

    int northest_x; int northest_y; size_t index_northest_slot;

    // Création du tableau de spots trié pour pouvoir les afficher dans l'ordre
    BoardSpot** board_spots_co_croissantes = new BoardSpot * [nbMax];
    for (size_t i = 0; i < nb; i++) {
        board_spots_co_croissantes[i] = board_spots[i];
        min_all_x = min(board_spots[i]->getCoordinates().first,min_all_x);
        max_all_x = max(board_spots[i]->getCoordinates().first,max_all_x);
    }

    // Tri de complexité n**2 : je sais plus le nom mais c'est pas un bon tri
    for (size_t i = 0; i < nb-1; i++) {
        northest_x = board_spots_co_croissantes[i]->getCoordinates().first;
        northest_y= board_spots_co_croissantes[i]->getCoordinates().second;
        index_northest_slot = i;
        for (size_t j = i+1; j <nb; j++){
            if(2*(board_spots_co_croissantes[j]->getCoordinates().second)-(board_spots_co_croissantes[j]->getCoordinates().first) >= 2*northest_y-northest_x){
                if((2*(board_spots_co_croissantes[j]->getCoordinates().second)-(board_spots_co_croissantes[j]->getCoordinates().first) > 2*northest_y-northest_x) != (board_spots_co_croissantes[j]->getCoordinates().first<northest_x)){ // != ici est équivalent au xor logique
                    northest_x = board_spots_co_croissantes[j]->getCoordinates().first;
                    northest_y = board_spots_co_croissantes[j]->getCoordinates().second;
                    index_northest_slot = j;
                    }
            }
        }
        if (i!=index_northest_slot){
            BoardSpot* temp = board_spots_co_croissantes[index_northest_slot];
            board_spots_co_croissantes[index_northest_slot] = board_spots_co_croissantes[i];
            board_spots_co_croissantes[i] = temp;
        }
    }
    cout<<"\n-------------------\n";
    cout << "Le plateau contient " << nb << " spots." << endl;
    for (size_t i = 0; i < nb; i++) {
        board_spots_co_croissantes[i]->print(cout);
        cout << " ";
    }
    cout<<"\n-------------------\n";

    int priority;
    int x=board_spots_co_croissantes[0]->getCoordinates().first;
    int y=board_spots_co_croissantes[0]->getCoordinates().second;
    int priority_max = 2*y-x; // La première priorité sera forcément la plus grande
    int k;
    int board_width = max_all_x-min_all_x+1; // nombre de colonnes
    //cout<< RED << board_width << NB << "\n";
    BoardSpot** pieces_above = new BoardSpot*[board_width];
    BoardSpot** pieces_on_line = new BoardSpot*[board_width];
    BoardSpot** pieces_bellow = new BoardSpot*[board_width];
    for(size_t i= 0; i<board_width;i++){pieces_above[i]=nullptr;}
    for(size_t i= 0; i<board_width;i++){pieces_on_line[i]=nullptr;}
    for (size_t i = 0 ; i < nb;){
        priority = 2*y-x;


        // Partie plate d'une pièce : "______"
        for(int j = 0; j<board_width; j++){
            if (x==j+min_all_x){pieces_bellow[j] = board_spots_co_croissantes[i];i++;} // si dans le parcours en largeur du plateau, on tombe sur une pièce
            else{pieces_bellow[j] = nullptr;}


            if (((j-min_all_x%2)%2 == min_all_x%2) == (priority%2 == priority_max%2)){
                if(pieces_above[j]!=nullptr || (j!=0 && pieces_on_line[j-1])){cout << " \\";}
                else{cout<<"  ";}
                if(pieces_bellow[j]!=nullptr || pieces_above[j]!=nullptr){cout << "______";}
                else{cout << "      ";}
                if(pieces_above[j]!=nullptr || (j!=board_width-1 && pieces_on_line[j+1])){cout << "/ ";}
                else{cout<<"  ";}
            }
            else{
                if(j==0){
                    if(pieces_on_line[j]!=nullptr){cout << "/ ";}
                    else{cout << "  ";}
                }
                if (pieces_on_line[j]!=nullptr){
                        cout << "  Q0  "; // nom de la pièce en pieces_on_line[j]
                        if(j==board_width-1){cout << " \\";}
                }
                else{cout << "      ";}
            }

            if (i<nb){
                x=board_spots_co_croissantes[i]->getCoordinates().first;
                y=board_spots_co_croissantes[i]->getCoordinates().second;
            }
            if(priority!=2*y-x){
                x=2*y-priority_max+1; // pour ne pas gêner le repérage des pièces sur la ligne suivante
            }
        }
        if (i<nb){
            x=board_spots_co_croissantes[i]->getCoordinates().first;
            y=board_spots_co_croissantes[i]->getCoordinates().second;
        }
        cout << "\n";


        // Deuxième partie d'une pièce : "/      \"
        for(int j = 0; j<board_width; j++){
            if (((j-min_all_x%2)%2 == min_all_x%2) == (priority%2 == priority_max%2)){
                if(j==0 && pieces_bellow[j]!=nullptr){cout << " /";}
                cout << "      ";
                if(j==board_width-1 && pieces_bellow[j]!=nullptr){cout << "\\ ";}
            }
            else{
                if(pieces_on_line!=nullptr || (j!=0 && pieces_bellow[j-1]!=nullptr)){cout << "\\";}
                else{cout << " ";}
                cout << "        ";
                if(pieces_on_line!=nullptr || (j!=board_width-1 && pieces_bellow[j+1]!=nullptr)){cout << "/";}
                else{cout << " ";}
            }
         }
         cout << "\n";



        for(size_t m= 0; m<board_width;m++){
            pieces_above[m]=pieces_on_line[m];
            pieces_on_line[m] = pieces_bellow[m];
            pieces_bellow[m]=nullptr;
        }


    }



}
