#ifndef MOSQUITO_H
#define MOSQUITO_H

#include "../Insect.h"

class Mosquito : public Insect {
static const unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}
};

#endif // MOSQUITO_H