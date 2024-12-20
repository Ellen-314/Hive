#ifndef N_GAME_H
#define N_GAME_H
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
#include <QGraphicsProxyWidget>
#include <QStyleFactory>
#include <QPushButton>

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
    bool isQueenSurrounded(bool color) const;



    // Events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    //Memento
    void saveState();
    void restoreState();

    //Méthode pour ajouter les types d'insects à la liste de types.
    void addType( std::function<Insect*()> cree, int maximum){insectTypes.push_back(std::make_pair(cree, maximum));}

    // Méthode pour ajouter un insecte à une case
    //void ajouterInsecte(int x, int y);

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

    void exchangeSpot(HexBoard* hb, Hex* h1, Hex* h2);


    QGraphicsScene* scene;
    HexBoard* hexBoard;
    Hex* pawnToPlace;
    Hex* pawnToMove;
    QPointF originalPos;

public slots:
    void start();
    void displayGameSetupMenu();

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

    QString player1Name;
    QString player2Name;
    QString player1Type;
    QString player2Type;


    QLineEdit* player1NameInput;
    QLineEdit* player2NameInput;
    QPushButton *player1MenuButton;
    QPushButton *player2MenuButton;
    QSpinBox* undoSpinBox;
    QCheckBox* extension1CheckBox;
    QCheckBox* extension2CheckBox;

    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex*> player1pawns;
    QList<Hex*> player2pawns;
    QList<Hex*> player1RemainingPawns;
    QList<Hex*> player2RemainingPawns;


    int numRetours;

};



#endif // N_GAME_H
