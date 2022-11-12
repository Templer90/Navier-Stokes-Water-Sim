//
// Created by eric on 09.11.22.
//

#ifndef WATER_INTRO_H
#define WATER_INTRO_H

#include "../Scene.h"

namespace Scene {

    class Intro : public Scene {
    public:
        Intro();

        void HandleInputs(helper::ButtonKeys Keys) override;

        void Display(int frameCounter) override;

        void ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void mouseMove(helper::ButtonKeys Keys, int x, int y) override;

        void mouseDown(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseUp(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) override;

    };

} // Scene

#endif //WATER_INTRO_H
