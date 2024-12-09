#include "ColorDictionnary.h"

// Static function to initialize the color map
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

// Static color map instance
static QMap<QString, QColor> colorMap = initializeColorMap();

// Returns the entire color map
QMap<QString, QColor> ColorDictionary::getColorMap()
{
    return colorMap;
}

// Returns the color for a given name, or black if not found
QColor ColorDictionary::getColor(const std::string colorName)
{
    QString colorNameQS = QString::fromStdString(colorName);
    return colorMap.value(colorNameQS, QColor(Qt::black)); // Default to black if not found
}
