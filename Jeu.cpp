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

//M�thode pour enregistrer le plateau
void Jeu::enregistrerBoard() {
    std::cout << "Board sauvegard�\n";
    historyStack.push(board);
    std::cout << "Le nombre d'entr�es dans la stack: " << historyStack.size() << std::endl;
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
    std::cout << "2. D�placer un insecte d�j� pos�\n";
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
    int choix;
    bool quitter = false;
    while (!quitter) {

        //Test de victoire du joueur qui vient de jouer (on v�rifie d'abord sur la reine adverse, c'est � dire la reine du joueur qui est sur le point de jouer)
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1) << "\n=========\n";
        //std::cout << "\n=========\nDEBUG : isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) = " << isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1) << "\n=========\n";
        if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1)){
            std::cout <<CYAN<< "Le joueur ";

            // Ici on annonce la victoire du joueur qui vient de jouer (c'est pour cela qu'on n'a pas de +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir)%2==1){ std::cout << WHITE << "blanc" << BLACK; }
            else{ std::cout << "noir"; }
            std::cout <<CYAN<< "a gagne !"<<BLACK<<"\n";
        }
        // On v�rifie maintenant sur la reine du joueur qui vient de jouer, dans le cas o� il s'est fait perdre tout seul
        else if(isQueenSurrounded((compteurDeToursBlanc+compteurDeToursNoir)%2==1)){
            std::cout <<CYAN<< "Le joueur ";

            // Ici on annonce la victoire du joueur qui �tait sur le point de jouer (c'est pour cela qu'on a un +1 dans le calcul du modulo
            if((compteurDeToursBlanc+compteurDeToursNoir+1)%2==1){ std::cout << WHITE << "blanc" << BLACK;}
            else{ std::cout << "noir";}
            std::cout <<CYAN<< "a gagne !"<<BLACK<<"\n";
        }
        else{
            afficherMenu();
            choix = demanderChoix();

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
                    //board.print(std::cout);
                    afficherPartie();
                    break;
                case 4:
                    annulerCoup();
                    std::cout << "Coup annul�\n";
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
                    std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";;
            }
        }
    }
}

// M�thode pour ajouter une case au plateau
void Jeu::ajouterCase() {
    auto [x, y] = demanderCoordonnees();
    board.addSpot(x, y);
    std::cout << "Case ajout�e aux coordonn�es (" << x << ", " << y << ").\n";
}

// M�thode pour ajouter un insecte � une case
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
            std::cout << RED << "Vous n'avez plus d'insecte � poser !!" << BLACK << "\n";
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
                    //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur blanche � la position (0, 0)\n=========\n\n";
                }
                const BoardSpot* spot = board.getSpot(0, 0);
                possibilite.push_back(spot);
            }
            if (color == 0){
                if (board.getSpot(0, 1) == nullptr) {
                    board.addSpot(0, 1);
                    //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur noire � la position (0, 1)\n=========\n\n";
                }
                const BoardSpot* spot = board.getSpot(0, 1);
                possibilite.push_back(spot);
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
            auto [newx, newy] = demanderCoordonnees();
            spot = BoardSpot(newx, newy);
            x = newx;
            y = newy;
            if (!board.est_dans_possibilite(&spot, possibilite)) {
                std::cout  << RED << "Coordonn�es invalides, veuillez r�essayer."<<BLACK<<"\n";
            }
        }while( !board.est_dans_possibilite(&spot, possibilite) );


        board.addInsectToSpot(x, y, insect);
        board.addNullSpot(x,y);

        //std::cout << "\n=========\nDEBUG : Insecte ajout� � la case (" << x << ", " << y << ").\n=========\n\n";
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
        // TO DO : incr�menter les compteurs des autres insectes
        else{ std::cout << RED <<"le choix n'est pas valide, mais �a ne devrait pas arriver ici... (ajout du nombre d'insectes pos�s dans Jeu::ajouterInsecte)"<<BLACK<<"/n"; }

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
                auto [oldX, oldY] = demanderCoordonnees();
                spot = board.getSpot(oldX, oldY);
                x = oldX;
                y = oldY;
                std::cout<< "debug : je viens de demander les coordonnees";
            }while( !board.est_dans_possibilite(spot, piece));
            //std::cout << "\n=========\nDEBUG : j'arrive dans la partie d'apr�s.\n=========\n\n";

            std::cout<< "debug : je viens de sortir du while";
            //appel de moov pour retourner les cases possibles (et potentiellement v�rifier s'il y a bien un insecte sur cette case)
            std::vector <const BoardSpot*> possibilite = spot->getInsect()->moov(x, y, board);



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
                    int newX, newY;
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
        auto [x, y] = demanderCoordonnees();
        board.deleteSpot(x, y);
        std::cout << "Case supprim�e aux coordonn�es (" << x << ", " << y << ").\n";
    }
    catch (const SetException& e){
        std::cout << e.getMessage() <<"\n";
    }
}

void Jeu::annulerCoup(){
    std::cout << "Le nombre d'entr�es dans la stack: " << historyStack.size() << std::endl;
    if (nbRetoursEnArriere<=0){
        std::cout << "Vous avez atteint le nombre maximum de retours en arriere de la partie.\n";
        return;
    }
    if (historyStack.size() == 1) {
        std::cout << "Vous �tes d�j� au d�but de la partie.\n";
        return;
    }

    historyStack.pop();
    majListeInsect(historyStack.top());
    nbRetoursEnArriere--;
    decCompteur();

}

//fonction qui permet de mettre � jour le tour du joueur;
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
void Jeu::saveGame(std::stack<Board> boardStack) {
    try {
        const std::string& filename = "boards.sauv";
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing.");
        }

        outFile << getnbRetoursEnArriere() << "\n"; // Write the number of retours en arrière

        while (!boardStack.empty()) {
            Board board = boardStack.top();
            boardStack.pop();

            outFile << board.getNb() << "\n"; // Write the number of spots
            for (size_t i = 0; i < board.getNb(); ++i) {
                BoardSpot spot = board.getSpotIndex(i);

                auto coordinates = spot.getCoordinates();
                outFile << coordinates.first << " " << coordinates.second << " ";

                if (spot.hasInsect()) {
                    Insect* insect = spot.getInsect();
                    outFile << insect->getType() << " " << insect->getColor() << "\n";
                } else {
                    outFile << "none\n"; // No insect
                }
            }
        }
        std::cout << "Game saved successfully!\n";
        outFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error saving boards: " << e.what() << std::endl;
    }
}


//Méthode pour reload la partie
std::stack<Board> Jeu::reloadGame() {
    try {
        createInsects();
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
        setnbRetoursEnArriere(nb_retours);

        std::stack<Board> boardStack;

        while (true) {
            size_t nb;
            inFile >> nb;
            if (inFile.eof()) {
                //std::cout << "End of file reached. No more boards to read.\n";
                break;
            }
            if (inFile.fail()) {
                throw std::runtime_error("Failed to read the number of spots.");
            }

            Board board;

            for (size_t i = 0; i < nb; ++i) {
                int x, y;
                inFile >> x >> y;
                if (inFile.fail()) {
                    throw std::runtime_error("Failed to read spot coordinates.");
                }

                BoardSpot spot(x, y);  // Create the spot using x, y as coordinates
                board.addSpot(x, y);   // Add the spot to the board

                std::string insectType;
                inFile >> insectType;
                if (inFile.fail()) {
                    throw std::runtime_error("Failed to read insect type.");
                }


                if (insectType != "none") {
                    int color;
                    inFile >> color;
                    if (inFile.fail()) {
                        throw std::runtime_error("Failed to read insect color.");
                    }

                    Insect* insect = nullptr;
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

                    if (insect) {
                        insect->setColor(color);
                        spot.setInsect(insect);
                        board.addInsectToSpot(x, y, insect);  // Place insect in the spot
                    }
                }
            }

            boardStack.push(board);
        }

        inFile.close();
        std::cout << "Boards charg�s avec succ�s!" << std::endl;

        // Manage turn counters
        int sizeBoardStack = boardStack.size();
        if (sizeBoardStack % 2 == 0) {  // Even
            for (int i = 0; i < (sizeBoardStack / 2); i++) {
                incCompteur(0);
                incCompteur(1);
            }
        } else if (sizeBoardStack % 2 != 0) {  // Odd
            for (int i = 0; i < (sizeBoardStack / 2); i++) {
                incCompteur(0);
                incCompteur(1);
            }
            incCompteur(1);
        }

        //std::cout << "TB:" << compteurDeToursBlanc << "\n";
        //std::cout << "TN:" << compteurDeToursNoir << "\n";
        return boardStack;
    } catch (const std::exception& e) {
        std::cerr << "Erreur au chargement des boards: " << e.what() << std::endl;
    }
    //return std::stack<Board>();  // Return an empty stack on failure
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

//M�thode qui free la liste de tous les instects restants et refait la liste du d�but
//cherche si l'insecte est sur le board, si oui l'enl�ve de la liste
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
                    std::cout << RED << "Probl�me pour l'insect blanc: " << insectOnBoard->getType() << "\n";
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
                    std::cout << RED << "Probl�me pour l'insect noir: " << insectOnBoard->getType() << "\n";
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
        //std::cout<< "\npossibilites de placement : ";
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

    //std::cout<<"\npiecesPosees sur le plateau : ";
    for (const BoardSpot* bs : piecesPosees){
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

    //std::cout << "\nmin_x = " << min_x << "\nmax_x = " << max_x << "\nmin_y = " << min_y << "\nmax_y = " << max_y << "\npriority_min = " << priority_min << "\npriority_max = " << priority_max << "\npriority_of_min_x = " << priority_of_min_x << "\n";

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
                    std::cout << CYAN << "_";
                    possibilite.erase(possibilite.begin());
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

