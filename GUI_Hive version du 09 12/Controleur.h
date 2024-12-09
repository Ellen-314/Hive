#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <stack>
#include <iostream>
#include <stack>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Board.h"
#include "Insect.h"
#include "Jeu.h"

// Exception pour gestion des erreurs dans la classe Controleur
class ControleurException : public std::exception {
private:
    std::string message;

public:
    ControleurException(const std::string& msg) : message(msg) {}
    std::string getMessage() const { return message; }
};

class Controleur {
    Jeu jeu;
public:
    // Constructeur
    Controleur()=default;

    // Pour l'instant
    ~Controleur()=default;

    // Méthode principale pour démarrer le menu, lancer une nouvelle partie, choisir les options, etc...
    void demarrage();

    // Pour éviter la création de plusieurs Controleurs
    Controleur(const Controleur& c) = delete;
    Controleur& operator=(const Controleur& c) = delete;
};


#endif // CONTROLEUR_H
