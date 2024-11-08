#include "Controleur.h"

// Méthode pour afficher le menu principal avec les différentes actions disponibles
void Controleur::afficherMenu() const {
    std::cout << "\n=== Menu de Jeu ===\n";
    std::cout << "1. Poser un nouvel insecte sur le plateau\n";
    std::cout << "2. Déplacer un insecte déjà posé\n";
    std::cout << "3. Afficher le plateau\n";
    std::cout << "4. Annuler le coup\n";
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
    int choix;
    bool quitter = false;

    while (!quitter) {
        afficherMenu();
        std::cin >> choix;

        switch (choix) {
            case 0:
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
    //TO DO gerer le premier placement sur une case fixe

    try {
        std::cout << "Placement d'un nouvel insect sur le plateau ";

        // Se fera automatiquement en fonction du tour du joueur
        unsigned int color;
        std::cout << "Choisissez la couleur de l'insecte (1 pour blanc, 0 pour noir) : ";
        std::cin >> color;
        if(color!=1 && color!=0){ throw ControleurException("Couleur choisie incorrecte."); }



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

            case 6 :
                std::cout << "retour au menu\n";
                return;


            default:
                std::cout<<"le choix n'est pas valide /n";
                break;
            }

        }while(choix_insect!= 10);


        insect->setColor(color);

        std::vector<const BoardSpot* > possibilite = board.possibleplacer(color);
        board.afficherpossibilite(possibilite);
        auto [x, y] = demanderCoordonnees();


        board.addInsectToSpot(x, y, insect);
        //TO DO: fonction creer cases vides autour de l'insect ajouté
        std::cout << "Insecte ajouté à la case (" << x << ", " << y << ").\n";
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
        do {
                std::cout << "Entrez les coordonnées de la case dont vous voulez connaitre les possibilités d'actions.\n";
                auto [oldX, oldY] = demanderCoordonnees();
                const BoardSpot* spot = board.getSpot(oldX, oldY);
                if (!spot){std::cout <<"les coordonnées ne sont pas bonnes \n";}
                //appel de moov pour retourner les cases possibles (et potentiellement vérifier s'il y a bien un insecte sur cette case)
                else{
                     std::vector <const BoardSpot*> possibilite = spot->getInsect()->moov(oldX, oldY, board);
                     board.afficherpossibilite(possibilite);

                std::cout <<"entrez 1 pour placer la pièce à l'un des emplacements donnés.\n ";
                std::cout <<"entrez 2 pour voir les mouvements possibles d'une autre pièce.\n ";
                std::cout <<"entrez 2 pour retourner au menu.\n ";
                std::cout <<"entrez 3 pour voir les mouvements possibles d'une autre pièce.\n ";//ou autre
                std::cin >> choix;

                if(choix == 1){
                    std::cout << "Entrez les coordonnées de la case de destination.\n";
                    auto [newX, newY] = demanderCoordonnees();
                    const BoardSpot* spot = board.getSpot(newX, newY);
                    if ( board.est_dans_possibilite(spot, possibilite)== true)
                    {
                        board.modifySpot(oldX, oldY, newX, newY);
                        std::cout << "Insecte déplacé de (" << oldX << ", " << oldY << ") à (" << newX << ", " << newY << ").\n";
                        choix = 2;//TO DO: ameliorer pour que ça passe au tour de l'autre direct
                    }
                    else{std::cout << "les coordonnées ne sont pas bonnes\n";}

                }}} while(choix!=2);
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
    std::cout << "cette fonction n'est pas encore implémentée.\n";
}



