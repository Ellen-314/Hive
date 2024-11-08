#include "ant.h"
#include "Board.h"

const unsigned int Ant::Max =3;
unsigned int Ant::poseBlanc = 0;
unsigned int Ant::poseNoir = 0;

std::vector<const BoardSpot*> Ant::moov(int x, int y, const Board& board){
std::vector <const BoardSpot*> possibilite;
std::queue <const BoardSpot*> Averifier;//queue permet de creer FIFO
std::set <const BoardSpot*> verifie; //set peremet le tri et l'unicité des éléments
const BoardSpot* Spotfourmi = board.getSpot(x, y);

Averifier.push(Spotfourmi); //push l'ajoute à la fin
verifie.insert(Spotfourmi);// ajoute uniquement si il n'est pas déjà dans la liste

 while (!Averifier.empty()) {
        const BoardSpot* currentSpot = Averifier.front(); //front permet d'acceder au premier element ajouté à la FIFO
        Averifier.pop();//on retire l'élement qu'on est en train de verifier de la liste à verifier

        //on cree le vecteur voisins qui repertorie les voisins sans insects autour de la position à verifier
        std::vector<const BoardSpot*> voisins = board.voisinsNull(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
        );

        for (size_t i = 0; i < voisins.size(); i++) {
            // visite.find(voisins[i]) renvoie visite.end() uniquement si le voisin n'a pas déjà été visité
            if (verifie.find(voisins[i]) == verifie.end()) {
                int surroundingInsects = board.trouverVoisinsInsects(
                    voisins[i]->getCoordinates().first,
                    voisins[i]->getCoordinates().second
                ).size(); //surrondingInsects indique combien d'insects il y a autour de l'emplacement
                        if (surroundingInsects < 5) {// si il y a plus de 5 insects autour de l'emplacement la fourmi ne peut pas y acceder
                            possibilite.push_back(voisins[i]);
                            Averifier.push(voisins[i]);
                            verifie.insert(voisins[i]);
                        }
                    }
        }
    }
    return possibilite;
}
