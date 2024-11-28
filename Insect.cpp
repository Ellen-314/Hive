#include "Insect.h"

using namespace std;

// Constructeur
Insect::Insect()
    : neighborTop(nullptr), neighborBottom(nullptr), neighborTopRight(nullptr),
    neighborBottomRight(nullptr), neighborTopLeft(nullptr), neighborBottomLeft(nullptr),
    covered(false), color(false) {}

// Setter and Getter pour neighborTop
void Insect::setNeighborTop(Insect* insect) {
    neighborTop = insect;
}

Insect* Insect::getNeighborTop() const {
    return neighborTop;
}

// Setter and Getter pour neighborBottom
void Insect::setNeighborBottom(Insect* insect) {
    neighborBottom = insect;
}

Insect* Insect::getNeighborBottom() const {
    return neighborBottom;
}

// Setter and Getter pour neighborTopRight
void Insect::setNeighborTopRight(Insect* insect) {
    neighborTopRight = insect;
}

Insect* Insect::getNeighborTopRight() const {
    return neighborTopRight;
}

// Setter and Getter pour neighborBottomRight
void Insect::setNeighborBottomRight(Insect* insect) {
    neighborBottomRight = insect;
}

Insect* Insect::getNeighborBottomRight() const {
    return neighborBottomRight;
}

// Setter and Getter pour neighborTopLeft
void Insect::setNeighborTopLeft(Insect* insect) {
    neighborTopLeft = insect;
}

Insect* Insect::getNeighborTopLeft() const {
    return neighborTopLeft;
}

// Setter and Getter pour neighborBottomLeft
void Insect::setNeighborBottomLeft(Insect* insect) {
    neighborBottomLeft = insect;
}

Insect* Insect::getNeighborBottomLeft() const {
    return neighborBottomLeft;
}

// Setter and Getter pour covered
bool Insect::isCovered() const {
    return covered;
}

void Insect::setCovered(bool cov) {
    covered = cov;
}

// Setter and Getter pour color
bool Insect::getColor() const {
    return color;
}

void Insect::setColor(bool col) {
    color = col;
}

Insect::~Insect() {}

