#include "Controleur.h"

// Méthode pour afficher le menu principal avec les différentes actions disponibles
void Controleur::afficherMenu() const {
    std::cout << "\n=== Menu de Jeu ===\n";
    std::cout << "1. Poser un insecte\n";
    std::cout << "2. Déplacer un insecte\n";
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
    try {
        auto [x, y] = demanderCoordonnees();

        // Demander la couleur de l'insecte
        // Se fera automatiquement en fonction du tour du joueur
        unsigned int color;
        std::cout << "Choisissez la couleur de l'insecte (1 pour blanc, 0 pour noir) : ";
        std::cin >> color;
        if(color!=1 && color!=0){ throw ControleurException("Couleur choisie incorrecte."); }

        Insect* insect = new Insect();
        insect->setColor(color);

        board.addInsectToSpot(x, y, insect);
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
    try{
        std::cout << "Entrez les coordonnées de la case de départ.\n";
        auto [oldX, oldY] = demanderCoordonnees();
        //appel de moov pour retourner les cases possibles (et potentiellement vérifier s'il y a bien un insecte sur cette case)

        std::cout << "Entrez les coordonnées de la case de destination.\n";
        auto [newX, newY] = demanderCoordonnees();
        //vérification de moov pour savoir si le déplacement n'est pas illégal

        board.modifySpot(oldX, oldY, newX, newY);
        std::cout << "Insecte déplacé de (" << oldX << ", " << oldY << ") à (" << newX << ", " << newY << ").\n";
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
