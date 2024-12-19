#include "ant.h"

const unsigned int Ant::Max =3;
unsigned int Ant::poseBlanc = 0;
unsigned int Ant::poseNoir = 0;

//std::vector<const BoardSpot*> Ant::moov(int x, int y, const Board& board)const{
//    std::vector <const BoardSpot*> possibilite;
//    std::queue <const BoardSpot*> Averifier;//queue permet de creer FIFO
//    std::set <const BoardSpot*> verifie; //set peremet le tri et l'unicité des éléments
//    const BoardSpot* Spotfourmi = board.getSpot(x, y);
//
//    Averifier.push(Spotfourmi); //push l'ajoute à la fin
//    verifie.insert(Spotfourmi);// ajoute uniquement si il n'est pas déjà dans la liste
//
//    while (!Averifier.empty()) {
//            const BoardSpot* currentSpot = Averifier.front(); //front permet d'acceder au premier element ajouté à la FIFO
//            Averifier.pop();//on retire l'élement qu'on est en train de verifier de la liste à verifier
//
//            //on cree le vecteur voisins qui repertorie les voisins sans insects autour de la position à verifier
//            std::vector<const BoardSpot*> voisins = board.trouverVoisinsGlisseur(
//                currentSpot->getCoordinates().first,
//                currentSpot->getCoordinates().second
//            );
//
//            for (size_t i = 0; i < voisins.size(); i++) {
//            // Vérifie si le voisin n'a pas déjà été vérifié
//            if (verifie.find(voisins[i]) == verifie.end()) {
//                possibilite.push_back(voisins[i]);    // Ajoute le voisin à la liste des possibilités
//                Averifier.push(voisins[i]);          // Ajoute le voisin à la liste à vérifier
//                verifie.insert(voisins[i]);          // Marque le voisin comme vérifié
//            }
//        }
//    }
//    return possibilite;
//}

std::vector<const BoardSpot*> Ant::moov(int x, int y, const Board& board) const {
    std::vector<const BoardSpot*> possibilite;
    std::queue<const BoardSpot*> aVerifier; // FIFO pour la recherche en largeur
    std::set<const BoardSpot*> verifie;    // Pour éviter les redondances

    const BoardSpot* spotFourmi = board.getSpot(x, y);

    if (!spotFourmi) {
        // Si la position initiale est invalide
        return possibilite;
    }

    aVerifier.push(spotFourmi);
    verifie.insert(spotFourmi);

    while (!aVerifier.empty()) {
        const BoardSpot* currentSpot = aVerifier.front();
        aVerifier.pop();

        // Récupérer les voisins accessibles à partir de la position actuelle
        std::vector<const BoardSpot*> voisins = board.trouverVoisinsGlisseur(
            currentSpot->getCoordinates().first,
            currentSpot->getCoordinates().second
        );

        for (const BoardSpot* voisin : voisins) {
            if (verifie.find(voisin) == verifie.end()) {
                possibilite.push_back(voisin);
                aVerifier.push(voisin);
                verifie.insert(voisin);
            }
        }
    }

    // Affichage de la liste des possibilités
    std::cout << "Possibilités de déplacement : " << std::endl;
    for (const BoardSpot* spot : possibilite) {
        auto coord = spot->getCoordinates();
        std::cout << "(" << coord.first << ", " << coord.second << ")" << std::endl;
    }

    return possibilite;
}


bool Ant::estPasAuMax(bool couleur){
    if (couleur==0){ return getPoseNoir()< getMax(); }
    else{ return getPoseBlanc()< getMax(); }
}
