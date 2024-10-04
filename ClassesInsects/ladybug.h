#ifndef LADYBUG_H
#define LADYBUG_H

#include "Insect.h"

class Ladybug : public Insect {
static unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}
};

#endif // LADYBUG_H
