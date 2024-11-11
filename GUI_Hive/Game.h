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
#include "Button.h"  // Ensure this includes Button if it's a custom class

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // Constructor
    Game(QWidget* parent = nullptr);

    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);
    void pickUppawn(Hex* pawn);
    void placepawn(Hex* hexToReplace);
    void nextPlayersTurn();
    void removeFromDeck(Hex* pawn, QString player);
    void addPawnToPlayer(QString player, QString insectType, int quantity, QList<Hex*>& pawnList);
    bool createReplacementPawn(QString insectType, QString player);

    // Events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    QGraphicsScene* scene;
    HexBoard* hexBoard;
    Hex* pawnToPlace;
    QPointF originalPos;

public slots:
    void start();
    void displayGameSetupMenu();
    void undoLastAction();  // New slot for undo
    void saveGame();        // New slot for save

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

    QLineEdit* player1NameInput;
    QLineEdit* player2NameInput;
    QComboBox* player1TypeComboBox;
    QComboBox* player2TypeComboBox;
    QSpinBox* undoSpinBox;
    QCheckBox* extension1CheckBox;
    QCheckBox* extension2CheckBox;

    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex*> player1pawns;
    QList<Hex*> player2pawns;
    QList<Hex*> player1RemainingPawns;
    QList<Hex*> player2RemainingPawns;

    // Undo and save
    int numRetours;  // Number of undo actions left
    QList<QGraphicsItem*> history;  // Track game state changes for undo
};

#endif // GAME_H
