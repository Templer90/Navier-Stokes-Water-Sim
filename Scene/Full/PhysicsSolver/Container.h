//
// Created by eric on 09.11.22.
//

#ifndef WATER_CONTAINER_H
#define WATER_CONTAINER_H

#include "../../../Constants.h"
#include "Physics.h"

namespace Physic {

    class Container {
    private:
        Physics physics;

        float dt{};
        float diff{};
        float visc{};

        float px[GridSize]{};
        float py[GridSize]{};

        float previousDensity[GridSize]{};

        static void InitArr(float arr[], int size);

    public:
        static const int size = GridWidth;
        static const int iterations = 16;

        Container();

        Container(float dt, float diff, float visc);

        float density[GridSize]{};

        void AddDensity(float x, float y, float amount);

        void AddVelocity(float x, float y, float px, float py);

        void Step();

        void FadeDensity(int size);


        static float MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut);

        float x[GridSize]{};
        float y[GridSize]{};
    };


} // Physic

#endif //WATER_CONTAINER_H
