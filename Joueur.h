#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Joueur {
private:
    bool couleur; // true = blanc, false = noir

public:
    // Constructeur par d�faut
    Joueur();

    // Constructeur avec param�tre
    Joueur(bool couleur);

    // Getter pour la couleur
    bool getCouleur() const;

    // Setter pour la couleur
    void setCouleur(bool couleur);
};

#endif // JOUEUR_H_INCLUDED
