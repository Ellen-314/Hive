#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QMessageBox>
#include <QFile>

#include <QDebug>
Game::Game(QWidget *parent): QGraphicsView(parent), numRetours(0), pawnToPlace(nullptr) {
    //adapter la taille dynamiquement en fonction de l'écran
    QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    int newWidth = screenSize.width() * 0.8;
    int newHeight = screenSize.height();
    // mettre l'écran
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(newWidth,newHeight);

    // mettre la scène
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,newWidth,newHeight);
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

void Game::drawGUI() {
    // Affichage panneau latéral gauche
    drawPanel(0, 0, 150, scene->height(), Qt::darkCyan, 1);

    // Affichage panneau latéral droit
    drawPanel(scene->width() - 150, 0, 150, scene->height(), Qt::darkCyan, 1);

    // Texte joueur 1 : Nom et type
    QString player1Label = QString("Joueur 1: %1 (%2)")
                               .arg(player1Name.isEmpty() ? "Anonyme" : player1Name)
                               .arg(player1Type == "IA" ? "IA" : "Humain");

    QGraphicsTextItem* p1 = new QGraphicsTextItem(player1Label);
    p1->setDefaultTextColor(Qt::black);
    p1->setFont(QFont("Arial", 8));
    p1->setPos(10, 6);  // Position sur le panneau gauche
    scene->addItem(p1);

    // Texte joueur 2 : Nom et type
    QString player2Label = QString("Joueur 2: %1 (%2)")
                               .arg(player2Name.isEmpty() ? "Anonyme" : player2Name)
                               .arg(player2Type == "IA" ? "IA" : "Humain");

    QGraphicsTextItem* p2 = new QGraphicsTextItem(player2Label);
    p2->setDefaultTextColor(Qt::black);
    p2->setFont(QFont("Arial", 8));
    p2->setPos(scene->width() - 140, 6);  // Position sur le panneau droit
    scene->addItem(p2);

    // Texte pour indiquer le joueur dont c'est le tour
    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(player1Name);  // Initialisation à Joueur 1
    whosTurnText->setDefaultTextColor(Qt::black);
    whosTurnText->setFont(QFont("Arial", 8, QFont::Bold));
    whosTurnText->setPos(scene->width() / 2 - 50, 6);  // Centré en haut
    scene->addItem(whosTurnText);

    // Label pour les retours en arrière
    QString retoursLabel = QString("Retours en arrière: %1").arg(numRetours); // Use dynamic numRetours
    QGraphicsTextItem* retoursText = new QGraphicsTextItem(retoursLabel);
    retoursText->setDefaultTextColor(Qt::black);
    retoursText->setFont(QFont("Arial", 8));
    retoursText->setPos(scene->width() / 2 - 180, 6); // Adjusted left of whosTurnText
    scene->addItem(retoursText);

    // Bouton pour les retours en arrière
    Button* backButton = new Button(QString("Retour"));
    backButton->setScale(0.5);
    backButton->setFontSize(18);
    backButton->setPos(scene->width() / 2 - 300, 0);  // Left aligned further for button
    connect(backButton, SIGNAL(clicked()), this, SLOT(undoLastAction()));
    scene->addItem(backButton);

    // Bouton enregistrer
    Button* saveButton = new Button(QString("Enregistrer"));
    saveButton->setScale(0.5);
    saveButton->setFontSize(18);  // Taille de la police
    saveButton->setPos(scene->width() / 2 + 80, 0);  // Right of whosTurnText for save button
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    scene->addItem(saveButton);
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
            pawn1->setOwner(player1Name); //utilise les noms dynamiques
            pawn1->setIsPlaced(false);
            pawn1->setInsectType(type); // Assignez le type d'insecte
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::blue);
            pawn1->setBrush(brush);
            player1pawns.append(pawn1);
        }
    }

    // Création de tous les pions pour Joueur 2
    for (auto it = insectCounts.begin(); it != insectCounts.end(); ++it) {
        QString type = it.key();
        int count = it.value();
        for (int i = 0; i < count; ++i) {
            Hex* pawn2 = new Hex();
            pawn2->setOwner(player2Name); //utilise les noms dynamiques
            pawn2->setIsPlaced(false);
            pawn2->setInsectType(type); // Assignez le type d'insecte
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::red);
            pawn2->setBrush(brush);
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
        yPos += 45; // Espace entre les pions
        scene->addItem(pawn);
    }

    // Dessiner les pions pour le Joueur 2 dans la zone de sélection droite
    yPos = 25; // Réinitialiser la position verticale
    for (Hex* pawn : player2pawns) {
        pawn->setPos(874 + 13, yPos); // Positionner chaque pion verticalement pour le joueur 2
        yPos += 45; // Espace entre les pions
        scene->addItem(pawn);
    }
}





void Game::displayMainMenu(){
    // efface tout pour un bon affichage lors des retours en arrières
    scene->clear();
    // Titre
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Hive"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = scene->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // création du bouton de paramétrage d'une nouvelle partie
    Button* newPlayButton = new Button(QString("Parametrer une nouvelle partie"));
    int nbxPos = scene->width()/2 - newPlayButton->boundingRect().width()/2;
    int nbyPos = 200;
    newPlayButton->setPos(nbxPos,nbyPos);
    connect(newPlayButton,SIGNAL(clicked()),this, SLOT(displayGameSetupMenu()));
    scene->addItem(newPlayButton);

    // création du bouton de reprise de la partie
    Button* resumeButton = new Button(QString("Reprendre la partie"));
    int rbxPos = scene->width()/2 - resumeButton->boundingRect().width()/2;
    int rbyPos = 300;
    resumeButton->setPos(rbxPos,rbyPos);
    connect(resumeButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(resumeButton);

    // création du bouton pour abandonner la partie en cours
    Button* quitPlayButton = new Button(QString("Abandonner la partie"));
    int qpxPos = scene->width()/2 - quitPlayButton->boundingRect().width()/2;
    int qpyPos = 400;
    quitPlayButton->setPos(qpxPos,qpyPos);
    connect(quitPlayButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitPlayButton);

    // création du bouton pour quitter
    Button* quitButton = new Button(QString("Quitter"));
    int qxPos = scene->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 500;
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
   // whosTurnText->setPlainText(QString("Tour de: %1").arg(player));
    whosTurnText->setPlainText(QString("Tour de : ") + player);
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


bool Game::createReplacementPawn(QString insectType, QString player) { // Plus besoin de cette méthode
    Hex* newPawn = nullptr;

    if (player == player1Name) {
        // Chercher un pion du même type dans la réserve
        for (int i = 0; i < player1RemainingPawns.size(); ++i) {
            if (player1RemainingPawns[i]->getInsectType() == insectType) {
                newPawn = player1RemainingPawns.takeAt(i);
                break;
            }
        }
        if (newPawn) {
            newPawn->setOwner(player1Name);
            player1pawns.append(newPawn); // Ajouter au plateau
        }
    } else if (player == player2Name) {
        for (int i = 0; i < player2RemainingPawns.size(); ++i) {
            if (player2RemainingPawns[i]->getInsectType() == insectType) {
                newPawn = player2RemainingPawns.takeAt(i);
                break;
            }
        }
        if (newPawn) {
            newPawn->setOwner(player2Name);
            player2pawns.append(newPawn);
        }
    }

    // Retourne vrai si un pion a été ajouté et doit être affiché
    return newPawn != nullptr;
}


void Game::nextPlayersTurn(){
    if (getWhosTurn() == QString(player1Name)){
        setWhosTurn(QString(player2Name));
    }
    else {
        setWhosTurn(QString(player1Name));
    }
}

void Game::removeFromDeck(Hex *pawn, QString player){
    if (player == QString(player1Name)){
        // supprimer du joueur 1
        player1pawns.removeAll(pawn);
    }

    if (player == QString(player2Name)){
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

void Game::displayGameSetupMenu() {
    // Effacer l'écran actuel
    scene->clear();

    // Titre du menu
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Paramétrage de la partie"));
    QFont titleFont("comic sans", 30);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    // Paramètres des joueurs
    QGraphicsTextItem* player1Label = new QGraphicsTextItem("Nom Joueur 1 :");
    player1Label->setPos(200, 150);
    scene->addItem(player1Label);

    player1NameInput = new QLineEdit();
    player1NameInput->setText("Joueur1");
    player1NameInput->setGeometry(400, 150, 200, 30);
    scene->addWidget(player1NameInput);

    QGraphicsTextItem* player2Label = new QGraphicsTextItem("Nom Joueur 2 :");
    player2Label->setPos(200, 200);
    scene->addItem(player2Label);

    player2NameInput = new QLineEdit();
    player2NameInput->setText("Joueur2");
    player2NameInput->setGeometry(400, 200, 200, 30);
    scene->addWidget(player2NameInput);

    // Type des joueurs (Humain/IA)
    player1TypeComboBox = new QComboBox();
    player1TypeComboBox->addItem("Humain");
    player1TypeComboBox->addItem("IA");
    player1TypeComboBox->setGeometry(620, 150, 100, 30);
    scene->addWidget(player1TypeComboBox);

    player2TypeComboBox = new QComboBox();
    player2TypeComboBox->addItem("Humain");
    player2TypeComboBox->addItem("IA");
    player2TypeComboBox->setGeometry(620, 200, 100, 30);
    scene->addWidget(player2TypeComboBox);

    // Nombre de retours arrière
    QGraphicsTextItem* undoLabel = new QGraphicsTextItem("Nombre de retours arrière :");
    undoLabel->setPos(200, 300);
    scene->addItem(undoLabel);

    undoSpinBox = new QSpinBox();
    undoSpinBox->setRange(0, 10);
    undoSpinBox->setValue(0);  // Par défaut 0
    undoSpinBox->setGeometry(500, 300, 100, 30);
    scene->addWidget(undoSpinBox);

    // Extensions
    QGraphicsTextItem* extensionLabel = new QGraphicsTextItem("Extensions disponibles :");
    extensionLabel->setPos(200, 400);
    scene->addItem(extensionLabel);

    extension1CheckBox = new QCheckBox("Ladybug");
    extension1CheckBox->setGeometry(400, 400, 150, 30);
    scene->addWidget(extension1CheckBox);

    extension2CheckBox = new QCheckBox("Mosquito");
    extension2CheckBox->setGeometry(400, 450, 150, 30);
    scene->addWidget(extension2CheckBox);

    // Bouton pour lancer la partie
    Button* startButton = new Button(QString("Lancer la partie"));
    int bxPos = this->width()/2 - startButton->boundingRect().width()/2;
    int byPos = 500;
    startButton->setPos(bxPos, byPos);
    connect(startButton, &Button::clicked, this, &Game::startGameWithSettings);
    scene->addItem(startButton);

    // Bouton pour retourner au menu principal
    Button* backButton = new Button(QString("Retour"));
    backButton->setPos(bxPos, byPos + 100);
    connect(backButton, &Button::clicked, this, &Game::displayMainMenu);
    scene->addItem(backButton);


}
void Game::startGameWithSettings() {

    // Récupérer les paramètres de l'interface utilisateur
    player1Name = player1NameInput->text();
    player2Name = player2NameInput->text();
    player1Type = player1TypeComboBox->currentText();
    player2Type = player2TypeComboBox->currentText();

    // Autres paramètres
    int undoCount = undoSpinBox->value();
    bool extension1Enabled = extension1CheckBox->isChecked();
    bool extension2Enabled = extension2CheckBox->isChecked();

    // Afficher les paramètres dans le debug
    qDebug() << "Player 1: " << player1Name << "Type:" << player1Type;
    qDebug() << "Player 2: " << player2Name << "Type:" << player2Type;
    qDebug() << "Undo count:" << undoCount;
    qDebug() << "Extension 1:" << extension1Enabled;
    qDebug() << "Extension 2:" << extension2Enabled;

    start();
}

void Game::undoLastAction() {
    if (numRetours > 0 && !history.isEmpty()) {
        QGraphicsItem* lastAction = history.takeLast();
        scene->removeItem(lastAction);  // Undo the last action visually
        delete lastAction;
        numRetours--;
        drawGUI();  // Update undo count on GUI
    } else {
        QMessageBox::warning(this, "Retour", "Il n'y a plus de retours en arrières!");
    }
}

void Game::saveGame() {
    QFile file("savegame.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << "Player 1: " << player1Name << " (" << player1Type << ")\n";
        out << "Player 2: " << player2Name << " (" << player2Type << ")\n";
        out << "Undo actions remaining: " << numRetours << "\n";
        // Save additional game state details here.
        file.close();
        QMessageBox::information(this, "Enregistrement", "Le jeu a bien été sauvegardé.");
    } else {
        QMessageBox::warning(this, "Enregistrement", "Erreur, le jeu n'a pas été sauvegardé.");
    }
}


