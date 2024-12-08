#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>

class Hex: public QGraphicsPolygonItem{
public:
    // constructeur
    Hex(QGraphicsItem* parent=NULL);
    // getters
    bool getIsPlaced();
    QString getOwner();
    QColor getColor() const;
    int getCouleur(){return couleur;}
    QPoint getCoord() {return coords;}
    void setCoord(int x,int y) {coords.setX(x); coords.setY(y);}


    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // setters
    void setOwner(QString player);
    void setIsPlaced(bool b);
    void setInsectType(const QString& type);
    void setColor(const QColor& color);
    void setCouleur(int col){couleur = col;}
    void unSetColor(const QColor& color);
    QString getInsectType() const { return insectType; }

private:
    //mettre id couple de coordonnées vector?
    QPoint coords;
    int couleur;
    bool isPlaced;
    QGraphicsTextItem* labelText;
    QString insectType;
    QPixmap insectImage;
    QString owner;
    QColor color;
};

#endif // HEX_H
