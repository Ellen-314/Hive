#ifndef INSECT_H_INCLUDED
#define INSECT_H_INCLUDED
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>

class Board;
class BoardSpot;
class Insect{
private:



    bool color; // True pour blanc et False pour noir
    // Pointeur vers l'insecte couvert (si il y en a un)
    Insect* couvert= nullptr;

    //on retire la possiblité de recopie pour ne pas avoir de probleme avec couvert
    Insect(const Insect&) = delete;
    Insect& operator=(const Insect&) = delete;

public:
    // Constructeur
    Insect(){};
    //destructeur
    virtual ~Insect() {
        delete couvert;
    }


    // Getter and Setter pour le pointeur vers l'insecte couvert
    const Insect* getcouvert()const{return couvert;}
    Insect* getcouvertModify(){return couvert;}
    void setInsectUnder( Insect* ins){couvert= ins;}

    // Getter and Setter pour color()

    bool getColor() const;
    void setColor(bool color);

    // Methode getType() virtuelle pure car surchargée pour chaque insect. Elle renvoie le type de chaque insect
    virtual std::string getType() const = 0;
    // Methode moov() virtuelle pure car surchargée pour chaque insect. Elle renvoie les possibilités de mouvements
    virtual std::vector<const BoardSpot*> moov(int x, int y, const Board& board)const = 0;


};

#endif // INSECT_H_INCLUDED
