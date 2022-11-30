//
// Created by eric on 09.11.22.
//

#include "Container.h"
#include<thread>

namespace Physic {
    unsigned int IX(unsigned int x, unsigned int y, unsigned int N);

    Container::Container() = default;

    void Init();

    Container::Container(float dt, float diff, float visc) {
        this->dt = dt;
        this->diff = diff;
        this->visc = visc;

        Physic::Init();
        Physic::Container::InitArr(this->px, GridSize);
        Physic::Container::InitArr(this->py, GridSize);
        Physic::Container::InitArr(this->x, GridSize);
        Physic::Container::InitArr(this->y, GridSize);
        Physic::Container::InitArr(this->previousDensity, GridSize);
        Physic::Container::InitArr(this->density, GridSize);
    }



    void Container::InitArr(float arr[], int size) {
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }

    void Container::AddDensity(float xPos, float yPos, float amount) {
        this->density[IX((int)xPos, (int)yPos, Physic::Container::size)] += amount;
    }

    void Container::AddVelocity(float xPos, float yPos, float vx, float vy) {
        unsigned int index = IX((int)xPos, (int)yPos, Physic::Container::size);

        this->x[index] += vx;
        this->y[index] += vy;
    }

    void Container::Step() {
        this->diff+=0.00000001f;
        const int constSize = Physic::Container::size;
        const int iter = Physic::Container::iterations;

#if MULTITHREADED == 1
        std::thread threadXDiffuse(Physic::Physics::Diffuse,Boundry::XAxis, this->px, this->x, this->visc, this->dt, iter, constSize);
        std::thread threadYDiffuse(Physic::Physics::Diffuse,Boundry::YAxis, this->py, this->y, this->visc, this->dt, iter, constSize);
        threadXDiffuse.join();
        threadYDiffuse.join();
#else
        Physic::Physics::Diffuse(Boundry::XAxis, this->px, this->x, this->visc, this->dt, iter, constSize);
        Physic::Physics::Diffuse(Boundry::YAxis, this->py, this->y, this->visc, this->dt, iter, constSize);
#endif
        Physic::Physics::Project(this->px, this->py, this->x, this->y, iter, Physic::Container::size);
#if MULTITHREADED == 1
        std::thread threadXAdvect(Physic::Physics::Advect, Boundry::XAxis, this->x, this->px, this->px, this->py, this->dt, constSize);
        std::thread threadYAdvect(Physic::Physics::Advect, Boundry::YAxis, this->y, this->py, this->px, this->py, this->dt, constSize);
        threadXAdvect.join();
        threadYAdvect.join();
#else
        Physic::Physics::Advect(Boundry::XAxis, this->x, this->px, this->px, this->py, this->dt, constSize);
        Physic::Physics::Advect(Boundry::YAxis, this->y, this->py, this->px, this->py, this->dt, constSize);
#endif
        Physic::Physics::Project(this->x, this->y, this->px, this->py, iter, constSize);


#if MULTITHREADED == 1
        std::thread threadNoneDiffuse(Physic::Physics::Diffuse, Boundry::None, this->previousDensity, this->density, this->diff, this->dt, iter, constSize);
        std::thread threadNoneAdvect(Physic::Physics::Advect, Boundry::None, this->density, this->previousDensity, this->x, this->y, this->dt, constSize);
        threadNoneDiffuse.join();
        threadNoneAdvect.join();
#else
        Physic::Physics::Diffuse(Boundry::None, this->previousDensity, this->density, this->diff, this->dt, iter, constSize);
        Physic::Physics::Advect(Boundry::None, this->density, this->previousDensity, this->x, this->y, this->dt, constSize);
#endif
    }

    float Container::MapToRange(float val, float minIn, float maxIn, float minOut, float maxOut) {
        float x = (val - minIn) / (maxIn - minIn);
        float result = minOut + (maxOut - minOut) * x;
        return (result < minOut) ? minOut : (result > maxOut) ? maxOut : result;
    }

    void Container::FadeDensity(float delta) {
        for (int i = 0; i < Physic::Container::size; i++) {
            float d = this->density[i];
            density[i] = (d - delta < 0) ? 0 : d - delta;
        }
    }


    void Container::addVelocityAtTop(float vector){
        for (int i = 1; i < Physic::Container::size - 1; i++) {
            this->py[Physic::LookUP::IJBuffer[i][1]] += vector;
        }

    }
} // Physic