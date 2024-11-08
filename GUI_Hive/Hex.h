#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex: public QGraphicsPolygonItem{
public:
    // constructeur
    Hex(QGraphicsItem* parent=NULL);
    // getters
    bool getIsPlaced();
    QString getOwner();
    QColor getColor() const;

    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // setters
    void setOwner(QString player);
    void setIsPlaced(bool b);
    void setInsectType(const QString& type);
    void setColor(const QColor& color);
    QString getInsectType() const { return insectType; }

private:
    bool isPlaced;
    QGraphicsTextItem* labelText;
    QString insectType;
    QPixmap insectImage;
    QString owner;
    QColor color;
};

#endif // HEX_H
