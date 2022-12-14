//
// Created by eric on 09.11.22.
//

#ifndef WATER_PHYSICS_H
#define WATER_PHYSICS_H

#include "../../../Constants.h"
#include "../IX.h"
#include "LookUP.cpp"

namespace Physic {
    enum Boundry {
        None = 0,
        XAxis = 1,
        YAxis = 2
    };

    class Physics {
    private:
        static void LinSolve(Boundry b, float x[], const float x0[], float a, float c, int iter, int N);

        static void SetBnd(Boundry b, float x[], int N);

    public:
        static void Diffuse(Boundry b, float x[], float x0[], float diff, float dt, int iter, int N);

        static void Project(float vx[], float vy[], float p[], float div[], int iter, int N);

        static void Advect(Boundry b, float d[], const float d0[], const float vx[], const float vy[], float dt, int N);

        static void AddConstantVector( float x[], float vector);

        inline static LookUP lookup=LookUP(GridWidth);
    };

} // Physic

#endif //WATER_PHYSICS_H
