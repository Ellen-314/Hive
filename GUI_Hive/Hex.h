#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex: public QGraphicsPolygonItem{
public:
    // constructeur
    Hex(QGraphicsItem* parent=NULL);
    // getters
    int getAttackOf(int side);
    bool getIsPlaced();
    QString getOwner();

    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // setters
    void setAttackOf(int side, int attack);
    void setOwner(QString player);
    void setIsPlaced(bool b);
    void setInsectType(const QString& type);
    QString getInsectType() const { return insectType; }

private:
    bool isPlaced;
    QGraphicsTextItem* labelText;
    QString insectType;
    QPixmap insectImage;
    QString owner;
};

#endif // HEX_H
