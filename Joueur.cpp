#include "Joueur.h"

// Constructeur par défaut, initialise la couleur à false (noir)
Joueur::Joueur() : couleur(false) {}

// Constructeur avec paramètre
Joueur::Joueur(bool couleur) : couleur(couleur) {}

// Getter pour la couleur
bool Joueur::getCouleur() const {
    return couleur;
}

// Setter pour la couleur
void Joueur::setCouleur(bool couleur) {
    this->couleur = couleur;
}
