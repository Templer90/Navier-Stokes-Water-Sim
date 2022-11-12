//
// Created by eric on 09.11.22.
//

#ifndef WATER_PHYSICS_H
#define WATER_PHYSICS_H

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

        static void Advect(Boundry b, float d[], float d0[], float vx[], float vy[], float dt, int N);
    };

} // Physic

#endif //WATER_PHYSICS_H
