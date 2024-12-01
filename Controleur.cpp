#include "Controleur.h"

void Controleur::demarrage(){

    std::string c;
    std::cout<<"Voulez-vous recharger la partie précédente ? Oui/Non:";
    std::cin>>c;
    if (c=="Oui"||c=="oui"||c=="o"){
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
        std::cout << "Nombre maximal de retours en arrière : ";
        std::cin >> nbRetoursEnArriere;
        jeu.setNbRetoursEnArriere(nbRetoursEnArriere);
    }

    jeu.demarrerPartie();
}
