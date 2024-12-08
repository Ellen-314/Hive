#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "N_game.h"
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

QColor Hex::getColor() const {
    return color;
}

void Hex::setColor(const QColor& color) {
    this->color = color; // Assuming `color` is the member variable for storing the color
    setBrush(QBrush(color)); // Apply the color to the QGraphicsPolygonItem visually
}

void Hex::unSetColor(const QColor& color) {
    this->color = Qt::white; // Assuming `color` is the member variable for storing the color
    setBrush(Qt::NoBrush); // Apply the color to the QGraphicsPolygonItem visually
}


void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    game->getPlateau().addSpot(2, 3);
    Insect* insect = new Ant();
    insect->setColor(1);
    game->getPlateau().addInsectToSpot(2,3, insect);
    game->getPlateau().addNullSpot(2,3);

    // si hex est pas placé (=pion) alors le prendre
    if (getIsPlaced() == false){


        std::vector<const BoardSpot*> possibilites = game->getPlateau().possibleplacer(getCouleur());
        int x, y;
        HexBoard* hexboard = game->hexBoard;
        qDebug()<<possibilites.size();
        for(const auto& spot : possibilites){
            auto [x,y] = spot->getCoordinates();
            qDebug() << x << " " << y;

            hexboard->hexHighlight(QPoint(x, y));

        }
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

    /*// changer la couleur
    if (player == QString("Anonyme")){
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
    } */
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
