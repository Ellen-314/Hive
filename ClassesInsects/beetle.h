#ifndef BEETLE_H
#define BEETLE_H

#include "../Insect.h"
#include "../Board.h"

class Beetle : public Insect {
    static const unsigned int Max;
    static unsigned int poseBlanc;
    static unsigned int poseNoir;


public:

    static unsigned int getMax(){return Max;}
    static unsigned int getPoseBlanc(){return poseBlanc;}
    static unsigned int getPoseNoir(){return poseNoir;}
    static void resetBlanc() {poseBlanc=0;}
    static void resetNoir() {poseNoir=0;}
    static void ajouterBlanc(){poseBlanc++;}
    static void ajouterNoir(){poseNoir++;}
    static bool estPasAuMax(bool couleur);
    std::string getType() const { return "beetle"; }
    std::vector<const BoardSpot*> moov(int x, int y, const Board& board)const override;//override est utillis� pour indiquer que la fonction prends le pas sur celle de insect.

    ~Beetle() override{};
};

#endif // BEETLE_H
