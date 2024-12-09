#ifndef MEMENTO_H
#define MEMENTO_H

#include <QString>
#include <QList>
#include "Hex.h"

class Memento {
public:
    Memento(QString whosTurn, QList<Hex*> p1Pawns, QList<Hex*> p2Pawns)
        : whosTurn_(whosTurn), player1Pawns_(p1Pawns), player2Pawns_(p2Pawns) {}

    QString getWhosTurn() const { return whosTurn_; }
    QList<Hex*> getPlayer1Pawns() const { return player1Pawns_; }
    QList<Hex*> getPlayer2Pawns() const { return player2Pawns_; }

private:
    QString whosTurn_;
    QList<Hex*> player1Pawns_;
    QList<Hex*> player2Pawns_;
};

#endif // MEMENTO_H
