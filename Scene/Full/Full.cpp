//
// Created by eric on 08.11.22.
//

#include <cstdlib>
#include "Full.h"
#include <GL/glut.h>
#include "IX.h"

namespace Scene {
    Full::Full() {
        container = Physic::Container(0.2f, 0, 0.0000001f);
        Name = "Navier-Stokes";
    }

    void Full::HandleInputs(helper::ButtonKeys Keys) {
        if (Keys.esc == 1) { exit(0); }

        if (Keys.mouseL) {
            this->container.AddDensity(Keys.mouseX / POINT_SIZE, Keys.mouseY / POINT_SIZE, 200);

        }
        if (Keys.mouseR) {

        }
    }

   void Hsv(int hue,  float sat,  float val, const float d) {
       hue %= 360;
       while (hue < 0) hue += 360;

       if (sat < 0.f) sat = 0.f;
       if (sat > 1.f) sat = 1.f;

       if (val < 0.f) val = 0.f;
       if (val > 1.f) val = 1.f;

       int h = hue / 60;
       float f = float(hue) / 60 - h;
       float p = val * (1.f - sat);
       float q = val * (1.f - sat * f);
       float t = val * (1.f - sat * (1 - f));

        switch(h) {
            default:
            case 0:
            case 6:  Color::Direct(val*255, t*255, p*255, d);break;
            case 1:  Color::Direct(q*255, val*255, p*255, d);break;
            case 2:  Color::Direct(p*255, val*255, t*255, d);break;
            case 3:  Color::Direct(p*255, q*255, val*255, d);break;
            case 4:  Color::Direct(t*255, p*255, val*255, d);break;
            case 5:  Color::Direct(val*255, p*255, q*255, d);break;
        }
    }

    void Full::Display(int FrameCounter) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize((int) POINT_SIZE);

        this->container.Step();

        switch (editState) {
            case Normal:
                for (int i = 0; i < Physic::Container::size; i++) {
                    for (int j = 0; j < Physic::Container::size; j++) {
                        Color::Red().setGL(
                                std::min(container.density[Physic::IX(i, j, Physic::Container::size)], 255.0f));

                        glBegin(GL_POINTS);
                        glVertex2i(i * POINT_SIZE + POINT_OFFSET, j * POINT_SIZE + POINT_OFFSET);
                        glEnd();
                    }
                }
                break;
            case Velocity:
                for (int i = 0; i < Physic::Container::size; i++) {
                    for (int j = 0; j < Physic::Container::size; j++) {
                        int r = (int) Physic::Container::MapToRange(
                                container.x[Physic::IX(i, j, Physic::Container::size)], -0.05f, 0.05f, 0, 255);
                        int g = (int) Physic::Container::MapToRange(
                                container.y[Physic::IX(i, j, Physic::Container::size)], -0.05f, 0.05f, 0, 255);
                        int b = 255;

                        glBegin(GL_POINTS);
                        Color::Direct(r, g, b);
                        glVertex2i(i * POINT_SIZE + POINT_OFFSET, j * POINT_SIZE + POINT_OFFSET);
                        glEnd();
                    }
                }
                break;
            case HSL:
                for (int i = 0; i < Physic::Container::size; i++) {
                    for (int j = 0; j < Physic::Container::size; j++) {
                        glBegin(GL_POINTS);
                        Hsv(((int)container.density[Physic::IX(i,j,Physic::Container::size)]), 1, 1, 255);
                        glVertex2i(i * POINT_SIZE + POINT_OFFSET, j * POINT_SIZE + POINT_OFFSET);
                        glEnd();
                    }
                }
                break;
        };

        this->container.FadeDensity(GridSize);

        glBegin(GL_POINTS);
        Color::White().setGL();
        glVertex2i(mouseX * POINT_SIZE + POINT_OFFSET, mouseY * POINT_SIZE + POINT_OFFSET);
        glVertex2i(oldMouseX * POINT_SIZE + POINT_OFFSET, oldMouseY * POINT_SIZE + POINT_OFFSET);
        glEnd();
    }

    void Full::ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        if (key == 27) { Keys.esc = 1; }
        glutPostRedisplay();
    }

    void Full::ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        if (key == 27) { Keys.esc = 0; }

        if (key == 98) {
            switch (editState) {
                case Normal:
                    editState = States::Velocity;
                    break;
                case Velocity:
                    editState = States::HSL;
                    break;
                case HSL:
                    editState = States::Normal;
                    break;
            }
        }

        glutPostRedisplay();
    }

    void Full::mouseDown(helper::ButtonKeys Keys, int button, int x, int y) {
        if (button == helper::MouseButtons::R) {
            oldMouseX = x;
            oldMouseY = y;
        }
    }

    void Full::mouseUp(helper::ButtonKeys Keys, int button, int x, int y) {
        if (button == helper::MouseButtons::R) {
            float amountX = (Keys.mouseX - oldMouseX) / 1;
            float amountY = (Keys.mouseY - oldMouseY) / 1;

            this->displayInfoText(std::to_string(amountY), 4);
            this->container.AddVelocity(oldMouseX / POINT_SIZE, oldMouseY / POINT_SIZE, amountX, amountY);

        }

    }

    void Full::mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) {}

    void Full::mouseMove(helper::ButtonKeys Keys, int x, int y) {
        mouseX = Keys.mouseX / POINT_SIZE;
        mouseY = Keys.mouseY / POINT_SIZE;
    }

}


