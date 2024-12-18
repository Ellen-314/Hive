#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "N_game.h"
#include <QPixmap>
#include "Insect.h"

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
    this->color = color;
    setBrush(QBrush(color));
}

void Hex::unSetColor() {
    this->color = Qt::white;
    setBrush(Qt::NoBrush);
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Board& board = game->getPlateau();
    if(getIsPlaced() && getOwner() == game->getWhosTurn()){
        if(!getIsEmpty() && getOwner() == game->getWhosTurn()){
            HexBoard* hexboard = game->hexBoard;
            hexboard->eraseHighlighted();
            qDebug() << getCoord();
            // mettre possibilités de move
            const BoardSpot* spot = nullptr;
            spot = board.getSpot(getCoord().x(), getCoord().y());
            qDebug() << spot->getCoordinates();
            qDebug() << spot->getInsect();

            std::vector<const BoardSpot*> possibilite = spot->getInsect()->moov(getCoord().x(), getCoord().y(), board);
            for(const auto& spot : possibilite){
                auto [x, y] = spot->getCoordinates();

                // Création d'un board temporaire pour simuler le move
                Board tempBoard = board;
                tempBoard.moovInsect(getCoord().x(), getCoord().y(), x, y);

                // Verifie que le board est tj connexe si on fait le move
                if (tempBoard.isConnexe()) {
                    Hex& hex = hexboard->getHex(QPoint(x, y));
                    qDebug() << "x:" << x << " y:" << y;
                    hexboard->addHighlightedHex(&hex, "magenta");
                }
            }
            game->pawnToMove = this;
            return;
        }
    }

    if(this->isEmpty && game->pawnToMove != NULL && game->hexBoard->inHighlighted(this)){
        // Check si ça reste connexe
        Board tempBoard = board; // Crée un board temporaire pour simuler le move
        tempBoard.moovInsect(game->pawnToMove->getCoord().x(), game->pawnToMove->getCoord().y(), this->getCoord().x(), this->getCoord().y());
        if (tempBoard.isConnexe()) {
            game->getPlateau().print_debug();
            game->getPlateau().moovInsect(game->pawnToMove->getCoord().x(), game->pawnToMove->getCoord().y(), this->getCoord().x(), this->getCoord().y());
            game->getPlateau().print_debug();
            game->getPlateau().addNullSpot(this->getCoord().x(), this->getCoord().y());
            game->exchangeSpot(game->hexBoard, game->pawnToMove, this);
            game->pawnToMove = NULL;
            game->hexBoard->eraseHighlighted();
            game->nextPlayersTurn();
        } else {
            qDebug() << "Move pas autorisé: Le board ne sera pas connexe.";
        }
        return;
    }

    // si hex est pas placé (=pion) alors le prendre
    if (getIsPlaced() == false && getOwner() == game->getWhosTurn()){
        game->pawnToMove = NULL;
        HexBoard* hexboard = game->hexBoard;
        hexboard->eraseHighlighted();
        std::vector<const BoardSpot*> possibilites = board.possibleplacer(getCouleur());
        if(game->getColorToPlay() == 1){
            if (board.getSpot(0, 0) == nullptr){
                board.addSpot(0, 0);
                //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur blanche à la position (0, 0)\n=========\n\n";
            }
            const BoardSpot* spot = board.getSpot(0, 0);
            possibilites.push_back(spot);
        } else {
            if (board.getSpot(0, 1) == nullptr) {
                board.addSpot(0, 1);
                //std::cout << "\n=========\nDEBUG : Ajout du spot pour la couleur noire à la position (0, 1)\n=========\n\n";
            }
            const BoardSpot* spot = board.getSpot(0, 1);
            possibilites.push_back(spot);
        }
        int x, y;
        qDebug() << possibilites.size();
        for(const auto& spot : possibilites){
            auto [x, y] = spot->getCoordinates();
            Hex& hex = hexboard->getHex(QPoint(x, y));
            hexboard->addHighlightedHex(&hex, "cyan");
        }
        game->pickUppawn(this);
    }
    // si il est pris alors le replacer
    else {
        if(game->hexBoard->inHighlighted(this)){
            game->placepawn(this);
        }
    }
}



void Hex::setOwner(QString player){
    // MAJ owner
    owner = player;
}

void Hex::setIsPlaced(bool b){
    isPlaced = b;
}

void Hex::setInsectType(const QString& type) {
    insectType = type;

    // Crée un label pour afficher le type d'insecte
    QGraphicsTextItem* label = new QGraphicsTextItem(type, this);
    setLabel(label);
    label->setDefaultTextColor(Qt::white);
    label->setPos(3, 7);  // Ajuster pour centrer le label dans l'hexagone

}

void Hex::majLabelCoord(){
    QString coord = QStringLiteral("(%1,%2)").arg(getCoord().x()).arg(getCoord().y());
    getLabel()->setPlainText(coord);
}
