
#ifndef QUEENBEE_H
#define QUEENBEE_H

class QueenBee : public Insect {

    static unsigned int Max;
static unsigned int poseBlanc;
static unsigned int poseNoir;

public:
   static unsigned int getMax(){return Max;}
   static unsigned int getPoseBlanc(){return poseBlanc;}
   static unsigned int getPoseNoir(){return poseNoir;}
   static void ajouterBlanc(){poseBlanc++;}
   static void ajouterNoir(){poseNoir++;}

    //méthode qui renvoit true si la reine est entourée
    bool isSurrounded() const;
};
#endif // QUEENBEE_H
