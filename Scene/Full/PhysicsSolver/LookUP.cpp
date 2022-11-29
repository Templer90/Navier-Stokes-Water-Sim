//
// Created by eric on 13.11.22.
//

#ifndef WATER_LOOKUP_CPP
#define WATER_LOOKUP_CPP

#include "../../../Constants.h"
#include "../IX.h"

namespace Physic {
    struct LookUP {
        inline static int **IJBuffer = {};

        inline static int *AllIndices = {};
        inline static int MaxIndex = 0;

        inline static int IJ_00 = 0;
        inline static int IJ_10 = 0;
        inline static int IJ_01 = 0;

        inline static int IJ_0N = 0;
        inline static int IJ_N0 = 0;
        inline static int IJ_NN = 0;

        explicit LookUP(const unsigned int N) {
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

            AllIndices = new int[(N - 2) * (N - 2)];
            int index = 0;
            for (int j = 1; j < N - 1; j++) {
                for (int i = 1; i < N - 1; i++) {
                    AllIndices[index] = IJBuffer[i][j];
                    index++;
                }
            }
            MaxIndex = index - 1;
        }
    };
}


#endif //WATER_LOOKUP_CPP
