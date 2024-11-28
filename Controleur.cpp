#include "Controleur.h"
#include <string>
#include "Board.h"

unsigned int Controleur::compteurDeToursBlanc = 0;
unsigned int Controleur::compteurDeToursNoir = 0;

//Méthode pour enregistrer le plateau
void Controleur::enregistrerBoard() {
    std::cout << "Board sauvegardé\n";
    historyStack.push(board);
    std::cout << "Le nombre d'entrées dans la stack: " << historyStack.size() << std::endl;


}
// Méthode pour afficher le menu principal avec les différentes actions disponibles
void Controleur::afficherMenu() const {
    std::cout << "\n=== Menu de Jeu ===\n";
    std::cout << "1. Poser un nouvel insecte sur le plateau\n";
    std::cout << "2. Déplacer un insecte déjà posé\n";
    std::cout << "3. Afficher le plateau\n";
    std::cout << "4. Annuler le coup\n";
    std::cout << "5.Sauvegarder la partie\n";
    std::cout << "0. Quitter\n";
    std::cout << "=== Menu de Debug ===\n"; // n'existera pas pendant une partie
    std::cout << "99. Ajouter une case\n";
    std::cout << "98. Supprimer une case\n";
    std::cout << "Entrez votre choix : ";
}



// Méthode pour obtenir de la part l'utilisateur des coordonnées de la case où une action doit être effectuée
std::pair<int, int> Controleur::demanderCoordonnees() const {
    int x, y;
    std::cout << "Entrez les coordonnées x et y : ";
    std::cin >> x >> y;
    return std::make_pair(x, y);
}

// Méthode principale pour gérer les interactions utilisateur
void Controleur::demarrerPartie() {
    //ici qu'on crée tous nos insectes dès le départ ?
    std::string c;
    std::cout<<"Voulez-vous recharger la partie précédente ? Oui/Non:";
    std::cin>>c;
    if (c=="Oui"){
            std::stack<Board> tempStack;
            std::stack<Board> tempStack1;
            tempStack=reloadGame();
            while (!tempStack.empty()){
                //Inverser la pile pour l'ordre
                tempStack1.push(tempStack.top());
                tempStack.pop();
            }
            historyStack=tempStack1;
            historyStack.pop();
            historyStack.top().print(std::cout);
            board = historyStack.top();
    }
    else {
        std::cout << "Nombre maximal de retours en arrière : ";
        std::cin >> nbRetoursEnArriere;
        if(nbRetoursEnArriere<0){
            std::cout << "Le nombre maximal de retours en arrière doit être positif";
            while(nbRetoursEnArriere<0){
            std::cout << "Nombre maximal de retours en arrière : ";
            std::cin >> nbRetoursEnArriere;
        }
    }

    }

    int choix;
    bool quitter = false;
    Controleur::enregistrerBoard();
    while (!quitter) {
        afficherMenu();
        std::cin >> choix;

        switch (choix) {
            case 0:
                saveGame(historyStack);
                quitter = true;
                break;
            case 1:
                ajouterInsecte();
                break;
            case 2:
                deplacerInsecte();
                break;
            case 3:
                board.print(std::cout);
                break;
            case 4:
                annulerCoup();
                break;
            case 5:
                saveGame(historyStack);
                break;
            case 99:
                ajouterCase();
                break;
            case 98:
                supprimerCase();
                break;
            default:
                std::cout << "Choix invalide, veuillez réessayer.\n";
        }
    }
}

// Méthode pour ajouter une case au plateau
void Controleur::ajouterCase() {
    auto [x, y] = demanderCoordonnees();
    board.addSpot(x, y);
    std::cout << "Case ajoutée aux coordonnées (" << x << ", " << y << ").\n";

}

// Méthode pour ajouter un insecte à une case
void Controleur::ajouterInsecte() {
    //TO DO gerer quand il n'y a pas de possibilité de placement et le retour en arrière

    try {
        std::cout << "Placement d'un nouvel insect sur le plateau ";

        // Se fera automatiquement en fonction du tour du joueur
        unsigned int color;
        std::cout << "Choisissez la couleur de l'insecte (1 pour blanc, 0 pour noir) : ";
        std::cin >> color;


        if(color!=1 && color!=0){ throw ControleurException("Couleur choisie incorrecte."); }
        std::vector<const BoardSpot* > possibilite;
        //si c'est le premier pour chacun tour on cree le premier spot pour insecte
         if (((color == 1)&& (Controleur::getCompteurDeToursBlanc() == 0))||((color==0)&&(Controleur::getCompteurDeToursNoir() == 0)))
        {    std::cout << "Rentre dans la boucle des conditions";
            if (color == 1 ){
            board.addSpot(0, 0);
            std::cout << "j'ajoute un spot" ;
            const BoardSpot* spot = board.getSpot(0, 0);
            possibilite.push_back(spot);}
            if (color == 0){
            std::cout << "Ajout du spot pour la couleur noire à la position (0, 1)";
            board.addSpot(0, 1);
            std::cout << "j'ajoute un spot" ;
            const BoardSpot* spot = board.getSpot(0, 1);
            possibilite.push_back(spot);
            std::cout<< "j'affiche \n";
            board.afficherpossibilite(possibilite);}
        }

        int choix_insect;
        Insect* insect = nullptr;

        do {
        std::cout << "Quel insecte souhaitez vous ajouter? :\n 1: reine, 2: fourmie, 3: arreignée , 4: sauterelle, 5: scarabé, 6:revenir au menu  \n";
        //TODO: voir pour gérér quand on ajoute l'extension
        std::cin >> choix_insect;


        switch (choix_insect)

            {
            case 1:
                if (QueenBee::estPasAuMax(color))
                {
                    insect = new QueenBee();
                    choix_insect=10;
                    break;
                }
            case 2:
                 if (Ant::estPasAuMax(color))
                 {
                     insect = new Ant();
                     choix_insect=10;
                     break;
                 }
            //TODO ecrire les case pour les autres insects et leur ajouter leurs methodes estPasAuMax;
            case 3:
                 if (Spider::estPasAuMax(color))
                 {
                     insect = new Spider();
                     choix_insect=10;
                     break;
                 }
             case 4:
             if (Grasshopper::estPasAuMax(color))
             {
                 insect = new Grasshopper ();
                 choix_insect=10;
                 break;
             }
              case 5:
             if (Beetle::estPasAuMax(color))
             {
                 insect = new Beetle ();
                 choix_insect=10;
                 break;
             }
            case 6 :
                std::cout << "retour au menu\n";
                return;


            default:
                std::cout<<"le choix n'est pas valide /n";

                break;
            }

        }while(choix_insect!= 10);


        insect->setColor(color);


        if (((color == 1)&& (Controleur::getCompteurDeToursBlanc() != 0))||((color==0)&&(Controleur::getCompteurDeToursNoir() != 0))){
            possibilite = board.possibleplacer(color);}
        std::cout<<"afficher possibilités:  \n";
        board.afficherpossibilite(possibilite);
        BoardSpot spot(0, 0);
        int x, y;
        do {auto [newx, newy] = demanderCoordonnees();
            spot = BoardSpot(newx, newy);
            x = newx;
            y = newy;


           }while( !board.est_dans_possibilite(&spot, possibilite));


        board.addInsectToSpot(x, y, insect);
        board.addNullSpot(x,y);

        std::cout << "Insecte ajouté à la case (" << x << ", " << y << ").\n";
        incCompteur(color);
        Controleur::enregistrerBoard();


    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
    catch (const ControleurException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

// Méthode pour déplacer un insecte, différent de moov dans Insect qui testera les différentes possibilités de déplacement
void Controleur::deplacerInsecte() {
    try{     int choix;
        do {    unsigned int color;

                std::cout << "Choisissez votre couleur (1 pour blanc, 0 pour noir) : ";
                std::cin >> color;
                if(color!=1 && color!=0){ throw ControleurException("Couleur choisie incorrecte."); }
                std::vector <const BoardSpot*> piece = board.piecejoueur(color);
                std::cout << "voici vos pièces:";
                board.afficherpossibilite(piece);


                std::cout << "Entrez les coordonnées de la case dont vous voulez connaitre les possibilités d'actions.\n";
                int x, y;
                const BoardSpot* spot = nullptr;
                  do {auto [oldX, oldY] = demanderCoordonnees();
           spot = board.getSpot(oldX, oldY);
            x = oldX;
            y = oldY;


           }while( !board.est_dans_possibilite(spot, piece));



                //appel de moov pour retourner les cases possibles (et potentiellement vérifier s'il y a bien un insecte sur cette case)
                    std::cout << "affichage des possibilités de la pièce\n";
                     std::vector <const BoardSpot*> possibilite = spot->getInsect()->moov(x, y, board);
                     board.afficherpossibilite(possibilite);
                //TODO gerer pour que si il n'y ai pas de possibilité on ne puisse pas entrer 1
                std::cout <<"entrez 1 pour placer la pièce à l'un des emplacements donnés.\n ";
                std::cout <<"entrez 2 pour voir les mouvements possibles d'une autre pièce.\n ";
                std::cout <<"entrez 3 pour retourner au menu.\n ";
                //ou autre
                std::cin >> choix;

                if(choix == 1){
                    std::cout << "Entrez les coordonnées de la case de destination.\n";
                    int newX, newY;
                     const BoardSpot* spot2 = nullptr;
                     do {std::pair<int, int> coordonnees = demanderCoordonnees();
                    newX = coordonnees.first;
                    newY = coordonnees.second;
                        spot2 = board.getSpot(newX, newY);

                        if (!board.est_dans_possibilite(spot2, possibilite)) {
            std::cout << "Coordonnées invalides, veuillez réessayer.\n";
        }

                    }while( !board.est_dans_possibilite(spot2, possibilite));
                    {
                        board.moovInsect(x, y, newX, newY);
                        //TODO gerer les problèmes avec le scarabé
                        board.addNullSpot(newX,newY);

                        std::cout << "Insecte déplacé de (" << x << ", " << y << ") à (" << newX << ", " << newY << ").\n";
                        choix = 3;//TO DO: ameliorer pour que ça passe au tour de l'autre direct
                    }}


                 }while(choix!=3);
    Controleur::enregistrerBoard();

    }


    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

// Méthode pour supprimer une case du plateau
void Controleur::supprimerCase() {
    try{
        auto [x, y] = demanderCoordonnees();
        board.deleteSpot(x, y);
        std::cout << "Case supprimée aux coordonnées (" << x << ", " << y << ").\n";
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

void Controleur::annulerCoup(){
    std::cout << "Le nombre d'entrées dans la stack: " << historyStack.size() << std::endl;

    if (historyStack.size() == 1) {
        std::cout << "Vous êtes déjà au début de la partie.\n";
        return;
    }
    if (nbRetoursEnArriere<=0){
        std::cout << "Vous avez atteint le nombre maximum de retours en arriere de la partie.\n";
        return;
    }
    historyStack.pop();
    board = historyStack.top();
    nbRetoursEnArriere--;
    decCompteur();
    std::cout << "Coup annulé\n";
    std::cout << "Nombre de retours en arriere restants: "<<nbRetoursEnArriere<<"\n";

    //TODO => Regarder pour enlever les tours
}

//fonction qui permet de mettre à jour le tour du joueur;
void Controleur::incCompteur(bool color){
if (color == 1)     Controleur::ajouterCompteurDeToursBlanc();
if (color == 0)   Controleur::ajouterCompteurDeToursNoir();
}

//fonction qui permet d'annuler le tour du joueur;
void Controleur::decCompteur(){
    if (compteurDeToursBlanc>compteurDeToursNoir){
        enleverCompteurDeToursBlanc();
    }
    else {
        enleverCompteurDeToursNoir();
    }
}

//Méthode pour sauvegarder la partie
void Controleur::saveGame(std::stack<Board> boardStack){
    try {
        const std::string& filename = "boards.sauv";
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing.");
        }

        while (!boardStack.empty()) {
            Board board = boardStack.top();
            boardStack.pop();

            // Save the board
            outFile << board.getNb() << "\n";  // Write the number of spots
            for (size_t i = 0; i < board.getNb(); ++i) {
                BoardSpot spot = board.getSpotIndex(i);
                //serialize a BoardSpot to a file
                // Write coordinates (x, y)
                auto coordinates = spot.getCoordinates();
                outFile << coordinates.first << " " << coordinates.second << " ";

                // Write insect type if present
                if (spot.hasInsect()) {
                    Insect* insect = spot.getInsect();
                    outFile << insect->getType() << " " << insect->getColor() << "\n"; // Save insect type and color
                } else {
                    outFile << "none\n";  // Indicate no insect present
                }
            }

        } std::cout<<"Fichier sauvegardé avec succès !\n";

        outFile.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving boards: " << e.what() << std::endl;
    }
}

//Méthode pour reload la partie
std::stack<Board> Controleur::reloadGame(){
    try {

        const std::string& filename = "boards.sauv";
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        std::stack<Board> boardStack;
        while (inFile.peek() != EOF) {  // Loop until the end of the file
            size_t nb;
            inFile >> nb;  // Read the number of spots for this board

            Board board;
            for (size_t i = 0; i < nb; ++i) {

                int x, y;
                inFile >> x >> y;  // Read coordinates
                std::cout<<"x="<<x<<"\n";
                std::cout<<"y="<<y<<"\n";
                BoardSpot spot(x, y);

                std::string insectType;
                inFile >> insectType;  // Read insect type

                if (insectType != "none") {
                    int color;
                    inFile >> color;  // Read insect color

                    // You would need to properly reconstruct the insect based on its type and color
                    Insect* insect = nullptr;
                    if (insectType == "ant") {
                        insect = new Ant(); // Example, you'd need to handle creating the correct insect type
                    } else if (insectType == "queenbee") {
                        insect = new QueenBee();  // Similarly for QueenBee or other types
                    }

                    spot.setInsect(insect);
                }
                board.addSpot(spot.getCoordinates().first, spot.getCoordinates().second);  // Add to the board
                if (spot.hasInsect()) {
                    std::cout<<"here\n";
                    board.addInsectToSpot(spot.getCoordinates().first, spot.getCoordinates().second, spot.getInsect());
                }
            }

            boardStack.push(board);  // Push the board to the stack
        }

    inFile.close();
    std::cout << "Boards chargés avec succès!" << std::endl;
    return boardStack;


    } catch (const std::exception& e) {
        std::cerr << "Erreur au chargement des boards: " << e.what() << std::endl;
    }
}
