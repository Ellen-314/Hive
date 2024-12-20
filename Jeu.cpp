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

//Méthode pour enregistrer le plateau, on ajoute la sauvegarde des Boards dans historyStack
void Jeu::enregistrerBoard() {
    std::cout << "Board sauvegardé\n";
    historyStack.push(board);
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




// M�thode pour afficher le menu principal avec les diff�rentes actions disponibles
void Jeu::afficherMenu() const {
    std::cout << "\n=== Menu de Jeu ===\n";
    std::cout << "1. Poser un nouvel insecte sur le plateau\n";
    std::cout << "2. Déplacer un insecte déja posé\n";
    std::cout << "3. Afficher le plateau\n";
    std::cout << "4. Annuler le coup\n";
    std::cout << "5. Sauvegarder la partie\n";
    //if (getHasbot() == 1){ std::cout << "6. Faire jouer l'IA\n"; } // On la fait jouer automatiquement
    std::cout << "0. Quitter\n";
    /*std::cout << "=== Menu de Debug ===\n"; // n'existera pas pendant une partie
    std::cout << "99. Ajouter une case\n";
    std::cout << "98. Supprimer une case\n";*/
    std::cout << "===================\n";
    std::cout << "Tour de "; // Le joueur blanc commence
    if((compteurDeToursBlanc+compteurDeToursNoir+1)%2==0){ std::cout << getJoueurNoir() <<".\n"; }
    else{ std::cout << WHITE << getJoueurBlanc() << BLACK<<".\n"; }
    std::cout << "Entrez votre choix : ";
}

// M�thode pour obtenir de la part l'utilisateur des coordonn�es de la case o� une action doit �tre effectu�e
std::pair<int, int> Jeu::demanderCoordonnees() const {
    int x, y;
    do {
    std::cout << "Entrez les coordonn�es x et y : ";
    std::cin >> x >> y;
    if (std::cin.fail()) {
            // Effacer l'�tat d'erreur
            std::cin.clear();
            // Ignorer le reste de la ligne
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Afficher un message d'erreur
            std::cout << "Entr�e invalide.\n";
        } else {
            // Si tout est valide, sortir de la boucle
            break;
        }}while (true);


    return std::make_pair(x, y);
}


// M�thode principale pour g�rer les interactions utilisateur
void Jeu::demarrerPartie() {

    int num;
    std::cout << "Voulez vous jouer contre un bot ? NON:0 , OUI:1 \n";
    num = demanderChoix();
    while (num != 1 && num != 0) {
        std::cout << RED << "Le choix n'est pas valide." << WHITE << "\n";
        num = demanderChoix();
    }
    //On crée le Bot + on initialise à 1 si on joue contre un bot
    if (num == 1) { setHasbot(1);  setJoueurNoir("IA"); }
    else {
        std::string nomNoir;
        if(getJoueurNoir()=="IA" || getJoueurNoir()==""){
            // Dans le cas où on a récupéré une partie précédemment et où le joueur noir était une IA
            // Ou bien dans le cas où on vient de commencer une nouvelle partie
            std::cout << "Entrez le nom du joueur noir : ";
            std::cin >> nomNoir;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            setJoueurNoir(nomNoir);
        }
    }


    int choix;
    bool quitter = false;

    while (!quitter) {

        //Test de victoire du joueur qui vient de jouer (on v�rifie d'abord sur la reine adverse, c'est � dire la reine du joueur qui est sur le point de jouer)
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) << "\n=========\n";
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) << "\n=========\n";
        if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1)){

            // Ici on annonce la victoire du joueur qui vient de jouer (c'est pour cela qu'on n'a pas de +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir)%2==1){ std::cout << WHITE << getJoueurBlanc() << BLACK; } // Victoire du joueur blanc
            else{ std::cout << getJoueurNoir(); } // Victoire du joueur noir
            std::cout <<CYAN<< " a gagne !"<<BLACK<<"\n";
        }
        // On vérifie maintenant sur la reine du joueur qui vient de jouer, dans le cas où il s'est fait perdre tout seul
        else if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1)){

            // Ici on annonce la victoire du joueur qui était sur le point de jouer (c'est pour cela qu'on a un +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1){ std::cout << WHITE << getJoueurBlanc() << BLACK;} // Victoire du joueur blanc
            else{ std::cout << getJoueurNoir(); } // Victoire du joueur noir
            std::cout <<CYAN<< " a gagne !"<<BLACK<<"\n";
        }
        else{
//            afficherMenu();
//            choix = demanderChoix();
//
//            //ici on force a taper 6 quand c'est à l'IA de jouer
//            while (getHasbot() == 1 && choix != 6 && ((compteurDeToursBlanc + compteurDeToursNoir + 1) % 2 == 0)) {
//                std::cout << RED<< "C'est au tour de l'IA de jouer, veuillez taper 6 \n "<< BLACK<< "\n";
//                afficherMenu();
//                choix = demanderChoix();
//            }
//            while (getHasbot() == 1 && choix == 6 && ((compteurDeToursBlanc + compteurDeToursNoir + 1) % 2 != 0)) {
//                std::cout << RED << "C'est a toi de jouer pas à l'IA, t'as cru contourner le système ? \n " << BLACK << "\n";
//                afficherMenu();
//                choix = demanderChoix();
//            }

            //ici on entre 6 automatiquement quand c'est à l'IA de jouer, s'il y en a une
            if (getHasbot() == 1 && ((compteurDeToursBlanc + compteurDeToursNoir + 1) % 2 == 0)) {
                choix = 6;
            }
            else {
                afficherMenu();
                choix = demanderChoix();
            }

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
                    afficherPartie();
                    break;
                case 4:
                    annulerCoup();
                    std::cout << "Coup annulé\n";
                    std::cout << "Nombre de retours en arriere restants: "<<nbRetoursEnArriere<<"\n";
                    break;
                case 5:
                    saveGame(historyStack);
                    break;
                case 6:
                    // On fait jouer l'IA automatiquement
                    if (getHasbot()==1 && ((compteurDeToursBlanc + compteurDeToursNoir + 1) % 2 == 0) ){ botIsPlayingToWin(); afficherPartie(); }
                    else { std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n"; }
                    break;
                case 99:
                    ajouterCase();
                    break;
                case 98:
                    supprimerCase();
                    break;
                default:
                    std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
            }
        }
    }
}

// M�thode pour ajouter une case au plateau
void Jeu::ajouterCase() {
    std::pair<int, int> coordonnees = demanderCoordonnees();
    int x = coordonnees.first;
    int y = coordonnees.second;
    board.addSpot(x, y);
    std::cout << "Case ajoutée aux coordonnées (" << x << ", " << y << ").\n";
}

// Methode pour ajouter un insecte a une case
void Jeu::ajouterInsecte() {
    try {
        std::cout << "Placement d'un nouvel insecte sur le plateau : joueur ";

        // Joueur blanc commence
        unsigned int color=(compteurDeToursBlanc+compteurDeToursNoir+1)%2;

        // Se fera automatiquement en fonction du tour du joueur
        /*std::cout << "Choisissez la couleur de l'insecte (1 pour blanc, 0 pour noir) : ";
        std::cin >> color;*/

        if(color!=1 && color!=0){ throw JeuException("Couleur choisie incorrecte."); }
        if(color==1){ std::cout << WHITE << getJoueurBlanc() << "\n" << BLACK; }
        else{ std::cout << getJoueurNoir() << "\n"; }
        // Affichage et retour au menu si jamais le joueur n'a plus d'insecte à poser
        if((color==0 && insectsNoir.empty()) || (color==1 && insectsBlanc.empty())) {
            std::cout << RED << "Vous n'avez plus d'insecte � poser !!" << BLACK << "\n";
            return;
        }

        std::cout <<BLACK<< "Voici les insectes que vous pouvez poser :\n";

        if(color==0){ printInsectsNoir(); }
        else{ printInsectsBlanc(); }

        std::vector<const BoardSpot* > possibilite;
        //si c'est le premier pour chaque tour on cree le premier spot pour insecte
        if (((color == 0)&& (Jeu::getCompteurDeToursNoir() == 0))||((color==1)&&(Jeu::getCompteurDeToursBlanc() == 0))){
            //std::cout << "\n=========\nDEBUG : Rentre dans la boucle des conditions\n=========\n\n";
            if (color == 1){
                if (board.getSpot(0, 0)==nullptr){
                    board.addSpot(0, 0);
                    //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur blanche � la position (0, 0)\n=========\n\n";
                }
                const BoardSpot* spot = board.getSpot(0, 0);
                possibilite.push_back(spot);
            }
            if (color == 0){
                possibilite = board.trouverVoisins(0,0);
                }


        }

        if (((color == 1)&& (Jeu::getCompteurDeToursBlanc() != 0))||((color==0)&&(Jeu::getCompteurDeToursNoir() != 0))){
            possibilite = board.possibleplacer(color);
        }

        std::cout<<"Voici vos possibilités de placement : \n";
        //board.afficherpossibilite(possibilite);
        afficherPartie(&possibilite);


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
                std::cout << "Quelle pi�ce souhaitez vous ajouter?  20:revenir au menu\n";
                std::cout << "Entrez votre choix : ";

                choix_insect= demanderChoix();




                if (choix_insect == 20){
                        std::cout << "retour au menu\n";
                        return;}

                else if(color == 1){
                if (choix_insect > -1 && choix_insect<getInsectBlanc().size())
                {
                    insect = getInsectBlancMod()[choix_insect];
                    insect->setColor(1);
                    insectsBlanc.erase(insectsBlanc.begin()+choix_insect);
                    choix_insect= 100;
                }}
                else if (choix_insect >= 0 && choix_insect<getInsectNoir().size())
                {
                    insect = getInsectNoirMod()[choix_insect];
                    insect->setColor(0);
                    insectsNoir.erase(insectsNoir.begin()+choix_insect);
                    choix_insect= 100;
                }


                else{ std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";}


                    }

            while(choix_insect!= 100);

        }

        BoardSpot spot(0, 0);
        int x, y;
        do {
            std::pair<int, int> coordonnees = demanderCoordonnees();
            int newx = coordonnees.first;
            int newy = coordonnees.second;
            spot = BoardSpot(newx, newy);
            x = newx;
            y = newy;
            if (!board.est_dans_possibilite(&spot, possibilite)) {
                std::cout  << RED << "Coordonn�es invalides, veuillez r�essayer."<<BLACK<<"\n";
            }
        }while( !board.est_dans_possibilite(&spot, possibilite) );


        board.addInsectToSpot(x, y, insect);
        board.addNullSpot(x,y);
        // Vérifier la connexité
        if (!board.isConnexe()) {
            std::cout << RED << "Placement annulé : cela romprait la connexité du graphe." << BLACK << "\n";
            board.deleteInsectFromSpot(x, y);
            return;
        }

        //std::cout << "\n=========\nDEBUG : Insecte ajout� � la case (" << x << ", " << y << ").\n=========\n\n";
        incCompteur(color);
        Jeu::enregistrerBoard();

        // On incremente le compte pour le type d'insect en fonction de la couleur
        // En fonction du type de l'insect
        auto it = insectCountUpdate.find(insect->getType());
        if (it != insectCountUpdate.end()) {
            it->second(color);
        } else {
            throw JeuException("Unknown insect type");
        }

    }
    catch (const SetException& e){
        std::cout  << RED << e.getMessage()  << BLACK <<"\n";
    }
    catch (const JeuException& e){
        std::cout  << RED << e.getMessage()  << BLACK <<"\n";
    }
}

// M�thode pour d�placer un insecte, diff�rent de moov dans Insect qui testera les diff�rentes possibilit�s de d�placement
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


            std::vector <const BoardSpot*> piece = board.piecejoueur(color);
            std::cout << "Voici vos pi�ces disponibles sur le plateau : \n";
            board.afficherpossibilite(piece);


            std::cout << "Entrez les coordonn�es de la case dont vous voulez connaitre les possibilit�s d'actions.\n";
            int x, y;
            const BoardSpot* spot = nullptr;
            do {
                std::pair<int, int> coordonnees = demanderCoordonnees();
                int newx = coordonnees.first;
                int newy = coordonnees.second;
                spot = board.getSpot(newx, newy);
                x = newx;
                y = newy;
                // std::cout<< "debug : je viens de demander les coordonnees";
            }while( !board.est_dans_possibilite(spot, piece));
            //std::cout << "\n=========\nDEBUG : j'arrive dans la partie d'apr�s.\n=========\n\n";

            //std::cout<< "debug : je viens de sortir du while";

            //appel de moov pour retourner les cases possibles (et potentiellement v�rifier s'il y a bien un insecte sur cette case)
            std::vector <const BoardSpot*> possibilite = spot->getInsect()->moov(x, y, board);

            // Vérifier la connexité si on déplace la pièce, c'est-à-dire si on la retire du plateau un instant
            Insect* insectOnSpot = spot->getInsect();
            if (insectOnSpot->getcouvert() == nullptr){
                board.deleteInsectFromSpot(x,y); // On retire temporairement l'insecte (on simule un début de déplacement)
                if (!board.isConnexe()) { possibilite.clear(); } // Si déplacer la pièce casse la ruche alors on empêche toute possibilité de déplacement
                board.addInsectToSpot(x,y,insectOnSpot);  // On replace l'insecte à sa place
            }

            int newX, newY;
            std::vector <const BoardSpot*> testpossibilite = possibilite;

            // Vérifier la connexité pour chaque possiblite
            for (size_t i = 0; i < possibilite.size(); i++){
                std::cout << "i = " << i << "\n";
                const BoardSpot* spot = possibilite[possibilite.size()-1-i];
                newX = spot->getCoordinates().first;
                newY = spot->getCoordinates().second;
                board.moovInsect(x, y, newX, newY);

                if (!board.isConnexe()) {
                    // std::cout << RED << "Déplacement annulé : cela romprait la connexité du graphe." << BLACK << "\n";
                    testpossibilite.erase (testpossibilite.begin()+possibilite.size()-1-i);
                }

                board.moovInsect(newX, newY, x, y); // Annuler le déplacement temporaire
            }

            possibilite = testpossibilite;

            // On v�fifie qu'il y a bien des possibilit�s avant de proposer un d�placement
            if(!possibilite.empty()){
                std::cout << "Voici les possibilités de déplacement de votre pièce\n";
                //board.afficherpossibilite(possibilite);
                afficherPartie(&possibilite);

                std::cout <<"Entrez 1 pour placer la pi�ce � l'un des emplacements donn�s.\n";}

            if (possibilite.empty()){std::cout<<"cette pi�ce n'a pas de possibilit� de d�placement\n";}

                std::cout <<"Entrez 2 pour voir les mouvements possibles d'une autre pi�ce.\n";
                std::cout <<"Entrez 3 pour retourner au menu.\n";
                std::cout <<"Entrez votre choix : ";
                //ou autre
                choix = demanderChoix();

                if(choix == 1 && !possibilite.empty()){
                    std::cout << "Entrez les coordonn�es de la case de destination.\n";
                    const BoardSpot* spot2 = nullptr;
                    do {
                        std::pair<int, int> coordonnees = demanderCoordonnees();
                        newX = coordonnees.first;
                        newY = coordonnees.second;
                        spot2 = board.getSpot(newX, newY);

                        if (!board.est_dans_possibilite(spot2, possibilite)) {
                            std::cout  << RED << "Coordonn�es invalides, veuillez r�essayer."<<BLACK<<"\n";
                        }
                    }while( !board.est_dans_possibilite(spot2, possibilite) );

                    board.moovInsect(x, y, newX, newY);

                    //TODO gerer les probl�mes avec le scarab�
                    board.addNullSpot(newX,newY);
                    board.deleteNullSpot(x,y);

                    //std::cout << "\n=========\nDEBUG : Insecte d�plac� de (" << oldX << ", " << oldY << ") � (" << newX << ", " << newY << ").\n=========\n\n";
                    incCompteur(color);
                    choix = 3;//TO DO: ameliorer pour que �a passe au tour de l'autre direct
                }


    }while(choix!=3);
        Jeu::enregistrerBoard();
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

// M�thode pour supprimer une case du plateau
void Jeu::supprimerCase() {
    try{
        std::pair<int, int>coordonnees = demanderCoordonnees();
        int x = coordonnees.first;
        int y = coordonnees.second;
        board.deleteSpot(x, y);
        //std::cout << "Case supprim�e aux coordonn�es (" << x << ", " << y << ").\n";
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

//Méthode qui permet de revenir en arrière en supprimant la dernière entrée de history stack
void Jeu::annulerCoup(){
    std::cout << "Le nombre d'entrées dans la stack: " << historyStack.size() << std::endl;
    if (nbRetoursEnArriere<=0){
        std::cout << "Vous avez atteint le nombre maximum de retours en arriere de la partie.\n";
        return;
    }
    //Si on est déja au début de la partie, pas de retours en arrière possibles
    if (historyStack.size() == 1) {
        std::cout << "Vous êtes déjà au début de la partie.\n";
        return;
    }

    historyStack.pop();
    majListeInsect(historyStack.top());
    nbRetoursEnArriere--;
    decCompteur();

}

//fonction qui permet de mettre à jour le tour du joueur;
void Jeu::incCompteur(bool color){
if (color == 1)   Jeu::ajouterCompteurDeToursBlanc();
if (color == 0)   Jeu::ajouterCompteurDeToursNoir();
}

//fonction qui permet de décrémenter les compteurs pour l'annulation
void Jeu::decCompteur(){
    if (compteurDeToursBlanc>compteurDeToursNoir) enleverCompteurDeToursBlanc();
    else enleverCompteurDeToursNoir();
}

//Méthode pour sauvegarder la partie dans un fichier externe, ici un .sauv pour s'assurer de l'unicité du fichier
void Jeu::saveGame(std::stack<Board> boardStack) {
    try {
        const std::string& filename = "boards.sauv";
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing.");
        }

        outFile << getnbRetoursEnArriere() << "\n"; // Ecriture du nombre de retours en arrière
        outFile << getJoueurBlanc() << "\n"; // Ecriture du nom du joueur blanc
        outFile << getJoueurNoir() << "\n"; // Ecriture du nom du joueur noir

        while (!boardStack.empty()) {
            Board board = boardStack.top();
            boardStack.pop();

            outFile << board.getNb() << "\n"; // Ecriture du nombre de spots
            for (size_t i = 0; i < board.getNb(); ++i) {
                BoardSpot spot = board.getSpotIndex(i);

                std::pair<int, int> coordinates = spot.getCoordinates();
                outFile << coordinates.first << " " << coordinates.second << " "; //Ecriture des coordonnées

                if (spot.hasInsect()) {
                    Insect* insect = spot.getInsect();
                    outFile << insect->getType() << " " << insect->getColor() << "\n"; //Ecriture du type d'insects

                    // Ajout de l'insecte couvert par le précédent tant qu'il y en a (par exemple : cas d'un scarabé sur un scarabé sur un scarabé sur une fourmi)
                    while (insect->getcouvert() != nullptr){
                        insect = insect->getcouvertModify();
                        outFile << coordinates.first << " " << coordinates.second << " "; //Ecriture des coordonnées
                        outFile << insect->getType() << " " << insect->getColor() << "\n"; //Ecriture du type d'insects
                    }

                } else {
                    outFile << "none\n"; // Si pas d'insects
                }
            }
        }
        std::cout << "Game saved successfully!\n";
        outFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error saving boards: " << e.what() << std::endl;
    }
}


//Méthode pour reload la partie à partir d'un ficher externe .sauv
std::stack<Board> Jeu::reloadGame() {
    try {
        createInsects();
        const std::string& filename = "boards.sauv";
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Failed to open file for reading.");
        }

        int nb_retours;
        inFile >> nb_retours; //Lecture du nombre de retours en arrière
        if (inFile.fail()) {
            throw std::runtime_error("Failed to read number of retours.");
        }
        setnbRetoursEnArriere(nb_retours);

        std::string nomBlanc; std::string nomNoir;
        inFile >> nomBlanc; // Lecture du nom du joueur Blanc
        if (inFile.fail()) {
            throw std::runtime_error("Failed to read name of white player.");
        }
        setJoueurBlanc(nomBlanc);

        inFile >> nomNoir; // Lecture du nom du joueur Noir
        if (inFile.fail()) {
            throw std::runtime_error("Failed to read name of black player.");
        }
        setJoueurNoir(nomNoir);

        std::stack<Board> boardStack;

        while (true) {
            size_t nb;
            inFile >> nb; //Lecture du nombre de spots
            if (inFile.eof()) {
                //std::cout << "End of file reached. No more boards to read.\n";
                break;
            }
            if (inFile.fail()) {
                throw std::runtime_error("Failed to read the number of spots.");
            }

            Board board;

            // Mise en place de oldx et oldy pour vérifier si les coordonnées de l'insecte précédent ne sont pas les mêmes que l'actuel
            // C'est-à-dire pour vérifier le cas où un insecte était sur un autre (type scarabé)
            int x, y;
            int oldx, oldy;
            for (size_t i = 0; i < nb; ++i) {
                inFile >> x >> y; //Lecture des coordonnées
                if (inFile.fail()) {
                    throw std::runtime_error("Failed to read spot coordinates.");
                }

                std::string insectType;
                inFile >> insectType; //Lecture du type d'insect
                if (inFile.fail()) {
                    throw std::runtime_error("Failed to read insect type.");
                }

                // Création d'un pointeur sur un potentiel insecte (utile pour la suite)
                Insect* insect = nullptr;
                if (insectType != "none") {
                    int color;
                    inFile >> color; //Lecture de l'appartenance à quel joueur c'est
                    if (inFile.fail()) {
                        throw std::runtime_error("Failed to read insect color.");
                    }


                    if (insectType == "ant") {
                        insect = new Ant();
                    } else if (insectType == "queenbee") {
                        insect = new QueenBee();
                    } else if (insectType == "beetle") {
                        insect = new Beetle();
                    } else if (insectType == "grasshopper") {
                        insect = new Grasshopper();
                    } else if (insectType == "spider") {
                        insect = new Spider();
                    }
                    else if (insectType == "ladybug") {
                        insect = new Ladybug();
                    } else if (insectType == "mosquito") {
                        insect = new Mosquito();
                    }
                    insect->setColor(color);
                }

                // Gestion du cas où l'insecte actuel était couvert par un autre insecte
                // (impossible pour le premier insecte du tableau, d'où le i!=0)
                if (insect!=nullptr && i!=0 && x==oldx && y==oldy){
                    Insect* insectcovering = board.getSpot(x,y)->getInsect();

                    // Gestion du cas où plusieurs insectes sont couverts les uns sur les autres
                    // (par exemple : cas d'un scarabé sur un scarabé sur un scarabé sur une fourmi)
                    while (insectcovering->getcouvert()!=nullptr){
                        insectcovering = insectcovering->getcouvertModify();
                    }

                    insectcovering->setInsectUnder(insect);

                    // On décrémente car l'insecte couvert n'est pas sur une nouvelle case du plateau mais bien une qui a déjà été créee
                    i--;
                }
                // S'il n'y a pas d'insecte sur la case
                // ou bien que l'insecte n'est pas couvert par un autre
                else{
                    BoardSpot spot(x, y);  // Création des coordonnées
                    board.addSpot(x, y);   // Ajout du spot au board

                    // Dans le cas où il y a un insecte, on l'ajoute au spot
                    if (insect!=nullptr) {
                        spot.setInsect(insect);
                        board.addInsectToSpot(x, y, insect);  // Place l'insect dans le spot
                    }
                }

                // On récupère les coordonnées du spot actuel pour évaluer
                // dans la prochaine itération le cas où un insecte est couvert par le précédent
                oldx=x;
                oldy=y;
            }

            boardStack.push(board);
        }

        inFile.close();
        std::cout << "Boards chargés avec succès!" << std::endl;

        //Gestion du tour des joueurs
        int sizeBoardStack = boardStack.size();
        if (sizeBoardStack % 2 == 0) {  // Si pair
            for (int i = 0; i < (sizeBoardStack / 2); i++) {
                incCompteur(0);
                incCompteur(1);
            }
        } else if (sizeBoardStack % 2 != 0) {  // si impair
            for (int i = 0; i < (sizeBoardStack / 2); i++) {
                incCompteur(0);
                incCompteur(1);
            }
            incCompteur(1);
        }

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

//M�thode pour free les instects
void Jeu::freeListeInsect(std::vector<Insect*>& liste_i) {
    for (auto& i : liste_i) {
        delete i;
        i = nullptr;
    }
    liste_i.clear();
}

//M�thode pour cr�er une liste de tous les insects Blancs
std::vector<Insect*> Jeu::createInsectsB() {
            for (const auto& insectInfo : insectTypes) {
            for (unsigned int i = 0; i < insectInfo.second; i++) {
                // Noir
                Insect* blanc = insectInfo.first();
                blanc->setColor(true);
                insectsBlanc.push_back(blanc);
            }
        }

    return insectsBlanc; // Return the vector
}

//M�thode pour cr�er une liste de tous les insects Noirs
std::vector<Insect*> Jeu::createInsectsN() {

            for (const auto& insectInfo : insectTypes) {
            for (unsigned int i = 0; i < insectInfo.second; i++) {
                // Noir
                Insect* noir = insectInfo.first();
                noir->setColor(false);
                insectsNoir.push_back(noir);
            }
        }

    return insectsNoir; // Return the vector
}

//Méthode qui free la liste de tous les instects restants et refait la liste du début
//cherche si l'insecte est sur le board, si oui l'enlève de la liste
void Jeu::majListeInsect(Board& board_i) {
    // Free les listes d'insects
    freeListeInsect(insectsBlanc);
    freeListeInsect(insectsNoir);

    // On recrée les insects
    insectsBlanc = createInsectsB();
    insectsNoir = createInsectsN();

    resetInsectCount();

    // On check le board et on met à jour
    for (size_t i = 0; i < board_i.getNb(); i++) {
        const BoardSpot& spot = board_i.getSpotIndex(i);
        if (spot.hasInsect()) {
            Insect* insectOnBoard = spot.getInsect();

            // Boucle pour référencer l'insecte actuel et aussi tous les insectes qu'il couvre
            // (Récupération de tous les insectes couverts)
            while (insectOnBoard!=nullptr){
                bool color = insectOnBoard->getColor();
                if (color) { // Blanc
                    // On retire l'insecte de `insectsBlanc` si on le trouve
                    auto it = std::find_if(insectsBlanc.begin(), insectsBlanc.end(),
                                           [&insectOnBoard](const Insect* insect) {
                                               return insect->getType() == insectOnBoard->getType();
                                           });

                    if (it != insectsBlanc.end()) {
                        insectsBlanc.erase(it);

                        // On incremente le compte pour le type d'insect des blancs
                        // En fonction du type de l'insect
                        auto it = insectCountUpdate.find(insectOnBoard->getType());
                        if (it != insectCountUpdate.end()) {
                            it->second(color);
                        } else {
                            throw JeuException("Unknown insect type");
                        }

                    } else {
                        std::cout << RED << "Probl�me pour l'insect blanc: " << insectOnBoard->getType() << "\n";
                    }

                }
                else { // Noir
                    // On retire l'insecte de `insectsNoir` si on le trouve
                    auto it = std::find_if(insectsNoir.begin(), insectsNoir.end(),
                                           [&insectOnBoard](const Insect* insect) {
                                               return insect->getType() == insectOnBoard->getType();
                                           });

                    if (it != insectsNoir.end()) {

                        insectsNoir.erase(it);

                        // On incremente le compte pour le type d'insect des noirs
                        // En fonction du type de l'insect
                        auto it = insectCountUpdate.find(insectOnBoard->getType());
                        if (it != insectCountUpdate.end()) {
                            it->second(color);
                        } else {
                            throw JeuException("Unknown insect type");
                        }

                    } else {
                        std::cout << RED << "Problème pour l'insect noir: " << insectOnBoard->getType() << "\n";
                    }
                }

                // On passe à l'insecte couvert (s'il n'y en a pas, alors la boucle s'arrêtera)
                insectOnBoard = insectOnBoard->getcouvertModify();
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
    Ladybug::resetBlanc();
    Ladybug::resetNoir();
    Spider::resetBlanc();
    Spider::resetNoir();
    Mosquito::resetBlanc();
    Mosquito::resetNoir();
}

int demanderChoix (){
    int c;
    do{
std::cin>> c;
if (std::cin.fail())
{   std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
else  {std::cin.ignore(1000, '\n');
        return c;}
} while (true);
}

void Jeu::afficherPartie(std::vector<const BoardSpot*>* ptpossibilite){
    std::vector<const BoardSpot*> piecesPoseesBlanc = board.piecejoueur(true);
    std::vector<const BoardSpot*> piecesPoseesNoir = board.piecejoueur(false);
    std::vector<const BoardSpot*> piecesPosees;
    piecesPosees.insert(piecesPosees.end(), piecesPoseesBlanc.begin(), piecesPoseesBlanc.end());
    piecesPosees.insert(piecesPosees.end(), piecesPoseesNoir.begin(), piecesPoseesNoir.end());
    std::sort(piecesPosees.begin(),piecesPosees.end(), compBSco);
    std::reverse(piecesPosees.begin(),piecesPosees.end());


    // Car on a placé la première pièce en (0;0).
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;

    int priority_min = 0;
    int priority_max = 0;
    int priority_of_min_x = 0;


    int x; int y; int priority;

    std::vector<const BoardSpot*> possibilite;
    if(ptpossibilite!=nullptr){
        possibilite = *ptpossibilite;
        std::sort(possibilite.begin(),possibilite.end(), compBSco);
        std::reverse(possibilite.begin(),possibilite.end());
        //std::cout << RED << "\npossibilites de placement : ";
        for (const BoardSpot* bs : possibilite){
            //bs->print(std::cout);
            x=bs->getCoordinates().first;
            y=bs->getCoordinates().second;
            priority = 2*y-x;

            if (x < min_x) {
                min_x = std::min(x, min_x);
                priority_of_min_x = priority;
            }
            max_x = std::max(x,max_x);
            min_y = std::min(y, min_y);
            max_y = std::max(y, max_y);
            priority_min = std::min(priority, priority_min);
            priority_max = std::max(priority, priority_max);
        }
    }

    //std::cout<< "\n=========\nDEBUG : <<"\npiecesPosees sur le plateau : ";
    for (const BoardSpot* bs : piecesPosees){
        // bs->print(std::cout);
        x=bs->getCoordinates().first;
        y=bs->getCoordinates().second;
        priority = 2*y-x;

        if (x < min_x) {
            min_x = std::min(x, min_x);
            priority_of_min_x = priority;
        }
        max_x = std::max(x,max_x);
        min_y = std::min(y, min_y);
        max_y = std::max(y, max_y);
        priority_min = std::min(priority, priority_min);
        priority_max = std::max(priority, priority_max);
    }
//    std::cout << "\n=========\n";

    //std::cout << "\n=========\nDEBUG : << "\nmin_x = " << min_x << "\nmax_x = " << max_x << "\nmin_y = " << min_y << "\nmax_y = " << max_y << "\npriority_min = " << priority_min << "\npriority_max = " << priority_max << "\npriority_of_min_x = " << priority_of_min_x << "\n" << "\n=========\n";

    bool spot_vide = true;

    std::cout << "\n\n\n";

    for(int p = priority_max; p>=priority_min; p--){
        //std::cout << RED << "priority : " << p << "\t";
        if(std::abs(p%2) == std::abs(priority_of_min_x%2)) std::cout << "        ";
        for (int x=min_x; x<=max_x; x++){
            if ((std::abs(x%2)==std::abs(min_x%2) && std::abs(p%2) == std::abs(priority_of_min_x%2))
                || (std::abs(x%2)!=std::abs(min_x%2) && std::abs(p%2) != std::abs(priority_of_min_x%2))){
                if (ptpossibilite!=nullptr
                    && !possibilite.empty()
                    && 2 * possibilite.front()->getCoordinates().second - possibilite.front()->getCoordinates().first == p
                    && possibilite.front()->getCoordinates().first == x){
                    y = possibilite.front()->getCoordinates().second;
                    spot_vide=false;

                    // Dans le cas d'un affichage de possibilité de déplacement recouvrant une pièce
                    if (!piecesPosees.empty()
                        && piecesPosees.front()->getCoordinates().first == possibilite.front()->getCoordinates().first
                        && piecesPosees.front()->getCoordinates().second == possibilite.front()->getCoordinates().second){
                        if(piecesPosees.front()->getInsect()->getColor()) std::cout << WHITE;
                        else std::cout << BLACK;
                        std::cout << piecesPosees.front()->getInsect()->getType().front() << CYAN;
                        piecesPosees.erase(piecesPosees.begin());
                    }
                    else { std::cout << CYAN << "_"; }

                    //Pour patch les cas où une même possibilité apparaît 2 fois dans la liste des possibilités (déjà arrivé avec le déplacement du moustique)
                    while (!possibilite.empty() && possibilite.front()->getCoordinates().first == x && possibilite.front()->getCoordinates().second == y){
                        possibilite.erase(possibilite.begin());
                    }
                }
                else if (!piecesPosees.empty()
                         && 2 * piecesPosees.front()->getCoordinates().second - piecesPosees.front()->getCoordinates().first == p
                         && piecesPosees.front()->getCoordinates().first == x){
                    y = piecesPosees.front()->getCoordinates().second;
                    spot_vide=false;
                    if(piecesPosees.front()->getInsect()->getColor()) std::cout << WHITE;
                    else std::cout << BLACK;
                    std::cout << piecesPosees.front()->getInsect()->getType().front();
                    piecesPosees.erase(piecesPosees.begin());
                }

                if(spot_vide) std::cout << "          ";
                else{
                    std::cout << "(";

                    if (x>=0) std::cout << " ";
                    std::cout  << x;
                    if (x > -10 && x < 10) std::cout << " ";

                    std::cout << ";";

                    if (y>=0) std::cout << " ";
                    std::cout  << y;
                    if (y > -10 && y < 10) std::cout << " ";

                    std::cout << ")" << BLACK;

                    spot_vide=true;
                }

                std::cout << "      ";
            }else if( x == min_x ) std::cout << "          " << "      ";
        }
        std::cout << "\n";
    }

    std::cout << "\n\n\n";
}



//======================== METHODES DU BOT ==================================//

void Jeu::botIsPlayingToWin() {
    unsigned int color = 0; // Le bot est toujours joueur noir

    // Si toutes les pièces sont posées, le bot doit déplacer une pièce
    if (insectsNoir.empty()) {
        std::cout << "Le bot n'a plus d'insectes à poser. Il déplace une pièce.\n";
        botMoveInsect();
        ++compteurDeToursNoir;
        enregistrerBoard();
        return;
    }

    // Si la reine n'est pas posée ou si le bot décide de déplacer une pièce (25% de chance)
    if (!QueenBee::estPasAuMax(color) && (rand() % 2 == 0)) {
        std::cout << "Le bot décide de déplacer une pièce.\n";
        botMoveInsect();
        ++compteurDeToursNoir;
        enregistrerBoard();
        return;
    }

    std::cout << "Le bot décide de poser une nouvelle pièce.\n";

    int choix_insect = rand() % insectsNoir.size();
    Insect* insect = insectsNoir[choix_insect];
    insectsNoir.erase(insectsNoir.begin() + choix_insect);

    std::vector<const BoardSpot*> possibilite = board.possibleplacer(color);

    // Forcer la pose de la reine au premier tour
    if (Jeu::getCompteurDeToursNoir() == 0) {

        // Rechercher la reine dans les insectes
        Insect* queenBee = nullptr;
        for (size_t i = 0; i < insectsNoir.size(); ++i) {
            if (insectsNoir[i]->getType() == "queenbee") {
                queenBee = insectsNoir[i];
                insectsNoir.erase(insectsNoir.begin() + i);
                break;
            }
        }

        if (queenBee) {
            // Ajouter la reine à sa position (0,1)
            if (board.getSpot(0, 1) == nullptr) {
                board.addSpot(0, 1);
            }
            const BoardSpot* spot = board.getSpot(0, 1);

            int x = spot->getCoordinates().first;
            int y = spot->getCoordinates().second;
            board.addInsectToSpot(x, y, queenBee);
            board.addNullSpot(x, y);

            std::cout << "Le bot a placé sa reine à la position (" << x << ", " << y << ").\n";

            // Mettre à jour l'état de la reine posée
            QueenBee::ajouterNoir();

            ++compteurDeToursNoir;
            enregistrerBoard();
            return;
        }
        else {
            std::cerr << "Erreur : la reine n'a pas été trouvée parmi les pièces restantes !\n";
            return;
        }
    }


    int choix_position = rand() % possibilite.size();
    const BoardSpot* spot = possibilite[choix_position];
    int x = spot->getCoordinates().first;
    int y = spot->getCoordinates().second;

    board.addInsectToSpot(x, y, insect);
    board.addNullSpot(x, y);

    std::cout << "Le bot a placé un " << insect->getType()
        << " à la position (" << x << ", " << y << ").\n";

    ++compteurDeToursNoir;
    enregistrerBoard();


}

void Jeu::botMoveInsect() {
    unsigned int color = 0; // Le bot est toujours joueur noir

    try {
        // Vérifie si le bot a des pièces à déplacer
        if (board.piecejoueur(color).empty() || QueenBee::estPasAuMax(color)) {
            std::cout << "Le bot ne peut pas déplacer de pièce.\n";
            return;
        }

        std::vector<const BoardSpot*> pieces = board.piecejoueur(color);
        bool pieceMoved = false;

        while (!pieceMoved && !pieces.empty()) {
            // Choisir une pièce aléatoire parmi celles disponibles
            int randomIndex = rand() % pieces.size();
            const BoardSpot* selectedPiece = pieces[randomIndex];

            if (selectedPiece == nullptr || selectedPiece->getInsect() == nullptr) {
                pieces.erase(pieces.begin() + randomIndex); // Retirer la pièce invalide
                continue;
            }

            int x = selectedPiece->getCoordinates().first;
            int y = selectedPiece->getCoordinates().second;

            std::vector<const BoardSpot*> possibilites = selectedPiece->getInsect()->moov(x, y, board);

            if (!possibilites.empty()) {
                int randomDestIndex = rand() % possibilites.size();
                const BoardSpot* destination = possibilites[randomDestIndex];

                int destX = destination->getCoordinates().first;
                int destY = destination->getCoordinates().second;

                board.moovInsect(x, y, destX, destY);

                // Vérification de la connexité
                if (board.isConnexe()) {
                    std::cout << "Le bot a déplacé une pièce de (" << x << ", " << y << ") à (" << destX << ", " << destY << ").\n";

                    enregistrerBoard();
                    pieceMoved = true;
                }
                else {
                    std::cout << "Déplacement annulé : cela romprait la connexité du graphe.\n";
                    // Annuler le déplacement
                    board.moovInsect(destX, destY, x, y);
                }
            }

            // Si aucune possibilité ou échec, retirer la pièce de la liste
            if (!pieceMoved) {
                pieces.erase(pieces.begin() + randomIndex);
            }

            // Vérification si toutes les pièces ont été essayées
            if (pieces.empty() && !pieceMoved) {
                std::cout << "Le bot ne peut déplacer aucune pièce valide.\n";
                return;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur dans le déplacement par le bot : " << e.what() << "\n";
    }
}

