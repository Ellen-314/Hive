
#ifndef QUEENBEE_H
#define QUEENBEE_H
#include <stdio.h>
#include <iostream>
#include "Insect.h"
#include "Board.h"
class QueenBee : public Insect {

static const unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}

    //m�thode qui renvoit true si la reine est entour�e
    //TODO
    bool isSurrounded() const;
    void moov(int x, int y, const Board& board)override;//override est utillis� pour indiquer que la fonction prends le pas sur celle de insect.
    ~QueenBee() override {};
};


#endif // QUEENBEE_H
