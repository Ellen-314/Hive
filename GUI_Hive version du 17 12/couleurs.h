#ifndef COULEURS_H
#define COULEURS_H

#include <QMap>
#include <QString>
#include <QColor>

class ColorDictionary
{
public:
    // Returns the color map
    static QMap<QString, QColor> getColorMap();

    // Gets a color by name, or a default color if not found
    static QColor getColor(const QString &colorName);
};







#endif // COULEURS_H
