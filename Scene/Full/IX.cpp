//
// Created by eric on 09.11.22.
//

#include "IX.h"

namespace Physic{

    int IX(int x, int y, int N) {
        return (y * N) + x;
        /*if (x < 0) { x = 0; }
        if (x > N - 1) { x = N - 1; }

        if (y < 0) { y = 0; }
        if (y > N - 1) { y = N - 1; }

        return (y * N) + x;*/
    }
}