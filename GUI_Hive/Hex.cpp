#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "Game.h"
#include <QPixmap>

extern Game* game;

//#include <QDebug>

Hex::Hex(QGraphicsItem *parent){
    // dessin du polygone pour un pion

    // points pour dessiner l'hexagone: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    // augmentation avec une échelle car sinon trop petits
    int SCALE_BY = 20;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // création de l'hexagone
    QPolygonF hexagon(hexPoints);

    // affichage de l'hexagone
    setPolygon(hexagon);

    // initialisation
    isPlaced = false;

    // Initialisation du label de texte pour afficher le type d'insecte
    labelText = new QGraphicsTextItem(this);
    labelText->setDefaultTextColor(Qt::black);
    labelText->setFont(QFont("Arial", 6, QFont::Bold));
    labelText->setPos(SCALE_BY, SCALE_BY/2); // Centrer le texte

}


bool Hex::getIsPlaced(){
    return isPlaced;

}

QString Hex::getOwner(){
    return owner;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // si hex est pas placé (=pion) alors le prendre
    if (getIsPlaced() == false){
        game->pickUppawn(this);
    }

    // si il est pris alors le replacer
    else {
        game->placepawn(this);
    }
}

void Hex::setOwner(QString player){
    // MAJ owner
    owner = player;

    // changer la couleur
    if (player == QString("Personne")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if (player == QString("Joueur1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if (player == QString("Joueur2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void Hex::setIsPlaced(bool b){
    isPlaced = b;
}

void Hex::setInsectType(const QString& type) {
    insectType = type;

    // Crée un label pour afficher le type d'insecte
    QGraphicsTextItem* label = new QGraphicsTextItem(type, this);
    label->setDefaultTextColor(Qt::white);
    label->setPos(3, 7);  // Ajuster pour centrer le label dans l'hexagone


}
