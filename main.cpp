#include <iostream>
#include <GL/glut.h>
#include <string>
#include "Constants.h"
#include "Tile.h"
#include "helper/TileAction.h"
#include "helper/ButtonKeys.h"
#include "Scene/SceneList.h"
#include "Scene/SimpleCell/SimpleCell.h"
#include "Scene/Full/Full.h"
#include "Color.h"
#include "Scene/Start/Intro.h"
#include "helper/PrintString.h"

using namespace std;

int frame1, frame2;
int fps = 0;
int frameCounter = 0;

Scene::SceneList Scenes = Scene::SceneList({new Scene::Full(),new Scene::Intro(), new Scene::SimpleCell()});
helper::ButtonKeys Keys;

void init() {

}

void drawText(float x, float y, const std::string &text) {
    glRasterPos2f(x, y);
    for (auto c: text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
    }
}

void handleInputs() {
    Scenes.current()->HandleInputs(Keys);
}

void display() {
    frame2 = glutGet(GLUT_ELAPSED_TIME);
    fps = (frame2 - frame1);
    frame1 = glutGet(GLUT_ELAPSED_TIME);

    frameCounter++;
    handleInputs();

    Scenes.current()->Display(frameCounter);

    Scenes.current()->displayInfoText((float) fps / 1000.0f);

    Color::White().setGL();
    drawText(10, ScreenHeight - 20,
             helper::string_format("%s fps: %3.0f", Scenes.current()->Name, (1000.0f / (float) fps)));
    glutPostRedisplay();
    glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y) {
    //std::cout << (int) key << "\n";
    if (key == 27) { Keys.esc = 1; }
    Scenes.current()->ButtonDown(Keys, key, x, y);
    glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y) {
    if (key == 27) { Keys.esc = 0; }
    if (key == 110) {
        Scenes++;
        return;
    }
    if (key == 109) {
        Scenes--;
        return;
    }
    Scenes.current()->ButtonUp(Keys, key, x, y);
    glutPostRedisplay();
}

void MouseMove(int x, int y) {
    Scenes.current()->mouseMove(Keys, x, y);
    Keys.mouseX = x;
    Keys.mouseY = y;
}

void MouseClick(int button, int state, int x, int y) {
    if (state == 0) {
        if (button == helper::MouseButtons::L) { Keys.mouseL = 1; }
        if (button == helper::MouseButtons::M) { Keys.mouseM = 1; }
        if (button == helper::MouseButtons::R) { Keys.mouseR = 1; }
        Scenes.current()->mouseDown(Keys, button, x, y);
    }
    if (state == 1) {
        if (button == helper::MouseButtons::L) { Keys.mouseL = 0; }
        if (button == helper::MouseButtons::M) { Keys.mouseM = 0; }
        if (button == helper::MouseButtons::R) { Keys.mouseR = 0; }
        Scenes.current()->mouseUp(Keys, button, x, y);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - ScreenWidth / 2,
                           glutGet(GLUT_SCREEN_HEIGHT) / 2 - ScreenHeight / 2);

    glutCreateWindow("Waterdemo");
    gluOrtho2D(0, ScreenWidth, ScreenHeight, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);

    glutMouseFunc(MouseClick);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MouseMove);

    glutMainLoop();
}