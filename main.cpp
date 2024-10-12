#include "Board.h"

using namespace std;

int main() {
    Board board;

    // Ajouter des cases
    board.addSpot(1, 2);
    board.addSpot(-2, 3);
    board.addSpot(4, -5);

    // Afficher le plateau
    board.print(cout);

    // Modifier une case par ses coordonn�es
    try {
        board.modifySpot(1, 2, 10, 20); 
        cout << "Case modifi�e avec succ�s." << endl;
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    // Afficher le plateau apr�s modification
    board.print(cout);

    return 0;
}