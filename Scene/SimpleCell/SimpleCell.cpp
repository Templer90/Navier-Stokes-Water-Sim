//
// Created by eric on 08.11.22.
//

#include <cstdlib>
#include "SimpleCell.h"
#include <GL/glut.h>
#include <iostream>

namespace Scene {
    SimpleCell::SimpleCell() {
        Name = "Simple";

        grid = new Tile *[GridSize];

        for (int i = 0; i < GridSize; ++i) {
            grid[i] = new Tile(i);
            grid[i]->stone = (i / 128) + (int) rand() % 128;
            grid[i]->water = 0;
        }

        for (int x = 0; x < GridWidth; ++x) {
            grid[coord(x, 0)]->setStatic();
            grid[coord(x, GridHeight - 1)]->setStatic();
        }

        for (int y = 0; y < GridHeight; ++y) {
            grid[coord(0, y)]->setStatic();
            grid[coord(GridHeight, y) - 1]->setStatic();
        }

        actions = new helper::TileAction[]{
                {[](Tile *tile, float amount) { tile->water += amount; },                              "More Water"},
                {[](Tile *tile, float amount) { tile->stone += amount; },                              "More Stone"},
                {[](Tile *tile, float amount) { tile->water = std::max(tile->water - amount, 0.0f); }, "Less Water"},
                {[](Tile *tile, float amount) { tile->stone = std::max(tile->stone - amount, 0.0f); }, "Less Stone"},
        };
    }

    void SimpleCell::HandleInputs(helper::ButtonKeys Keys) {
        if (Keys.mouseL) {
            actions[editState % 4].action(grid[coord(mouseX, mouseY)], 100);
        }
    }

    void SimpleCell::Display(int FrameCounter) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize((int) POINT_SIZE);

        int iterationsPerFrame = 1;
        for (int count = 0; count < iterationsPerFrame; count++) {
            for (int i = 0; i < GridSize; ++i) {
                grid[i]->equalize(grid);
            }
        }

        for (int i = 0; i < GridSize; ++i) {
            grid[i]->draw();
        }

        //grid[65]->stone = 0;
        // grid[65]->water = 0;

        glBegin(GL_POINTS);
        Color::White().setGL();
        glVertex2i(mouseX * POINT_SIZE + POINT_OFFSET, mouseY * POINT_SIZE + POINT_OFFSET);
        glEnd();
    }

    void SimpleCell::ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        std::cout << (int) key << "\n";
        if (key == 27) { Keys.esc = 1; }

        glutPostRedisplay();
    }

    void SimpleCell::ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) {
        if (key == 27) { Keys.esc = 0; }
        glutPostRedisplay();
    }

    void SimpleCell::mouseDown(helper::ButtonKeys Keys, int button, int x, int y) {

    }

    void SimpleCell::mouseUp(helper::ButtonKeys Keys, int button, int x, int y) {
        if (button == helper::MouseButtons::R) {
            editState++;

            this->displayInfoText(actions[editState % 4].notice, 4);
        }
    }

    void SimpleCell::mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) {}

    void SimpleCell::mouseMove(helper::ButtonKeys Keys, int x, int y) {
        mouseX = Keys.mouseX / POINT_SIZE;
        mouseY = Keys.mouseY / POINT_SIZE;
    }
}


