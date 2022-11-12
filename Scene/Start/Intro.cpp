//
// Created by eric on 09.11.22.
//

#include "Intro.h"
#include <GL/glut.h>

namespace Scene {
    Intro::Intro(){
         Name = "Intro";
    }

    void Intro::HandleInputs(helper::ButtonKeys Keys) {
        if (Keys.esc == 1) { exit(0); }
    }

    void Intro::Display(int frameCounter) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Intro::ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        if (Keys.esc == 1) { exit(0); }
    }

    void Intro::ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        if (Keys.esc == 1) { exit(0); }
    }

    void Intro::mouseMove(helper::ButtonKeys Keys, int x, int y) {

    }

    void Intro::mouseDown(helper::ButtonKeys Keys, int button, int x, int y) {

    }

    void Intro::mouseUp(helper::ButtonKeys Keys, int button, int x, int y) {

    }

    void Intro::mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) {

    }
} // Scene