#include "ant.h"

const unsigned int Ant::Max =3;
unsigned int Ant::poseBlanc = 0;
unsigned int Ant::poseNoir = 0;

std::vector<const BoardSpot*> Ant:: moov(int x, int y, const Board& board)const{
    std::vector <const BoardSpot*> possibilite;
    std::queue <const BoardSpot*> Averifier;//queue permet de creer FIFO
    std::set <const BoardSpot*> verifie; //set peremet le tri et l'unicité des éléments
    const BoardSpot* Spotfourmi = board.getSpot(x, y);


    Averifier.push(Spotfourmi); //push l'ajoute à la fin
    verifie.insert(Spotfourmi);// ajoute uniquement si il n'est pas déjà dans la liste

    while (!Averifier.empty()) {
        const BoardSpot* currentSpot = Averifier.front(); //front permet d'acceder au premier element ajouté à la FIFO
        Averifier.pop();//on retire l'élement qu'on est en train de verifier de la liste à verifier
        //on cree le vecteur voisins qui repertorie les voisins auxquels l'insects à accès
        std::vector<const BoardSpot*> voisins = board.trouverVoisinsGlisseur(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
            );
        for (auto voisin : voisins ){
            if (!(voisin->hasInsect())){

                if (verifie.find(voisin) == verifie.end()) {

                    possibilite.push_back(voisin);

                    Averifier.push(voisin);

                    verifie.insert(voisin);}
            }
        }
    }
    return possibilite;
}


bool Ant::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
