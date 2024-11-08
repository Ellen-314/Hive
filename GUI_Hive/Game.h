#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

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
    void displayGameSetupMenu();

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewpawn(QString player);
    void createInitialpawns();
    void drawpawns();
    void startGameWithSettings();

    QString player1Name;
    QString player2Name;
    QString player1Type;
    QString player2Type;

    QLineEdit* player1NameInput; // Champ de texte pour le nom du joueur 1
    QLineEdit* player2NameInput; // Champ de texte pour le nom du joueur 2
    QComboBox* player1TypeComboBox;  // Type de joueur 1 (Humain/IA)
    QComboBox* player2TypeComboBox;  // Type de joueur 2 (Humain/IA)
    QSpinBox* undoSpinBox;  // Sélecteur pour le nombre de retours arrière possibles
    QCheckBox* extension1CheckBox;  // Checkbox pour activer/désactiver l'extension 1
    QCheckBox* extension2CheckBox;  // (Optionnel) Pour une autre extension si nécessaire
    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex* > player1pawns;     // Liste des pions visibles du joueur 1
    QList<Hex* > player2pawns;     // Liste des pions visibles du joueur 2
    QList<Hex*> player1RemainingPawns;    // Liste des pions en réserve du joueur 1
    QList<Hex*> player2RemainingPawns;    // Liste des pions en réserve du joueur 2

};

#endif // GAME_H
