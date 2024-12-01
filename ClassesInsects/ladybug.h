#ifndef LADYBUG_H
#define LADYBUG_H

#include "../Insect.h"
#include "../Board.h"

class Ladybug : public Insect {
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
   std::string getType() const { return "ladybug"; }
};

#endif // LADYBUG_H
