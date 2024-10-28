#ifndef INSECT_H_INCLUDED
#define INSECT_H_INCLUDED

class Insect {
private:
    // Pointeurs vers les insectes voisins
    Insect* neighborTop;
    Insect* neighborBottom;
    Insect* neighborTopRight;
    Insect* neighborBottomRight;
    Insect* neighborTopLeft;
    Insect* neighborBottomLeft;

    // Autres attributs
    bool covered; // couvert ou non par un scarab�e
    bool color; // True pour blanc et False pour noir

public:
    // Constructeur
    Insect();

    // Getter and Setter pour les voisins
    void setNeighborTop(Insect* insect);
    Insect* getNeighborTop() const;

    void setNeighborBottom(Insect* insect);
    Insect* getNeighborBottom() const;

    void setNeighborTopRight(Insect* insect);
    Insect* getNeighborTopRight() const;

    void setNeighborBottomRight(Insect* insect);
    Insect* getNeighborBottomRight() const;

    void setNeighborTopLeft(Insect* insect);
    Insect* getNeighborTopLeft() const;

    void setNeighborBottomLeft(Insect* insect);
    Insect* getNeighborBottomLeft() const;

    // Getter and Setter pour cover() et color()
    bool isCovered() const;
    void setCovered(bool covered);

    bool getColor() const;
    void setColor(bool color);

    // M�thode moov()
    void moov();
};

#endif // INSECT_H_INCLUDED