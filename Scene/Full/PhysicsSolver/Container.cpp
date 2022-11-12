//
// Created by eric on 09.11.22.
//

#include "Container.h"

namespace Physic {
    const int IX(int x, int y, int N);

    Container::Container() {}
    Container::Container(float dt, float diff, float visc) {
        this->dt = dt;
        this->diff = diff;
        this->visc = visc;

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

    void Container::AddDensity(float xpos, float ypos, float amount) {
        this->density[IX(xpos, ypos, Physic::Container::size)] += amount;
    }

    void Container::AddVelocity(float xpos, float ypos, float px, float py) {
        int index = IX(xpos, ypos, Physic::Container::size);

        this->x[index] += px;
        this->y[index] += py;
    }

    void Container::Step() {
        this->physics.Diffuse(Boundry::XAxis, this->px, this->x, this->visc, this->dt, Physic::Container::iterations, Physic::Container::size);
        this->physics.Diffuse(Boundry::YAxis, this->py, this->y, this->visc, this->dt, Physic::Container::iterations, Physic::Container::size);

        this->physics.Project(this->px, this->py, this->x, this->y, Physic::Container::iterations, Physic::Container::size);

        this->physics.Advect(Boundry::XAxis, this->x, this->px, this->px, this->py, this->dt, Physic::Container::size);
        this->physics.Advect(Boundry::YAxis, this->y, this->py, this->px, this->py, this->dt, Physic::Container::size);

        this->physics.Project(this->x, this->y, this->px, this->py, Physic::Container::iterations, Physic::Container::size);

        this->physics.Diffuse(Boundry::None, this->previousDensity, this->density, this->diff, this->dt, Physic::Container::iterations, Physic::Container::size);
        this->physics.Advect(Boundry::None, this->density, this->previousDensity, this->x, this->y, this->dt, Physic::Container::size);
    }

    float Container::MapToRange(float val, float minIn, float maxIn, float minOut, float maxOut) {
        float x = (val - minIn) / (maxIn - minIn);
        float result = minOut + (maxOut - minOut) * x;
        return (result < minOut) ? minOut : (result > maxOut) ? maxOut : result;
    }

    void Container::FadeDensity(int size) {
        for (int i = 0; i < size; i++) {
            float d = this->density[i];
            density[i] = (d - 0.05f < 0) ? 0 : d - 0.05f;
        }
    }
} // Physic