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

        inline static int IJ_00=0;
        inline static int IJ_10=0;
        inline static int IJ_01=0;

        inline static int IJ_0N=0;
        inline static int IJ_N0=0;
        inline static int IJ_NN=0;

        LookUP(){
            constexpr int N = GridWidth;
            IJBuffer = new int *[N];

            for (int i = 0; i < N; i++) {
                IJBuffer[i] = new int[N];

                for (int j = 0; j < N; j++) {
                    IJBuffer[i][j] = (int) IX(i, j, N);
                }
            }

            IJ_00 = IJBuffer[0][0];
            IJ_10 = IJBuffer[1][0];
            IJ_01 = IJBuffer[0][1];

            IJ_0N = IJBuffer[0][N - 1];
            IJ_N0 = IJBuffer[N - 1][0];
            IJ_NN = IJBuffer[N - 1][N - 1];
        }
    };
}



#endif //WATER_LOOKUP_H
