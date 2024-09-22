#include "Joueur.h"

// Constructeur par d�faut, initialise la couleur � false (noir)
Player::Player() : color(false) {}

// Constructeur avec param�tre
Player::Player(bool color) : color(color) {}

// Getter pour la couleur
bool Player::getColor() const {
    return color;
}

// Setter pour la couleur
void Player::setColor(bool color) {
    this->color = color;
}
