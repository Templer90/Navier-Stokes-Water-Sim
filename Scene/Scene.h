//
// Created by eric on 07.11.22.
//

#ifndef WATER_SCENE_H
#define WATER_SCENE_H

#include <utility>

#include "../helper/ButtonKeys.h"
#include "../helper/TileAction.h"
#include "../Color.h"
#include "../Constants.h"
#include "../helper/PrintString.h"

namespace Scene {
    class Scene {
    protected:
        int mouseX{}, mouseY{};

        float infoTimer = 0;
        std::string infoText;
    public:
        const char *Name = "Virtual";

        virtual void HandleInputs(helper::ButtonKeys Keys) = 0;

        virtual void Display(int frameCounter) = 0;

        virtual void ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) = 0;

        virtual void ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) = 0;

        virtual void mouseMove(helper::ButtonKeys Keys, int x, int y) = 0;

        virtual void mouseDown(helper::ButtonKeys Keys, int button, int x, int y) = 0;

        virtual void mouseUp(helper::ButtonKeys Keys, int button, int x, int y) = 0;

        virtual void mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) = 0;

        void displayInfoText(float delta) {
            if (infoTimer <= 0) {
                return;
            } else {
                infoTimer -= delta;
                Color::White().setGL();
                glRasterPos2f(10, ScreenHeight - 10);
                for (auto c: infoText) {
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
                }
            }
        }

        void displayInfoText(std::string s, float start) {
            infoTimer = start;
            infoText = std::move(s);
        }
    };

} // Scene

#endif //WATER_SCENE_H
