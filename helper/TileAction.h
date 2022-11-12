//
// Created by eric on 07.11.22.
//

#ifndef WATER_TILEACTION_H
#define WATER_TILEACTION_H

#include <functional>
#include <string>
#include "../Tile.h"

namespace helper {
    struct TileAction {
        std::function<void(Tile *, float)> action;
        std::string notice;
    };
}


#endif //WATER_TILEACTION_H
