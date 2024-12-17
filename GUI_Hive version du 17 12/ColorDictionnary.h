#ifndef COLORDICTIONNARY_H
#define COLORDICTIONNARY_H

#include <QMap>
#include <QString>
#include <QColor>

class ColorDictionary
{
public:
    // retourne la color map
    static QMap<QString, QColor> getColorMap();

    // getter avec le nom et retourne noir sinon
    static QColor getColor(const std::string colorName);
};
#endif // COLORDICTIONNARY_H
