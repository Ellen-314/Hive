#include "N_game.h"
#include "HexBoard.h"
#include "Board.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <string>
#include <Insect.h>
#include <QMessageBox>
#include <QComboBox>
#include <QListView>



#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QMenu>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGraphicsProxyWidget>



unsigned int Game::compteurDeToursBlanc=0;
unsigned int Game::compteurDeToursNoir=0;

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
    //scene->setBackgroundBrush(QBrush(Qt::white));
    setScene(scene);

    // initialisation de la place du pion
    pawnToPlace = NULL;
}

Game::~Game() {
}

void Game::start(){
    // remettre l'écran vide
    scene->clear();

    hexBoard = new HexBoard();
    hexBoard->placeHexes(200,30,15,15);
    drawGUI();
    createInsects();
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
    QString retoursLabel = QString("Retours en arrière: %1").arg(numRetours);
    QGraphicsTextItem* retoursText = new QGraphicsTextItem(retoursLabel);
    retoursText->setDefaultTextColor(Qt::black);
    retoursText->setFont(QFont("Arial", 8));
    retoursText->setPos(scene->width() / 2 - 180, 6);
    scene->addItem(retoursText);

    // Bouton pour les retours en arrière
    Button* backButton = new Button(QString("Retour"));
    backButton->setScale(0.5);
    backButton->setFontSize(18);
    backButton->setPos(scene->width() / 2 - 300, 0);
    //connect(backButton, &Button::clicked, this, &Game::undoLastAction); //Pas mis en place
    scene->addItem(backButton);

    // Bouton enregistrer
    Button* saveButton = new Button(QString("Enregistrer"));
    saveButton->setScale(0.5);
    saveButton->setFontSize(18);  // Taille de la police
    saveButton->setPos(scene->width() / 2 + 80, 0);
    //connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    scene->addItem(saveButton);
}




void Game::createInitialpawns() {
    // Effacer les pions actuels pour éviter les doublons
    player1pawns.clear();
    player2pawns.clear();

    // Création de tous les pions pour Joueur 1
    for (int i=0; i<insectsBlanc.size(); i++) {
        qDebug()<<"type insect pawn:"<<insectsBlanc[i]->getType();
        QString type = QString::fromStdString(insectsBlanc[i]->getType());

            Hex* pawn1 = new Hex();
            pawn1->setCouleur(1);
            pawn1->setOwner(player1Name); //utilise les noms dynamiques
            pawn1->setIsPlaced(false);
            pawn1->setInsectType(type);
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::blue);
            pawn1->setBrush(brush);
            player1pawns.append(pawn1);

    }

    // Création de tous les pions pour Joueur 2
    for (int i=0; i<insectsNoir.size(); i++) {
        qDebug()<<"type insect pawn:"<<insectsNoir[i]->getType();
        QString type = QString::fromStdString(insectsNoir[i]->getType());

        Hex* pawn2 = new Hex();
        pawn2->setCouleur(0);
        pawn2->setOwner(player2Name); //utilise les noms dynamiques
        pawn2->setIsPlaced(false);
        pawn2->setInsectType(type);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        pawn2->setBrush(brush);
        player2pawns.append(pawn2);

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
    whosTurnText->setPlainText(QString("Tour de : ") + player);

    // Vérification de la victoire
    if(isQueenSurrounded(1)){
        qDebug() << "Le joueur";

        int winningPlayer;
        // Calcul du joueur gagnant
        if((compteurDeToursBlanc + compteurDeToursNoir) % 2 == 1){
            winningPlayer = 1;
        } else {
            winningPlayer = 2;
        }

        qDebug() << winningPlayer << "a gagné !" << "\n";

        // Affichage d'une fenêtre pop-up pour annoncer la victoire
        QString winnerName = (winningPlayer == 1) ? player1Name : player2Name;
        QMessageBox::information(nullptr, "Victoire", QString("Le joueur %1 a gagné !").arg(winnerName));
    }
    // Vérification si le joueur s'est fait perdre tout seul
    else if(isQueenSurrounded(0)){
        qDebug() << "Le joueur";

        int winningPlayer;
        // Calcul du joueur gagnant
        if((compteurDeToursBlanc + compteurDeToursNoir) % 2 == 0){
            winningPlayer = 1;
        } else {
            winningPlayer = 2;
        }

        qDebug() << winningPlayer << "a gagné !" << "\n";

        // Affichage d'une fenêtre pop-up pour annoncer la victoire
        QString winnerName = (winningPlayer == 1) ? player1Name : player2Name;
        QMessageBox::information(nullptr, "Victoire", QString("Le joueur %1 a gagné !").arg(winnerName));
    }
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
    pawnToPlace->setIsEmpty(false);
    int x,y;
    QPoint point = hexToReplace->getCoord();
    x = point.x();
    y = point.y();
    pawnToPlace->setCoord(x, y);
    poserInsect(pawnToPlace, hexToReplace);
    removeFromDeck(pawnToPlace, getWhosTurn());
    pawnToPlace = nullptr;

    // Essayer de remplacer le pion posé par un autre du même type
    if (createReplacementPawn(hexToReplace->getInsectType(), getWhosTurn())) {
        drawpawns();  // Mettre à jour l'affichage
    }
    hexBoard->eraseHighlighted();
    // Passer au tour du joueur suivant
    nextPlayersTurn();

}

void Game::poserInsect(Hex *source, Hex *destination){
    int color = (getWhosTurn() == player1Name) ? 1 : 0;
    Insect* insect = nullptr;
    std::string insectLabel = source->getInsectType().toStdString();
    if(color == 1){
        int choix_insect = -1; // Initialissation avec -1 pour indiquer pas trouvé

        // Trouver l'index de l'insect dans la liste blanc
        for (int  i = 0; i < getInsectBlancMod().size(); ++i) {
            if (getInsectBlancMod()[i]->getType() == insectLabel) {
                choix_insect = i;
            }
        }

        if (choix_insect == -1) {
            throw std::runtime_error("No matching insect found in the noir list.");
        }

    insect = getInsectBlancMod()[choix_insect];
    insectsBlanc.erase(insectsBlanc.begin()+choix_insect);
    }
    else {
        int choix_insect = -1; // Initialisation avec -1 pour indiquer pas trouvé

        // Trouver l'index de l'insect dans la liste noir
        for (size_t i = 0; i < getInsectNoirMod().size(); ++i) {
            if (getInsectNoirMod()[i]->getType() == insectLabel) {
                choix_insect = static_cast<int>(i);
                break;
            }
        }

        if (choix_insect == -1) {
            throw std::runtime_error("No matching insect found in the noir list.");
        }

    insect = getInsectNoirMod()[choix_insect];
    insectsNoir.erase(insectsNoir.begin()+choix_insect);
    }
    insect->setColor(color);
    int x,y;
    x = destination->getCoord().x();
    y = destination->getCoord().y();
    BoardSpot spot(x,y);
    if(board.getSpot(x,y)==nullptr){
    board.addSpot(x,y);
    }
    board.addInsectToSpot(x, y, insect);
    board.addNullSpot(x,y);


    static std::unordered_map<std::string, std::function<void(int)>> insectCountUpdate = {
        {"queenbee", [](int color) { color == 1 ? QueenBee::ajouterBlanc() : QueenBee::ajouterNoir(); }},
        {"ant", [](int color) { color == 1 ? Ant::ajouterBlanc() : Ant::ajouterNoir(); }},
        {"spider", [](int color) { color == 1 ? Spider::ajouterBlanc() : Spider::ajouterNoir(); }},
        {"grasshopper", [](int color) { color == 1 ? Grasshopper::ajouterBlanc() : Grasshopper::ajouterNoir(); }},
        {"beetle", [](int color) { color == 1 ? Beetle::ajouterBlanc() : Beetle::ajouterNoir(); }},
        {"ladybug", [](int color) { color == 1 ? Ladybug::ajouterBlanc() : Ladybug::ajouterNoir(); }},
        {"mosquito", [](int color) { color == 1 ? Mosquito::ajouterBlanc() : Mosquito::ajouterNoir(); }}
    };

    // En fonction du type de l'insect
    auto it = insectCountUpdate.find(insect->getType());
    if (it != insectCountUpdate.end()) {
        it->second(color);
    } else {
        qDebug() << "Unknown insect type: " << QString::fromStdString(insect->getType());
    }


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
        ajouterCompteurDeToursBlanc();
        setWhosTurn(QString(player2Name));
    }
    else {
        ajouterCompteurDeToursNoir();
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

        }
        hexBoard->eraseHighlighted();
        return;

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
    QGraphicsProxyWidget* player1NameInputProxy = scene->addWidget(player1NameInput);
    player1NameInputProxy->setPos(400, 150);

    QGraphicsTextItem* player2Label = new QGraphicsTextItem("Nom Joueur 2 :");
    player2Label->setPos(200, 200);
    scene->addItem(player2Label);

    player2NameInput = new QLineEdit();
    player2NameInput->setText("Joueur2");
    player2NameInput->setGeometry(400, 150, 200, 30);
    QGraphicsProxyWidget* player2NameInputProxy = scene->addWidget(player2NameInput);
    player2NameInputProxy->setPos(400, 200);


    // Player 1 Menu Button
    QPushButton *player1MenuButton = new QPushButton("Humain");
    QMenu *player1Menu = new QMenu();
    QAction *player1HumainAction = player1Menu->addAction("Humain");
    QAction *player1IAAction = player1Menu->addAction("IA");
    player1MenuButton->setMenu(player1Menu);

    // Connect actions to update Player 1 button text
    QObject::connect(player1HumainAction, &QAction::triggered, [player1MenuButton]() {
        player1MenuButton->setText("Humain");
    });
    QObject::connect(player1IAAction, &QAction::triggered, [player1MenuButton]() {
        player1MenuButton->setText("IA");
    });

    // Add Player 1 menu button to the scene
    QGraphicsProxyWidget *player1MenuButtonProxy = scene->addWidget(player1MenuButton);
    player1MenuButtonProxy->setPos(620, 150); // Position in scene coordinates
    player1MenuButtonProxy->setZValue(100);   // Bring to front

    // Player 2 Menu Button
    QPushButton *player2MenuButton = new QPushButton("Humain");
    QMenu *player2Menu = new QMenu();
    QAction *player2HumainAction = player2Menu->addAction("Humain");
    QAction *player2IAAction = player2Menu->addAction("IA");
    player2MenuButton->setMenu(player2Menu);

    // Connect actions to update Player 2 button text
    QObject::connect(player2HumainAction, &QAction::triggered, [player2MenuButton]() {
        player2MenuButton->setText("Humain");
    });
    QObject::connect(player2IAAction, &QAction::triggered, [player2MenuButton]() {
        player2MenuButton->setText("IA");
    });

    // Add Player 2 menu button to the scene
    QGraphicsProxyWidget *player2MenuButtonProxy = scene->addWidget(player2MenuButton);
    player2MenuButtonProxy->setPos(620, 200); // Position in scene coordinates
    player2MenuButtonProxy->setZValue(100);   // Bring to front


    // Nombre de retours arrière
    QGraphicsTextItem* undoLabel = new QGraphicsTextItem("Nombre de retours arrière :");
    undoLabel->setPos(200, 300);
    scene->addItem(undoLabel);

    undoSpinBox = new QSpinBox();
    undoSpinBox->setRange(0, 10);
    undoSpinBox->setValue(0);  // Par défaut 0
    undoSpinBox->setGeometry(500, 300, 100, 30);
    QGraphicsProxyWidget* undoSpinBoxProxy = scene->addWidget(undoSpinBox);
    undoSpinBoxProxy->setPos(500, 300);

    // Extensions
    QGraphicsTextItem* extensionLabel = new QGraphicsTextItem("Extensions disponibles :");
    extensionLabel->setPos(200, 400);
    scene->addItem(extensionLabel);

    extension1CheckBox = new QCheckBox("Ladybug");
    extension1CheckBox->setGeometry(400, 400, 150, 30);
    QGraphicsProxyWidget* extension1CheckBoxProxy = scene->addWidget(extension1CheckBox);
    extension1CheckBoxProxy->setPos(400, 400);

    extension2CheckBox = new QCheckBox("Mosquito");
    extension2CheckBox->setGeometry(400, 450, 150, 30);
    QGraphicsProxyWidget* extension2CheckBoxProxy = scene->addWidget(extension2CheckBox);
    extension2CheckBoxProxy->setPos(400, 450);

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

    // Autres paramètres
    int undoCount = undoSpinBox->value();
    bool extension1Enabled = extension1CheckBox->isChecked();
    bool extension2Enabled = extension2CheckBox->isChecked();

    if (extension1Enabled){
        qDebug()<<"Ladybug"<<"\n";
        addType([](){return new Ladybug;}, Ladybug::getMax());
    }
    if (extension2Enabled){
        addType([](){return new Mosquito;}, Mosquito::getMax());
    }

    // Afficher les paramètres dans le debug
    qDebug() << "Player 1: " << player1Name << "Type:" << player1Type;
    qDebug() << "Player 2: " << player2Name << "Type:" << player2Type;
    qDebug() << "Undo count:" << undoCount;
    qDebug() << "Extension 1:" << extension1Enabled;
    qDebug() << "Extension 2:" << extension2Enabled;

    start();
}

/*void Game::undoLastAction() {
    if (history.isEmpty()) {
        QMessageBox::warning(this, "Retour","Pas d'action de retour en arrière !");
        return;
    }
    restoreState();

    // Redraw the board based on restored state
    scene->clear();
    hexBoard->placeHexes(200, 30, 15, 15);
    drawGUI();
    drawpawns();
} */



/*void Game::saveGame() {
    qDebug() << "Saving game state...";
    qDebug() << "Player 1 Pawns:";
    for (Hex* pawn : player1pawns) {
        qDebug() << "P1 Pawn " << pawn->getInsectType() << " at ("
                 << pawn->pos().x() << ", " << pawn->pos().y() << ")";
    }

    qDebug() << "Player 2 Pawns:";
    for (Hex* pawn : player2pawns) {
        qDebug() << "P2 Pawn " << pawn->getInsectType() << " at ("
                 << pawn->pos().x() << ", " << pawn->pos().y() << ")";
    }

    QFile file("savegame.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << "Player 1: " << player1Name << " (" << player1Type << ")\n";
        out << "Player 2: " << player2Name << " (" << player2Type << ")\n";
        out << "Undo actions remaining: " << numRetours << "\n";
        out << "Whose turn: " << getWhosTurn() << "\n";

        // Save the pawns and their positions
        for (Hex* pawn : player1pawns) {
            out << "P1 Pawn " << pawn->getInsectType() << " at "
                << pawn->pos().x() << "," << pawn->pos().y() << "\n";
        }
        for (Hex* pawn : player2pawns) {
            out << "P2 Pawn " << pawn->getInsectType() << " at "
                << pawn->pos().x() << "," << pawn->pos().y() << "\n";
        }

        file.close();
        QMessageBox::information(this, "Enregistrement", "Le jeu a bien été sauvegardé.");
    } else {
        QMessageBox::warning(this, "Enregistrement", "Erreur, le jeu n'a pas été sauvegardé.");
    }
} */

Hex* Game::cloneHex(Hex* original) {
    Hex* copy = new Hex();
    copy->setInsectType(original->getInsectType());
    copy->setOwner(original->getOwner());
    copy->setColor(original->getColor());
    copy->setIsPlaced(original->getIsPlaced());
    copy->setPos(original->pos()); // Use setPos() to set the position
    return copy;
}

// Save the current game state into the history stack
/*void Game::saveState() {
    QList<Hex*> p1Copy;
    QList<Hex*> p2Copy;

    for (Hex* pawn : player1pawns) {
        p1Copy.append(cloneHex(pawn));
    }
    for (Hex* pawn : player2pawns) {
        p2Copy.append(cloneHex(pawn));
    }

    history.push(new Memento(whosTurn_, p1Copy, p2Copy));
    qDebug() << "State saved. Current turn: " << whosTurn_;
} */


// Restaurer le dernier état
/*void Game::restoreState() {
    if (!history.isEmpty()) {
        Memento* memento = history.pop();
        whosTurn_ = memento->getWhosTurn();
        player1pawns = memento->getPlayer1Pawns();
        player2pawns = memento->getPlayer2Pawns();

        drawpawns();
        setWhosTurn(whosTurn_);
        delete memento;
    } else {
        QMessageBox::warning(this, "Retour","Pas d'action de retour en arrière !");
    }
} */


void Game::createInsects(){
    addType([](){return new QueenBee;}, QueenBee::getMax());
    addType([](){return new Ant;}, Ant::getMax());
    addType([](){return new Beetle;}, Beetle::getMax());
    addType([](){return new Grasshopper;}, Grasshopper::getMax());
    addType([](){return new Spider;}, Spider::getMax());


    for (const auto& insectInfo : insectTypes) {
        for (unsigned int i = 0; i < insectInfo.second; i++) {
            // Blanc
            Insect* blanc = insectInfo.first();
            blanc->setColor(true);
            insectsBlanc.push_back(blanc);

            // Noir
            Insect* noir = insectInfo.first();
            noir->setColor(false);
            insectsNoir.push_back(noir);
        }
    }

    for(int i=0; i<insectsBlanc.size(); i++){
        qDebug()<<"type insect:"<<insectsBlanc[i]->getType();

    }
}

void Game::incCompteur(bool color){
    if (color == 1)   ajouterCompteurDeToursBlanc();
    if (color == 0)   ajouterCompteurDeToursNoir();
}

int Game::getColorToPlay(){
    if(getWhosTurn() == player1Name){
        return 1;
    }
    return 0;
}

void Game::exchangeSpot(HexBoard* hb, Hex* h1, Hex* h2) {

    QPointF temp = h1->pos();
    QPoint temp1 = h1->getCoord();
    //swap des positions
    h1->setPos(h2->pos());
    h2->setPos(temp);
    //swap des coordonnées
    h1->setCoord(h2->getCoord().x(), h2->getCoord().y());
    h2->setCoord(temp1.x(), temp1.y());
    qDebug() << "Swapped coordinates. New h1 coord:" << h1->getCoord() << ", New h2 coord:" << h2->getCoord();
    h2->majLabelCoord();
    qDebug() << "Finished exchangeSpot function.";
}

//methode qui renvoit true si la reine de la couleur color est entouree
bool Game::isQueenSurrounded(bool color) const{
    if (QueenBee::estPasAuMax(color)){ return false; }
    std::vector<const BoardSpot*> piecesPosees = board.piecejoueur(color);
    for (size_t i = 0; i<piecesPosees.size(); i++){
        if (piecesPosees[i]->getInsect()->getType()=="queenbee"){
            std::pair<int, int> coords = piecesPosees[i]->getCoordinates();
            if(board.trouverVoisinsInsects(coords.first,coords.second).size()>=6){ return true; }
        }
    }
    return false;
}
