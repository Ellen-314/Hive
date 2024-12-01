#ifndef GRASSHOPPER_H
#define GRASSHOPPER_H

#include "../Insect.h"
#include "../Board.h"

class Grasshopper : public Insect {
static const unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}
   static bool estPasAuMax(bool couleur);
   static void resetBlanc() {poseBlanc=0;}
   static void resetNoir() {poseNoir=0;}
   std::string getType() const { return "grasshopper"; }

   std::vector<const BoardSpot*> moov(int x, int y, const Board& board)const override;//override est utillis� pour indiquer que la fonction prends le pas sur celle de insect.
   ~Grasshopper() override{};
};

#endif // GRASSHOPPER_H
