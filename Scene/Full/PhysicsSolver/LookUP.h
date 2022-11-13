//
// Created by eric on 13.11.22.
//

#ifndef WATER_LOOKUP_H
#define WATER_LOOKUP_H

#include "../../../Constants.h"
#include "../IX.h"

namespace Physic{
    struct LookUP {
        inline static int** IJBuffer={};
        inline static int** JIBuffer={};
        LookUP(){
            constexpr int N = GridWidth;
            IJBuffer = new int *[N];
            JIBuffer = new int *[N];

            for (int i = 0; i < N; i++) {
                IJBuffer[i] = new int[N];
                JIBuffer[i] = new int[N];
                for (int j = 0; j < N; j++) {
                    IJBuffer[i][j] = (int) IX(i, j, N);
                    JIBuffer[i][j] = (int) IX(j, i, N);
                }
            }
        }
    };
}



#endif //WATER_LOOKUP_H
