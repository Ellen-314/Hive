#include "Board.h"
#include "terminal.h"

using namespace std;

int main() {
    Board board;

    // Ajouter des cases
    board.addSpot(0, 0);
    board.addSpot(2, 1);
    board.addSpot(1, 0);
    board.addSpot(2, 0);

    // Afficher le plateau
    board.print(cout);

    cout<<"\n-------------------\n";
    /*
    // Modifier une case par ses coordonnées
    try {
        board.modifySpot(1, 2, 10, 20);
        cout << "Case modifiée avec succès." << endl;
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    */
    // Afficher le plateau après modification
    board.print(cout);

    cout<<"\n-------------------\n";

    board.terminal();

    cout<<"\n-------------------\n";

    return 0;
}
