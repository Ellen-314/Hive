#include "Joueur.h"

// Constructeur par défaut, initialise la couleur à false (noir)
Player::Player() : color(false) {}

// Constructeur avec paramètre
Player::Player(bool color) : color(color) {}

// Getter pour la couleur
bool Player::getColor() const {
    return color;
}

// Setter pour la couleur
void Player::setColor(bool color) {
    this->color = color;
}
