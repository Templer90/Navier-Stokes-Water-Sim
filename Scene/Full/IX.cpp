//
// Created by eric on 09.11.22.
//

#include "IX.h"
#include "../../Constants.h"

namespace Physic{

    unsigned int IX(unsigned int x, unsigned int y, const unsigned int N) {
        //return (y * N) + x;
        return (y << Power) + x;
        /*if (x < 0) { x = 0; }
        if (x > N - 1) { x = N - 1; }

        if (y < 0) { y = 0; }
        if (y > N - 1) { y = N - 1; }

        return (y * N) + x;*/
    }
}