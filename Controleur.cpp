#include "Controleur.h"

void Controleur::demarrage(){

    int c;

    std::cout << "Voulez-vous recharger la partie précédente ? OUI:1 , NON:0 \n";
    c = demanderChoix();

    while (c != 1 && c != 0) {
        std::cout << RED << "Le choix n'est pas valide." << BLACK << "\n";
        c = demanderChoix();
    }
    if (c == 1)
    {
            std::stack<Board> tempStack;
            std::stack<Board> tempStack1;
            tempStack=jeu.reloadGame();
            while (!tempStack.empty()){
                //Inverser la pile pour l'ordre
                tempStack1.push(tempStack.top());
                tempStack.pop();
            }
            jeu.historyStack=tempStack1;
            jeu.historyStack.top().print(std::cout);
            jeu.majListeInsect(jeu.historyStack.top());
    }
    else {
        // On demande le nom du joueur blanc
        // Ici et pas directement dans la méthode Jeu::demarrerPartie car si jamais on a récupéré une partie,
        // alors on n'a pas besoin de redonner un nom au joueur blanc, on le récupère directement
        std::string nomBlanc;
        std::cout << "Entrez le nom du joueur blanc : ";
        std::cin >> nomBlanc;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        jeu.setJoueurBlanc(nomBlanc);

        int nbRetoursEnArriere;
        int ext;
        std::cout <<"creation d'une nouvelle partie\n";
        std::cout << "Nombre maximal de retours en arrière : \n";
        nbRetoursEnArriere = demanderChoix();
        jeu.setNbRetoursEnArriere(nbRetoursEnArriere);
        std::cout << "Parametrer extension : OUI:1 , NON:0 \n";
        ext = demanderChoix();

        while(ext != 1 && ext != 0){
            std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
            ext = demanderChoix();
        }


        if (ext==1)
        {
            std::cout << "souhaitez vous ajouter la coccinelle ? OUI:1 , NON:0 \n";
            ext = demanderChoix();

            while(ext != 1 && ext != 0){
                std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
                ext = demanderChoix();
                }


            if(ext == 1)
            {
                jeu.addType([](){return new Ladybug;},Ladybug::getMax());
            }

            std::cout<< "souhaitez vous ajouter le moustique ? OUI:1 , NON:0 \n";
            ext = demanderChoix();

            while(ext != 1 && ext != 0){
                std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
                ext = demanderChoix();
                }

            if(ext == 1)
            {
                jeu.addType([](){return new Mosquito;},Mosquito::getMax());
            }
        }





    jeu.createInsects();

    }

    jeu.demarrerPartie();
}
