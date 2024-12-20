

#ifndef ANT_H
#define ANT_H
#include <string>

#include <stdio.h>
#include <iostream>
#include "../Insect.h"
#include "../Board.h"
#include <queue>
#include <set>
#include <vector>


class Ant : public Insect {
static const unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}
   static void resetBlanc() {poseBlanc=0;}
   static void resetNoir() {poseNoir=0;}
   std::string getType() const {return "ant";}


    //la fonction moov retourne un vecteur des possibilités des mouvements de la fourmie aux positions données.
    std::vector<const BoardSpot*> moov(int x, int y, const Board& board)const override ;//override est utillis� pour indiquer que la fonction prends le pas sur celle de insect.
    //dit si le joueur pet encore poser un pion de ce type; si il peut: true sinon: false
    //blanc: True black=False
    static bool estPasAuMax(bool couleur);

    ~Ant() override {};

};

#endif // ANT_H
