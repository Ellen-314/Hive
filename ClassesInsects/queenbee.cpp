#include "QueenBee.h"

bool QueenBee::isCompletelySurrounded() const {
    return neighborTop && neighborBottom &&
           neighborTopRight && neighborBottomRight &&
           neighborTopLeft && neighborBottomLeft;
}
