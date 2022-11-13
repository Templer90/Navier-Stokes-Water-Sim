//
// Created by eric on 09.11.22.
//

#include "Container.h"

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
        Physic::Physics::Diffuse(Boundry::XAxis, this->px, this->x, this->visc, this->dt, Physic::Container::iterations, Physic::Container::size);
        Physic::Physics::Diffuse(Boundry::YAxis, this->py, this->y, this->visc, this->dt, Physic::Container::iterations, Physic::Container::size);

        Physic::Physics::Project(this->px, this->py, this->x, this->y, Physic::Container::iterations, Physic::Container::size);

        Physic::Physics::Advect(Boundry::XAxis, this->x, this->px, this->px, this->py, this->dt, Physic::Container::size);
        Physic::Physics::Advect(Boundry::YAxis, this->y, this->py, this->px, this->py, this->dt, Physic::Container::size);

        Physic::Physics::Project(this->x, this->y, this->px, this->py, Physic::Container::iterations, Physic::Container::size);

        Physic::Physics::Diffuse(Boundry::None, this->previousDensity, this->density, this->diff, this->dt, Physic::Container::iterations, Physic::Container::size);
        Physic::Physics::Advect(Boundry::None, this->density, this->previousDensity, this->x, this->y, this->dt, Physic::Container::size);
    }

    float Container::MapToRange(float val, float minIn, float maxIn, float minOut, float maxOut) {
        float x = (val - minIn) / (maxIn - minIn);
        float result = minOut + (maxOut - minOut) * x;
        return (result < minOut) ? minOut : (result > maxOut) ? maxOut : result;
    }

    void Container::FadeDensity() {
        for (int i = 0; i < Physic::Container::size; i++) {
            float d = this->density[i];
            density[i] = (d - 0.05f < 0) ? 0 : d - 0.05f;
        }
    }
} // Physic