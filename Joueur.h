#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Player {
private:
    bool color; // true = blanc, false = noir

public:
    // Constructeur par défaut
    Player();

    // Constructeur avec paramètre
    Player(bool color);

    // Getter pour la couleur
    bool getColor() const;

    // Setter pour la couleur
    void setColor(bool color);
};

#endif // JOUEUR_H_INCLUDED
