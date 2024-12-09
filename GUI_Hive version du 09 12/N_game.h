#ifndef N_GAME_H
#define N_GAME_H
#include "Memento.h"
#include <QStack>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include "Button.h"

#include "Board.h"
#include "Insect.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // Constructeur
    Game(QWidget* parent = nullptr);
    // Destructeur
    ~Game();

    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString player);
    void pickUppawn(Hex* pawn);
    Board& getPlateau(){return board;};
    void placepawn(Hex* hexToReplace);
    void nextPlayersTurn();
    void removeFromDeck(Hex* pawn, QString player);
    void addPawnToPlayer(QString player, QString insectType, int quantity, QList<Hex*>& pawnList);
    bool createReplacementPawn(QString insectType, QString player);
    Hex* cloneHex(Hex* original);

    // Events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    //Memento
    void saveState();
    void restoreState();

    //Méthode pour ajouter les types d'insects à la liste de types.
    void addType( std::function<Insect*()> cree, int maximum){insectTypes.push_back(std::make_pair(cree, maximum));}

    // Méthode pour ajouter un insecte à une case
    void ajouterInsecte(int x, int y);

    static unsigned int getCompteurDeToursBlanc(){return compteurDeToursBlanc;}
    static unsigned int getCompteurDeToursNoir(){return compteurDeToursNoir;}
    static void ajouterCompteurDeToursBlanc(){compteurDeToursBlanc++;}
    static void ajouterCompteurDeToursNoir(){compteurDeToursNoir++;}
    static void enleverCompteurDeToursBlanc(){compteurDeToursBlanc--;}
    static void enleverCompteurDeToursNoir(){compteurDeToursNoir--;}
    void poserInsect(Hex *source, Hex *destination);
    std::vector<Insect*> getInsectNoirMod(){return insectsNoir;}
    std::vector<Insect*> getInsectBlancMod(){return insectsBlanc;}

    //fonction qui permet de mettre à jour le tour du joueur;
    void incCompteur(bool color);
    int getColorToPlay();


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
    void createInsects();
    void createInitialpawns();
    void drawpawns();
    void startGameWithSettings();

    Board board;
    // Vecteurs des insectes restant a poser
    std::vector<Insect*> insectsBlanc;
    std::vector<Insect*> insectsNoir;

    //liste contenant tout les types d'insects et leur nombre max
    std::vector<std::pair< std::function<Insect*()>, unsigned int>> insectTypes;

    static unsigned int compteurDeToursBlanc;
    static unsigned int compteurDeToursNoir;

    //Memento
    QStack< Memento*> history;
    void storeCurrentState();

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
    //QList<QGraphicsItem*> history;  // Track game state changes for undo
};

/*class GameState {
public:
    QList<Hex*> player1Pawns;
    QList<Hex*> player2Pawns;
    QString currentTurn;
    int undoCount;

    // Constructor to save state
    GameState(const QList<Hex*>& p1, const QList<Hex*>& p2, const QString& turn, int undos)
        : player1Pawns(p1), player2Pawns(p2), currentTurn(turn), undoCount(undos) {}
}; */


#endif // N_GAME_H
