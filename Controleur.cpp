#include "Controleur.h"

void Controleur::demarrage(){

    int c;
    std::cout<<"Voulez-vous recharger la partie précédente ? Tapez 1 pour reprendre ou 0 pour recommencer: ";
    std::cin>>c;
    if (c==1){
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


        int nbRetoursEnArriere;
        int ext;
        std::cout << "Nombre maximal de retours en arrière : ";
        std::cin >> nbRetoursEnArriere;
        jeu.setNbRetoursEnArriere(nbRetoursEnArriere);
        do {std::cout << "Parametrer extension : 0 oui,  1 non \n";
        std::cin>>ext;} while (ext != 1 && ext != 0);
        if (ext==0)
        {
            do {std::cout<< "souhaitez vous ajouter la coccinelle ? 0 oui, 1 non \n";
            std::cin>>ext;} while (ext != 1 && ext != 0);
            if(ext == 0)
            {
                jeu.addType([](){return new Ladybug;},Ladybug::getMax());
            }

        }

    jeu.createInsects();

    }

    jeu.demarrerPartie();
}
