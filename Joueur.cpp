#include "Joueur.h"

// Constructeur par d�faut, initialise la couleur � false (noir)
Joueur::Joueur() : couleur(false) {}

// Constructeur avec param�tre
Joueur::Joueur(bool couleur) : couleur(couleur) {}

// Getter pour la couleur
bool Joueur::getCouleur() const {
    return couleur;
}

// Setter pour la couleur
void Joueur::setCouleur(bool couleur) {
    this->couleur = couleur;
}
