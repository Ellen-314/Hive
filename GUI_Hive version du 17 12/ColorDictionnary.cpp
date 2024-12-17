#include "ColorDictionnary.h"

// Fonction statique pour initialiser la color map
static QMap<QString, QColor> initializeColorMap()
{
    QMap<QString, QColor> colorMap;
    colorMap["red"] = QColor(Qt::red);
    colorMap["green"] = QColor(Qt::green);
    colorMap["blue"] = QColor(Qt::blue);
    colorMap["black"] = QColor(Qt::black);
    colorMap["white"] = QColor(Qt::white);
    colorMap["yellow"] = QColor(Qt::yellow);
    colorMap["cyan"] = QColor(Qt::cyan);
    colorMap["magenta"] = QColor(Qt::magenta);
    return colorMap;
}

//instance statique de la color map
static QMap<QString, QColor> colorMap = initializeColorMap();

// retourne toute la color map
QMap<QString, QColor> ColorDictionary::getColorMap()
{
    return colorMap;
}

// retourne la couleur d'un nom particuler sinon noir
QColor ColorDictionary::getColor(const std::string colorName)
{
    QString colorNameQS = QString::fromStdString(colorName);
    return colorMap.value(colorNameQS, QColor(Qt::black)); // Par defaut noir si pas trouvé
}
