#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // dessiner le rectangle
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // texte
    text = new QGraphicsTextItem(name,this);

    // Définir la police et la taille du texte
    this->setFontSize(10);

    //Pour positionner le texte au milieu
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // rendre le bouton interactif aux events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}

void Button::setFontSize(int size) {
    QFont font = text->font(); // Get the current font
    font.setPointSize(size);   // Set the new font size
    text->setFont(font);       // Apply the updated font to the text item
}
