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
    bool getIsEmpty(){return isEmpty;}
    QString getOwner();
    QColor getColor() const;
    int getCouleur(){return couleur;}
    QPoint getCoord() {return coords;}
    void setCoord(int x,int y) {coords.setX(x); coords.setY(y);}
    void majLabelCoord();
    QString getInsectType() const { return insectType; }
    QGraphicsTextItem* getLabel() const {return labelText;}



    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // setters
    void setOwner(QString player);
    void setIsPlaced(bool b);
    void setIsEmpty(bool b) {isEmpty = b;}
    void setInsectType(const QString& type);
    void setColor(const QColor& color);
    void setCouleur(int col){couleur = col;}
    void unSetColor();
    void setLabel(QGraphicsTextItem* label){labelText=label;}

private:
    QPoint coords;
    int couleur;
    bool isPlaced;
    bool isEmpty = false;
    QGraphicsTextItem* labelText;
    QString insectType;
    QPixmap insectImage;
    QString owner;
    QColor color;
};

#endif // HEX_H
