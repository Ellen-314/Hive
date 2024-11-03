#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructeur
    Game(QWidget* parent=NULL);

    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);
    void pickUppawn(Hex* pawn);
    void placepawn(Hex* hexToReplace);
    void nextPlayersTurn();
    void removeFromDeck(Hex* pawn,QString player);
    void addPawnToPlayer(QString player, QString insectType, int quantity, QList<Hex*>& pawnList);
    bool createReplacementPawn(QString insectType, QString player);

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    QGraphicsScene* scene;
    HexBoard* hexBoard;
    Hex* pawnToPlace;
    QPointF originalPos;

public slots:
    void start();

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewpawn(QString player);
    void createInitialpawns();
    void drawpawns();

    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex* > player1pawns;     // Liste des pions visibles du joueur 1
    QList<Hex* > player2pawns;     // Liste des pions visibles du joueur 2
    QList<Hex*> player1RemainingPawns;    // Liste des pions en réserve du joueur 1
    QList<Hex*> player2RemainingPawns;    // Liste des pions en réserve du joueur 2

};

#endif // GAME_H
