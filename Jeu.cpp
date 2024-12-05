#include "Jeu.h"

unsigned int Jeu::compteurDeToursBlanc=0;
unsigned int Jeu::compteurDeToursNoir=0;

void Jeu::printInsectsNoir(std::ostream& f=std::cout){
    if(insectsNoir.size()==0) { f << "Il n'y a plus d'insecte noir a poser !\n"; }
    for(size_t i=0; i<insectsNoir.size(); i++){
        f << i << "eme insecte noir : " << insectsNoir[i]->getType() << "\n";
    }
}
void Jeu::printInsectsBlanc(std::ostream& f=std::cout){
    if(insectsBlanc.size()==0) { f << "Il n'y a plus d'insecte " << WHITE << "blanc" << BLACK << " a poser !\n"; }
    for(size_t i=0; i<insectsBlanc.size(); i++){
        f << BLACK << i << "eme insecte " << WHITE << "blanc" << BLACK << " : " << insectsBlanc[i]->getType() << "\n";
    }
}

//Méthode pour enregistrer le plateau
void Jeu::enregistrerBoard() {
    std::cout << "Board sauvegardé\n";
    historyStack.push(board);
    std::cout << "Le nombre d'entrées dans la stack: " << historyStack.size() << std::endl;
}

void Jeu::createInsects(){
       addType([](){return new QueenBee;}, QueenBee::getMax());
       addType([](){return new Ant;}, Ant::getMax());
       addType([](){return new Beetle;}, Beetle::getMax());
       addType([](){return new Grasshopper;}, Grasshopper::getMax());
       addType([](){return new Spider;}, Spider::getMax());


               for (const auto& insectInfo : insectTypes) {
            for (unsigned int i = 0; i < insectInfo.second; i++) {
                // Blanc
                Insect* blanc = insectInfo.first();
                blanc->setColor(true);
                insectsBlanc.push_back(blanc);

                // Noir
                Insect* noir = insectInfo.first();
                noir->setColor(false);
                insectsNoir.push_back(noir);
            }
        }
    }




// Méthode pour afficher le menu principal avec les différentes actions disponibles
void Jeu::afficherMenu() const {
    std::cout << "\n=== Menu de Jeu ===\n";
    std::cout << "1. Poser un nouvel insecte sur le plateau\n";
    std::cout << "2. Déplacer un insecte déjà posé\n";
    std::cout << "3. Afficher le plateau\n";
    std::cout << "4. Annuler le coup\n";
    std::cout << "5. Sauvegarder la partie\n";
    std::cout << "0. Quitter\n";
    /*std::cout << "=== Menu de Debug ===\n"; // n'existera pas pendant une partie
    std::cout << "99. Ajouter une case\n";
    std::cout << "98. Supprimer une case\n";*/
    std::cout << "===================\n";
    std::cout << "Tour du joueur ";
    if((compteurDeToursBlanc+compteurDeToursNoir+1)%2==0){ std::cout << "noir.\n"; }
    else{ std::cout << WHITE << "blanc"<<BLACK<<".\n"; }
    std::cout << "Entrez votre choix : ";
}

// Méthode pour obtenir de la part l'utilisateur des coordonnées de la case où une action doit être effectuée
std::pair<int, int> Jeu::demanderCoordonnees() const {
    int x, y;
    std::cout << "Entrez les coordonnées x et y : ";
    std::cin >> x >> y;
    return std::make_pair(x, y);
}

// Méthode principale pour gérer les interactions utilisateur
void Jeu::demarrerPartie() {
    int choix;
    bool quitter = false;
    while (!quitter) {

        //Test de victoire du joueur qui vient de jouer (on vérifie d'abord sur la reine adverse, c'est à dire la reine du joueur qui est sur le point de jouer)
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) << "\n=========\n";
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) << "\n=========\n";
        if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1)){
            std::cout <<CYAN<< "Le joueur ";

            // Ici on annonce la victoire du joueur qui vient de jouer (c'est pour cela qu'on n'a pas de +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir)%2==1){ std::cout << WHITE << "blanc" << BLACK; }
            else{ std::cout << "noir"; }
            std::cout <<CYAN<< "a gagne !"<<BLACK<<"\n";
        }
        // On vérifie maintenant sur la reine du joueur qui vient de jouer, dans le cas où il s'est fait perdre tout seul
        else if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1)){
            std::cout <<CYAN<< "Le joueur ";

            // Ici on annonce la victoire du joueur qui était sur le point de jouer (c'est pour cela qu'on a un +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1){ std::cout << WHITE << "blanc" << BLACK;}
            else{ std::cout << "noir";}
            std::cout <<CYAN<< "a gagne !"<<BLACK<<"\n";
        }
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
                std::cout << "Coup annulé\n";
                std::cout << "Nombre de retours en arriere restants: "<<nbRetoursEnArriere<<"\n";
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
void Jeu::ajouterCase() {
    auto [x, y] = demanderCoordonnees();
    board.addSpot(x, y);
    std::cout << "Case ajoutée aux coordonnées (" << x << ", " << y << ").\n";
}

// Méthode pour ajouter un insecte à une case
void Jeu::ajouterInsecte() {
    try {
        std::cout << "Placement d'un nouvel insecte sur le plateau : joueur ";

        // Joueur blanc commence
        unsigned int color=(compteurDeToursBlanc+compteurDeToursNoir+1)%2;

        // Se fera automatiquement en fonction du tour du joueur
        /*std::cout << "Choisissez la couleur de l'insecte (1 pour blanc, 0 pour noir) : ";
        std::cin >> color;*/

        if(color!=1 && color!=0){ throw JeuException("Couleur choisie incorrecte."); }
        if(color==1){ std::cout << WHITE << "Blanc\n" << BLACK; }
        else{ std::cout << "Noir\n"; }

        // Affichage et retour au menu si jamais le joueur n'a plus d'insecte à poser
        if((color==0 && insectsNoir.empty()) || (color==1 && insectsBlanc.empty())) {
            std::cout << RED << "Vous n'avez plus d'insecte à poser !!" << BLACK << "\n";
            return;
        }

        std::cout <<BLACK<< "Voici les insectes que vous pouvez poser :\n";
        if(color==0){ printInsectsNoir(); }
        else{ printInsectsBlanc(); }

        std::vector<const BoardSpot* > possibilite;
        //si c'est le premier pour chacun tour on cree le premier spot pour insecte
        if (((color == 0)&& (Jeu::getCompteurDeToursNoir() == 0))||((color==1)&&(Jeu::getCompteurDeToursBlanc() == 0))){
            //std::cout << "\n=========\nDEBUG : Rentre dans la boucle des conditions\n=========\n\n";
            if (color == 1){
                if (board.getSpot(0, 0)==nullptr){
                    board.addSpot(0, 0);
                    //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur blanche à la position (0, 0)\n=========\n\n";
                }
                const BoardSpot* spot = board.getSpot(0, 0);
                possibilite.push_back(spot);
            }
            if (color == 0){
                if (board.getSpot(0, 1) == nullptr) {
                    board.addSpot(0, 1);
                    //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur noire à la position (0, 1)\n=========\n\n";
                }
                const BoardSpot* spot = board.getSpot(0, 1);
                possibilite.push_back(spot);
            }
        }

        if (((color == 1)&& (Jeu::getCompteurDeToursBlanc() != 0))||((color==0)&&(Jeu::getCompteurDeToursNoir() != 0))){
            possibilite = board.possibleplacer(color);
        }

        std::cout<<"Voici vos possibilités de placement : \n";
        board.afficherpossibilite(possibilite);


        Insect* insect = nullptr;

        if((color==0 && getCompteurDeToursNoir()== 3 && QueenBee::getPoseNoir()==0) || (color==1 && getCompteurDeToursBlanc()== 3 && QueenBee::getPoseBlanc()==0)){
            std::cout  << RED << "C'est votre 4e tour, vous devez poser votre reine !"<<BLACK<<"\n";
            size_t i=0;
                do{
                    if(color==1){
                        if("queenbee" == insectsBlanc[i]->getType()){
                            //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                            insect=insectsBlanc[i];
                            insectsBlanc.erase(insectsBlanc.begin()+i);
                        }
                    }
                    else{
                        if("queenbee" == insectsNoir[i]->getType()){
                            //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                            insect=insectsNoir[i];
                            insectsNoir.erase(insectsNoir.begin()+i);
                        }
                    }
                    i++;
                }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())));
        }else{
            int choix_insect;

            do {
                std::cout << "Quel insecte souhaitez vous ajouter? :\n 1: reine, 2: fourmi, 3: araignée, 4: sauterelle, 5: scarabé, 0:revenir au menu\n";
                std::cout << "Entrez votre choix : ";
                //TODO: voir pour gérer quand on ajoute l'extension
                std::cin >> choix_insect;

                switch (choix_insect){
                    case 1:
                        //std::cout << "\n=========\nDEBUG : QueenBee::estPasAuMax(color) -> " << QueenBee::estPasAuMax(color) << "\n=========\n\n";
                        if (QueenBee::estPasAuMax(color)){
                            size_t i=0;
                            do{
                                if(color==1){
                                    if("queenbee" == insectsBlanc[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                                        insect=insectsBlanc[i];
                                        insectsBlanc.erase(insectsBlanc.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                else{
                                    if("queenbee" == insectsNoir[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                                        insect=insectsNoir[i];
                                        insectsNoir.erase(insectsNoir.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                i++;
                            }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())) && choix_insect!=10);
                        }
                        else{
                            std::cout  << RED << "Vous ne pouvez plus poser de QueenBee !"<<BLACK<<"\n";
                        }
                        break;
                    case 2:
                        //std::cout << "\n=========\nDEBUG : Ant::estPasAuMax(color) -> " << Ant::estPasAuMax(color) << "\n=========\n\n";
                        if (Ant::estPasAuMax(color)){
                            size_t i=0;
                            do{
                                if(color==1){
                                    if("ant" == insectsBlanc[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                                        insect=insectsBlanc[i];
                                        insectsBlanc.erase(insectsBlanc.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                else{
                                    if("ant" == insectsNoir[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                                        insect=insectsNoir[i];
                                        insectsNoir.erase(insectsNoir.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                i++;
                            }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())) && choix_insect!=10);
                        }
                        else{
                            std::cout  << RED << "Vous ne pouvez plus poser de Ant !"<<BLACK<<"\n";
                        }
                        break;
                    case 3:
                        //std::cout << "\n=========\nDEBUG : Spider::estPasAuMax(color) -> " << Spider::estPasAuMax(color) << "\n=========\n\n";
                        if (Spider::estPasAuMax(color)){
                            size_t i=0;
                            do{
                                if(color==1){
                                    if("spider" == insectsBlanc[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                                        insect=insectsBlanc[i];
                                        insectsBlanc.erase(insectsBlanc.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                else{
                                    if("spider" == insectsNoir[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                                        insect=insectsNoir[i];
                                        insectsNoir.erase(insectsNoir.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                i++;
                            }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())) && choix_insect!=10);
                        }
                        else{
                            std::cout  << RED << "Vous ne pouvez plus poser de Spider !"<<BLACK<<"\n";
                        }
                        break;
                    case 4:
                        //std::cout << "\n=========\nDEBUG : Grasshopper::estPasAuMax(color) -> " << Grasshopper::estPasAuMax(color) << "\n=========\n\n";
                        if (Grasshopper::estPasAuMax(color)){
                            size_t i=0;
                            do{
                                if(color==1){
                                    if("grasshopper" == insectsBlanc[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                                        insect=insectsBlanc[i];
                                        insectsBlanc.erase(insectsBlanc.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                else{
                                    if("grasshopper" == insectsNoir[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                                        insect=insectsNoir[i];
                                        insectsNoir.erase(insectsNoir.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                i++;
                            }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())) && choix_insect!=10);
                        }
                        else{
                            std::cout  << RED << "Vous ne pouvez plus poser de Grasshopper !"<<BLACK<<"\n";
                        }
                        break;
                    case 5:
                        //std::cout << "\n=========\nDEBUG : Beetle::estPasAuMax(color) -> " << Beetle::estPasAuMax(color) << "\n=========\n\n";
                        if (Beetle::estPasAuMax(color)){
                            size_t i=0;
                            do{
                                if(color==1){
                                    if("beetle" == insectsBlanc[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsBlanc[i]->getType() << insectsBlanc[i]->getColor() << "\n=========\n\n";
                                        insect=insectsBlanc[i];
                                        insectsBlanc.erase(insectsBlanc.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                else{
                                    if("beetle" == insectsNoir[i]->getType()){
                                        //std::cout << "\n=========\nDEBUG : "<< i << " : " << insectsNoir[i]->getType() << insectsNoir[i]->getColor() << "\n=========\n\n";
                                        insect=insectsNoir[i];
                                        insectsNoir.erase(insectsNoir.begin()+i);
                                        choix_insect=10;
                                    }
                                }
                                i++;
                            }while(((color==0 && i<insectsNoir.size()) || (color==1 && i<insectsBlanc.size())) && choix_insect!=10);
                        }
                        else{
                            std::cout  << RED << "Vous ne pouvez plus poser de Beetle !"<<BLACK<<"\n";
                        }
                        break;

                    //TODO ecrire les case pour les autres insects et leur ajouter leurs methodes estPasAuMax;
                    case 0 :
                        std::cout << "retour au menu\n";
                        return;
                        break;


                    default:
                        std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";

                        break;
                    }

            }while(choix_insect!= 10);
        }


        BoardSpot spot(0, 0);
        int x, y;
        do {
            auto [newx, newy] = demanderCoordonnees();
            spot = BoardSpot(newx, newy);
            x = newx;
            y = newy;
            if (!board.est_dans_possibilite(&spot, possibilite)) {
                std::cout  << RED << "Coordonnées invalides, veuillez réessayer."<<BLACK<<"\n";
            }
        }while( !board.est_dans_possibilite(&spot, possibilite) );


        board.addInsectToSpot(x, y, insect);
        board.addNullSpot(x,y);

        //std::cout << "\n=========\nDEBUG : Insecte ajouté à la case (" << x << ", " << y << ").\n=========\n\n";
        incCompteur(color);
        Jeu::enregistrerBoard();

        if(insect->getType()== "queenbee"){
            if(color==1){QueenBee::ajouterBlanc();}
            else{QueenBee::ajouterNoir();}
        }
        else if(insect->getType()== "ant"){
            if(color==1){Ant::ajouterBlanc();}
            else{Ant::ajouterNoir();}
        }
        else if(insect->getType()== "spider"){
            if(color==1){Spider::ajouterBlanc();}
            else{Spider::ajouterNoir();}
        }
        else if(insect->getType()== "grasshopper"){
            if(color==1){Grasshopper::ajouterBlanc();}
            else{Grasshopper::ajouterNoir();}
        }
        else if(insect->getType()== "beetle"){
            if(color==1){Beetle::ajouterBlanc();}
            else{Beetle::ajouterNoir();}
        }
        // TO DO : incrémenter les compteurs des autres insectes
        else{ std::cout << RED <<"le choix n'est pas valide, mais ça ne devrait pas arriver ici... (ajout du nombre d'insectes posés dans Jeu::ajouterInsecte)"<<BLACK<<"/n"; }

    }
    catch (const SetException& e){
        std::cout  << RED << e.getMessage()  << BLACK <<"\n";
    }
    catch (const JeuException& e){
        std::cout  << RED << e.getMessage()  << BLACK <<"\n";
    }
}

// Méthode pour déplacer un insecte, différent de moov dans Insect qui testera les différentes possibilités de déplacement
void Jeu::deplacerInsecte() {
    try{
        int choix=0;
        unsigned int color;
        // Le joueur blanc a commence
        color=(compteurDeToursBlanc+compteurDeToursNoir+1)%2;
        if(board.piecejoueur(color).empty()){
            std::cout  << RED << "Vous n'avez aucune piece sur le plateau !"<<BLACK<<"\n";
            return;
        }
        if(QueenBee::estPasAuMax(color)){
            std::cout  << RED << "Vous ne pouvez pas deplacer de piece tant que vous n'avez pas pose votre reine !"<<BLACK<<"\n";
            return;
        }
        do {

            /*std::cout << "Choisissez votre couleur (1 pour blanc, 0 pour noir) : ";
            std::cin >> color;
            if(color!=1 && color!=0){ throw JeuException("Couleur choisie incorrecte."); }*/
            std::vector <const BoardSpot*> piece = board.piecejoueur(color);
            std::cout << "Voici vos pièces disponibles sur le plateau : \n";
            board.afficherpossibilite(piece);


            std::cout << "Entrez les coordonnées de la case dont vous voulez connaitre les possibilités d'actions.\n";
            int x, y;
            const BoardSpot* spot = nullptr;
            do {
                auto [oldX, oldY] = demanderCoordonnees();
                spot = board.getSpot(oldX, oldY);
                x = oldX;
                y = oldY;
            }while( !board.est_dans_possibilite(spot, piece));
            //std::cout << "\n=========\nDEBUG : j'arrive dans la partie d'après.\n=========\n\n";


            //appel de moov pour retourner les cases possibles (et potentiellement vérifier s'il y a bien un insecte sur cette case)
            std::vector <const BoardSpot*> possibilite = spot->getInsect()->moov(x, y, board);
            std::cout << "Voici les possibilités de déplacement de votre pièce\n";
            board.afficherpossibilite(possibilite);

            // On véfifie qu'il y a bien des possibilités avant de proposer un déplacement
            if(!possibilite.empty()){
                std::cout <<"Entrez 1 pour placer la pièce à l'un des emplacements donnés.\n";
                std::cout <<"Entrez 2 pour voir les mouvements possibles d'une autre pièce.\n";
                std::cout <<"Entrez 3 pour retourner au menu.\n";
                std::cout <<"Entrez votre choix : ";
                //ou autre
                std::cin >> choix;

                if(choix == 1){
                    std::cout << "Entrez les coordonnées de la case de destination.\n";
                    int newX, newY;
                    const BoardSpot* spot2 = nullptr;
                    do {
                        std::pair<int, int> coordonnees = demanderCoordonnees();
                        newX = coordonnees.first;
                        newY = coordonnees.second;
                        spot2 = board.getSpot(newX, newY);

                        if (!board.est_dans_possibilite(spot2, possibilite)) {
                            std::cout  << RED << "Coordonnées invalides, veuillez réessayer."<<BLACK<<"\n";
                        }
                    }while( !board.est_dans_possibilite(spot2, possibilite) );

                    board.moovInsect(x, y, newX, newY);
                    //TODO gerer les problèmes avec le scarabé
                    board.addNullSpot(newX,newY);

                    //std::cout << "\n=========\nDEBUG : Insecte déplacé de (" << oldX << ", " << oldY << ") à (" << newX << ", " << newY << ").\n=========\n\n";
                    incCompteur(color);
                    choix = 3;//TO DO: ameliorer pour que ça passe au tour de l'autre direct
                }
            }
        }while(choix!=3);
        Jeu::enregistrerBoard();
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

// Méthode pour supprimer une case du plateau
void Jeu::supprimerCase() {
    try{
        auto [x, y] = demanderCoordonnees();
        board.deleteSpot(x, y);
        std::cout << "Case supprimée aux coordonnées (" << x << ", " << y << ").\n";
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

void Jeu::annulerCoup(){
    std::cout << "Le nombre d'entrées dans la stack: " << historyStack.size() << std::endl;
    if (nbRetoursEnArriere<=0){
        std::cout << "Vous avez atteint le nombre maximum de retours en arriere de la partie.\n";
        return;
    }
    if (historyStack.size() == 1) {
        std::cout << "Vous êtes déjà au début de la partie.\n";
        return;
    }

    historyStack.pop();
    majListeInsect(historyStack.top());
    nbRetoursEnArriere--;
    decCompteur();

    //TODO => Regarder pour enlever les tours
}

//fonction qui permet de mettre à jour le tour du joueur;
void Jeu::incCompteur(bool color){
if (color == 1)   Jeu::ajouterCompteurDeToursBlanc();
if (color == 0)   Jeu::ajouterCompteurDeToursNoir();
}

//fonction qui permet d'annuler le tour du joueur;
void Jeu::decCompteur(){
    if (compteurDeToursBlanc>compteurDeToursNoir) enleverCompteurDeToursBlanc();
    else enleverCompteurDeToursNoir();
}

//Méthode pour sauvegarder la partie
void Jeu::saveGame(std::stack<Board> boardStack){
    try {
        const std::string& filename = "boards.sauv";
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing.");
        }

        outFile <<getnbRetoursEnArriere() << "\n"; //Ecrire le nombre de retours en arrière dans le ficher

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
std::stack<Board> Jeu::reloadGame(){
    try {

        const std::string& filename = "boards.sauv";
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Failed to open file for reading.");
        }
        int nb_retours;
        inFile >> nb_retours;
        if (inFile.fail()) {
            throw std::runtime_error("Failed to read number of retours.");
        }
        std::cout << "Number of retours: " << nb_retours << "\n";
        setnbRetoursEnArriere(nb_retours);

        std::stack<Board> boardStack;
        while (inFile.peek() != EOF) {  // Loop until the end of the file
            size_t nb;
            inFile >> nb;  // Read the number of spots for this board

            Board board;
            for (size_t i = 0; i < nb; ++i) {

                int x, y;
                inFile >> x >> y;  // Read coordinates
                BoardSpot spot(x, y);
                board.addSpot(x, y);  //
                std::string insectType;
                inFile >> insectType;  // Read insect type

                if (insectType != "none") {
                    int color;
                    inFile >> color;  // Read insect color

                    // You would need to properly reconstruct the insect based on its type and color
                    Insect* insect = nullptr;
                    if (insectType == "ant" ) {
                        insect = new Ant(); // Example, you'd need to handle creating the correct insect type
                    } else if (insectType == "queenbee") {
                        insect = new QueenBee();  // Similarly for QueenBee or other types
                    }
                    else if (insectType == "beetle") {
                        insect = new Beetle();  // Similarly for QueenBee or other types
                    }
                    else if (insectType == "grasshopper") {
                        insect = new Grasshopper();  // Similarly for QueenBee or other types
                    }
                    else if (insectType == "spider") {
                        insect = new Spider();  // Similarly for QueenBee or other types
                    }
                    else if (insectType == "ladybug") {
                        //insect = new Ladybug();  // Similarly for QueenBee or other types
                    }
                    else if (insectType == "mosquito") {
                        //insect = new Mosquito();  // Similarly for QueenBee or other types
                    }

                    insect->setColor(color);
                    //TODO gérer les possibilités + a qui c'est le tour dans le fichier?
                    spot.setInsect(insect);
                    board.addInsectToSpot(x,y, insect);

                }

            }
            std::cout<<"b:";
            board.afficherpossibilite(board.possibleplacer(1));
            std::cout<<"N:";
            board.afficherpossibilite(board.possibleplacer(0));
            std::cout<<"\n";
            boardStack.push(board);  // Push the board to the stack
        }
        //board.afficherpossibilite(insect);

        inFile.close();
        std::cout << "Boards chargés avec succès!" << std::endl;

        //Gestion des tours
        int sizeBoardStack = boardStack.size();
        if (sizeBoardStack%2==0){ //pair
                for (int i=0; i<(sizeBoardStack/2)-1;i++){
                    incCompteur(0);
                    incCompteur(1);
                }}
        else if (sizeBoardStack%2!=0){
                for (int i=0; i<(sizeBoardStack/2)-1;i++){
                    incCompteur(0);
                    incCompteur(1);
                }
                incCompteur(1);
        }
        std::cout<<"TB:"<<compteurDeToursBlanc<<"\n";
        std::cout<<"TN:"<<compteurDeToursNoir<<"\n";
        return boardStack;
    } catch (const std::exception& e) {
        std::cerr << "Erreur au chargement des boards: " << e.what() << std::endl;
    }
}

//methode qui renvoit true si la reine de la couleur color est entouree
bool Jeu::isQueenSurrounded(bool color) const{
    if (QueenBee::estPasAuMax(color)){ return false; }
    std::vector<const BoardSpot*> piecesPosees = board.piecejoueur(color);
    for (size_t i = 0; i<piecesPosees.size(); i++){
        if (piecesPosees[i]->getInsect()->getType()=="queenbee"){
            std::pair<int, int> coords = piecesPosees[i]->getCoordinates();
            if(board.trouverVoisinsInsects(coords.first,coords.second).size()>=6){ return true; }
        }
    }
    return false;
}

//Méthode pour free les instects
void Jeu::freeListeInsect(std::vector<Insect*>& liste_i) {
    for (auto& i : liste_i) {
        delete i;
        i = nullptr;
    }
    liste_i.clear();
}

//Méthode pour créer une liste de tous les insects Blancs
std::vector<Insect*> Jeu::createInsectsB() {
    std::vector<Insect*> insectsBlanc; // Initialize the vector properly

    // Add QueenBees
    for (unsigned int i = 0; i < QueenBee::getMax(); i++) {
        insectsBlanc.push_back(new QueenBee);
        insectsBlanc.back()->setColor(true);
    }

    // Add Ants
    for (unsigned int i = 0; i < Ant::getMax(); i++) {
        insectsBlanc.push_back(new Ant);
        insectsBlanc.back()->setColor(true);
    }

    // Add Beetles
    for (unsigned int i = 0; i < Beetle::getMax(); i++) {
        insectsBlanc.push_back(new Beetle);
        insectsBlanc.back()->setColor(true);
    }

    // Add Grasshoppers
    for (unsigned int i = 0; i < Grasshopper::getMax(); i++) {
        insectsBlanc.push_back(new Grasshopper);
        insectsBlanc.back()->setColor(true);
    }

    // Add Spiders
    for (unsigned int i = 0; i < Spider::getMax(); i++) {
        insectsBlanc.push_back(new Spider);
        insectsBlanc.back()->setColor(true);
    }

    return insectsBlanc; // Return the vector
}

//Méthode pour créer une liste de tous les insects Noirs
std::vector<Insect*> Jeu::createInsectsN() {
    std::vector<Insect*> insectsNoir; // Initialize the vector properly

    // Add QueenBees
    for (unsigned int i = 0; i < QueenBee::getMax(); i++) {
        insectsNoir.push_back(new QueenBee);
        insectsNoir.back()->setColor(false);
    }

    // Add Ants
    for (unsigned int i = 0; i < Ant::getMax(); i++) {
        insectsNoir.push_back(new Ant);
        insectsNoir.back()->setColor(false);
    }

    // Add Beetles
    for (unsigned int i = 0; i < Beetle::getMax(); i++) {
        insectsNoir.push_back(new Beetle);
        insectsNoir.back()->setColor(false);
    }

    // Add Grasshoppers
    for (unsigned int i = 0; i < Grasshopper::getMax(); i++) {
        insectsNoir.push_back(new Grasshopper);
        insectsNoir.back()->setColor(false);
    }

    // Add Spiders
    for (unsigned int i = 0; i < Spider::getMax(); i++) {
        insectsNoir.push_back(new Spider);
        insectsNoir.back()->setColor(false);
    }

    return insectsNoir; // Return the vector
}

//Méthode qui free la liste de tous les instects restants et refait la liste du début
//cherche si l'insecte est sur le board, si oui l'enlève de la liste
void Jeu::majListeInsect(Board& board_i) {
    // Free the current lists of insects
    freeListeInsect(insectsBlanc);
    freeListeInsect(insectsNoir);


    // Recreate the lists
    insectsBlanc = createInsectsB();
    insectsNoir = createInsectsN();

    resetInsectCount();

    // Check the board and update the lists
    for (size_t i = 0; i < board_i.getNb(); i++) {
        const BoardSpot& spot = board_i.getSpotIndex(i); // Access each spot on the board
        if (spot.hasInsect()) {
            Insect* insectOnBoard = spot.getInsect();

            if (insectOnBoard->getColor() == 1) {
                // Remove insect from `insectsBlanc` if found
                auto it = std::find_if(insectsBlanc.begin(), insectsBlanc.end(),
                                       [&insectOnBoard](const Insect* insect) {
                                           return insect->getType() == insectOnBoard->getType();
                                       });

                if (it != insectsBlanc.end()) {
                    insectsBlanc.erase(it);

                    // Increment the count for the corresponding insect type
                    if (insectOnBoard->getType() == "queenbee") { QueenBee::ajouterBlanc(); }
                    else if (insectOnBoard->getType() == "ant") { Ant::ajouterBlanc(); }
                    else if (insectOnBoard->getType() == "beetle") { Beetle::ajouterBlanc(); }
                    //else if (insectOnBoard->getType() == "ladybug") { Ladybug::ajouterBlanc(); }
                    else if (insectOnBoard->getType() == "spider") { Spider::ajouterBlanc(); }
                    //else if (insectOnBoard->getType() == "mosquito") { Mosquito::ajouterBlanc(); }
                } else {
                    std::cout << RED << "Problème pour l'insect blanc: " << insectOnBoard->getType() << "\n";
                }

            } else {
                // Remove insect from `insectsNoir` if found
                auto it = std::find_if(insectsNoir.begin(), insectsNoir.end(),
                                       [&insectOnBoard](const Insect* insect) {
                                           return insect->getType() == insectOnBoard->getType();
                                       });

                if (it != insectsNoir.end()) {

                    insectsNoir.erase(it);

                    // Increment the count for the corresponding insect type
                    if (insectOnBoard->getType() == "queenbee") { QueenBee::ajouterNoir(); }
                    else if (insectOnBoard->getType() == "ant") { Ant::ajouterNoir(); }
                    else if (insectOnBoard->getType() == "beetle") { Beetle::ajouterNoir(); }
                    else if (insectOnBoard->getType() == "spider") { Spider::ajouterNoir(); }
                    else if (insectOnBoard->getType() == "grasshopper") { Spider::ajouterNoir(); }
                    //else if (insectOnBoard->getType() == "ladybug") { Ladybug::ajouterNoir(); }
                    //else if (insectOnBoard->getType() == "mosquito") { Mosquito::ajouterNoir(); }
                } else {
                    std::cout << RED << "Problème pour l'insect noir: " << insectOnBoard->getType() << "\n";
                }
            }
        }
    }


    board=board_i;
}


void Jeu::resetInsectCount(){
    QueenBee::resetBlanc();
    QueenBee::resetNoir();
    Ant::resetBlanc();
    Ant::resetNoir();
    Beetle::resetBlanc();
    Beetle::resetNoir();
    Grasshopper::resetBlanc();
    Grasshopper::resetNoir();
    //Ladybug::resetBlanc();
    //Ladybug::resetNoir();
    Spider::resetBlanc();
    Spider::resetNoir();
    //Mosquito::resetBlanc();
    //Mosquito::resetNoir();
}
