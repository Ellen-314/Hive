#ifndef COLORDICTIONNARY_H
#define COLORDICTIONNARY_H

#include <QMap>
#include <QString>
#include <QColor>

class ColorDictionary
{
public:
    // Returns the color map
    static QMap<QString, QColor> getColorMap();

    // Gets a color by name, or a default color if not found
    static QColor getColor(const std::string colorName);
};
#endif // COLORDICTIONNARY_H
