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
        float dt{};
        float diff{};
        float visc{};
        float previousDensity[GridSize]{};

        static void InitArr(float arr[], int size);

    public:
        static const int size = GridWidth;
        static const int iterations = 16;
        float density[GridSize]{};
        float x[GridSize]{};
        float y[GridSize]{};
        float px[GridSize]{};
        float py[GridSize]{};


        Container();

        Container(float dt, float diff, float visc);

        void AddDensity(float xPos, float yPos, float amount);

        void AddVelocity(float Ppos, float y, float px, float py);

        void Step();

        void FadeDensity();


        static float MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut);

    };


} // Physic

#endif //WATER_CONTAINER_H
