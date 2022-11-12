//
// Created by eric on 08.11.22.
//


#ifndef WATER_FULL_H
#define WATER_FULL_H

#include "../Scene.h"
#include "../../helper/ButtonKeys.h"
#include "../../Tile.h"
#include "../../helper/TileAction.h"
#include "PhysicsSolver/Container.h"

namespace Scene {
    class Full : public Scene {
        enum States {
            Normal = 0, Velocity, HSL, Previous
        };

        struct EditState {
            std::string name;
            States next;
        };


    private:
        Physic::Container container;

        int oldMouseX{}, oldMouseY{};
        States currentState = Full::Normal;
        EditState *StatesList = new EditState[]{
                {"Normal",   States::Velocity},
                {"Velocety", States::HSL},
                {"HSL",      States::Previous},
                {"Previous", States::Normal}
        };

    public:
        Full();

        void HandleInputs(helper::ButtonKeys Keys) override;

        void Display(int FrameCounter) override;

        void ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void mouseMove(helper::ButtonKeys Keys, int x, int y) override;

        void mouseDown(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseUp(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) override;
    };
}


#endif //WATER_FULL_H
