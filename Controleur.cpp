#include "Controleur.h"

void Controleur::demarrage(){

    int c;

    std::cout<<"Voulez-vous recharger la partie précédente ? 1 pour oui\ 0 pour non \n";
    c = demanderChoix();

            while(c != 1 && c != 0){
                std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
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


        int nbRetoursEnArriere;
        int ext;
        std::cout <<"creation d'une nouvelle partie\n";
        std::cout << "Nombre maximal de retours en arrière : \n";
        nbRetoursEnArriere = demanderChoix();
        jeu.setNbRetoursEnArriere(nbRetoursEnArriere);
        std::cout << "Parametrer extension : 1 pour oui\ 0 pour non \n";
        ext = demanderChoix();

            while(ext != 1 && ext != 0){
                std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
                ext = demanderChoix();
                }


        if (ext==1)
        {   std::cout<< "souhaitez vous ajouter la coccinelle ? 1 pour oui\ 0 pour non \n";
            ext = demanderChoix();

            while(ext != 1 && ext != 0){
                std::cout << RED <<"Le choix n'est pas valide."<<BLACK<<"\n";
                ext = demanderChoix();
                }

            if(ext == 1)
            {
                jeu.addType([](){return new Ladybug;},Ladybug::getMax());
            }

            std::cout<< "souhaitez vous ajouter le moustique ? 1 pour oui\ 0 pour non \n";
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
