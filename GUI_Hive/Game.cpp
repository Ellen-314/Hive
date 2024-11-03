#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include <QGraphicsTextItem>

#include <QDebug>
Game::Game(QWidget *parent){
    // mettre l'écran
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // mettre la scène
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

    // initialisation de la place du pion
    pawnToPlace = NULL;
}

void Game::start(){
    // remettre l'écran vide
    scene->clear();

    hexBoard = new HexBoard();
    hexBoard->placeHexes(200,30,15,15);
    drawGUI();
    createInitialpawns();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    //dessiner un panneau pour l'affichage à un endroit précis avec propriétés spécifiques
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI(){
    // affichage panneau latéral gauche
    drawPanel(0,0,150,768,Qt::darkCyan,1);

    // affichage panneau latéral droit
    drawPanel(874,0,150,768,Qt::darkCyan,1);

    // texte joueur1
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Pièces du Joueur 1: ");
    p1->setPos(25,0);
    scene->addItem(p1);

    // Texte joureur 2
    QGraphicsTextItem* p2 = new QGraphicsTextItem("Pièces du Joueur 2: ");
    p2->setPos(874+25,0);
    scene->addItem(p2);

    // Affichage de à qui est le tour
    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(QString("Joueur1"));
    whosTurnText->setPos(490,0);
    scene->addItem(whosTurnText);

}



void Game::createInitialpawns() {
    // Effacer les pions actuels pour éviter les doublons
    player1pawns.clear();
    player2pawns.clear();

    // Quantité de chaque type de pion
    QMap<QString, int> insectCounts = {
        {"Araignée", 2},
        {"Sauterelle", 3},
        {"Fourmi", 3},
        {"Scarabé", 2},
        {"Reine", 1}
    };

    // Création de tous les pions pour Joueur 1
    for (auto it = insectCounts.begin(); it != insectCounts.end(); ++it) {
        QString type = it.key();
        int count = it.value();
        for (int i = 0; i < count; ++i) {
            Hex* pawn1 = new Hex();
            pawn1->setOwner("Joueur1");
            pawn1->setIsPlaced(false);
            pawn1->setInsectType(type); // Assignez le type d'insecte
            player1pawns.append(pawn1);
        }
    }

    // Création de tous les pions pour Joueur 2
    for (auto it = insectCounts.begin(); it != insectCounts.end(); ++it) {
        QString type = it.key();
        int count = it.value();
        for (int i = 0; i < count; ++i) {
            Hex* pawn2 = new Hex();
            pawn2->setOwner("Joueur2");
            pawn2->setIsPlaced(false);
            pawn2->setInsectType(type); // Assignez le type d'insecte
            player2pawns.append(pawn2);
        }
    }

    // Dessiner tous les pions pour les deux joueurs
    drawpawns();
}






void Game::addPawnToPlayer(QString player, QString insectType, int quantity, QList<Hex*>& pawnList) {
    for (int i = 0; i < quantity; ++i) {
        Hex* pawn = new Hex();
        pawn->setOwner(player);
        pawn->setIsPlaced(false);
        pawn->setInsectType(insectType);  // Définir le type d'insecte
        pawnList.append(pawn);
    }
}



void Game::drawpawns() {
    // Supprime les anciens pions de la scène pour éviter les doublons
    for (Hex* pawn : player1pawns) {
        scene->removeItem(pawn);
    }
    for (Hex* pawn : player2pawns) {
        scene->removeItem(pawn);
    }

    // Dessiner les pions pour le Joueur 1 dans la zone de sélection gauche
    int yPos = 25; // Position de départ verticale
    for (Hex* pawn : player1pawns) {
        pawn->setPos(13, yPos); // Positionner chaque pion verticalement
        yPos += 60; // Espace entre les pions
        scene->addItem(pawn);
    }

    // Dessiner les pions pour le Joueur 2 dans la zone de sélection droite
    yPos = 25; // Réinitialiser la position verticale
    for (Hex* pawn : player2pawns) {
        pawn->setPos(874 + 13, yPos); // Positionner chaque pion verticalement pour le joueur 2
        yPos += 60; // Espace entre les pions
        scene->addItem(pawn);
    }
}





void Game::displayMainMenu(){
    // Titre
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Hive"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // création du bouton de jeu
    Button* playButton = new Button(QString("Jouer"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // création du bouton pour quitter
    Button* quitButton = new Button(QString("Quitter"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

QString Game::getWhosTurn(){
    return whosTurn_;
}

void Game::setWhosTurn(QString player){
    // mise à jour du QString
    whosTurn_ = player;

    // mise à jour QGraphicsTextItem
    whosTurnText->setPlainText(QString("Tour du: ") + player);
}

void Game::pickUppawn(Hex *pawn){
    // prends le pion séléctionné
    if (pawn->getOwner() == getWhosTurn() && pawnToPlace == NULL){
        pawnToPlace = pawn;
        originalPos = pawn->pos();
        return;
    }
}

void Game::placepawn(Hex *hexToReplace) {
    if (!pawnToPlace) return;

    // Placer le pion sélectionné
    pawnToPlace->setPos(hexToReplace->pos());
    hexBoard->getHexes().removeAll(hexToReplace);
    hexBoard->getHexes().append(pawnToPlace);
    scene->removeItem(hexToReplace);
    pawnToPlace->setIsPlaced(true);
    removeFromDeck(pawnToPlace, getWhosTurn());
    pawnToPlace = nullptr;

    // Essayer de remplacer le pion posé par un autre du même type
    if (createReplacementPawn(hexToReplace->getInsectType(), getWhosTurn())) {
        drawpawns();  // Mettre à jour l'affichage
    }

    // Passer au tour du joueur suivant
    nextPlayersTurn();
}


bool Game::createReplacementPawn(QString insectType, QString player) {
    Hex* newPawn = nullptr;

    if (player == "Joueur1") {
        // Chercher un pion du même type dans la réserve
        for (int i = 0; i < player1RemainingPawns.size(); ++i) {
            if (player1RemainingPawns[i]->getInsectType() == insectType) {
                newPawn = player1RemainingPawns.takeAt(i);
                break;
            }
        }
        if (newPawn) {
            newPawn->setOwner("Joueur1");
            player1pawns.append(newPawn); // Ajouter au plateau
        }
    } else if (player == "Joueur2") {
        for (int i = 0; i < player2RemainingPawns.size(); ++i) {
            if (player2RemainingPawns[i]->getInsectType() == insectType) {
                newPawn = player2RemainingPawns.takeAt(i);
                break;
            }
        }
        if (newPawn) {
            newPawn->setOwner("Joueur2");
            player2pawns.append(newPawn);
        }
    }

    // Retourne vrai si un pion a été ajouté et doit être affiché
    return newPawn != nullptr;
}


void Game::nextPlayersTurn(){
    if (getWhosTurn() == QString("Joueur1")){
        setWhosTurn(QString("Joueur2"));
    }
    else {
        setWhosTurn(QString("Joueur1"));
    }
}

void Game::removeFromDeck(Hex *pawn, QString player){
    if (player == QString("Joueur1")){
        // supprimer du joueur 1
        player1pawns.removeAll(pawn);
    }

    if (player == QString("Joueur2")){
        // supprimer pour le joueur 2
        player2pawns.removeAll(pawn);
    }

}

void Game::mouseMoveEvent(QMouseEvent *event){
    // s'il y a un pawnToPlace, alors le faire suivre le mvt de la souris
    if (pawnToPlace){
        pawnToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // click droit pour revenir à la position originale
    if (event->button() == Qt::RightButton){
        if (pawnToPlace){
            pawnToPlace->setPos(originalPos);
            pawnToPlace = NULL;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
