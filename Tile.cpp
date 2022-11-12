//
// Created by eric on 30.10.22.
//

#include "Tile.h"
#include "Constants.h"
#include "Color.h"
#include <GL/glut.h>
#include <iterator>

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
    this->index = coord(x, y);

    this->initneighbours();
}

Tile::Tile(int i) {
    this->index = i;
    this->x = xCoord(this->index);
    this->y = yCoord(this->index);

    this->initneighbours();
}

void Tile::initneighbours() {
    /*this->neighbours[0] = coord(this->x - 1, this->y - 1);
    this->neighbours[1] = coord(this->x - 0, this->y - 1);
    this->neighbours[2] = coord(this->x + 1, this->y - 1);

    this->neighbours[3] = coord(this->x - 1, this->y - 0);
    //this->neighbours[3]=coord(this->x-0,this->y-0);
    this->neighbours[4] = coord(this->x + 1, this->y - 0);

    this->neighbours[5] = coord(this->x - 1, this->y + 1);
    this->neighbours[6] = coord(this->x - 0, this->y + 1);
    this->neighbours[7] = coord(this->x + 1, this->y + 1);
*/
    this->neighbours[0] = coord(this->x - 0, this->y - 1);
    this->neighbours[1] = coord(this->x - 0, this->y + 1);
    this->neighbours[2] = coord(this->x - 1, this->y - 0);
    this->neighbours[3] = coord(this->x + 1, this->y - 0);


    this->neighbours[4] = coord(this->x - 1, this->y - 1);
    this->neighbours[5] = coord(this->x + 1, this->y - 1);
    this->neighbours[6] = coord(this->x - 1, this->y + 1);
    this->neighbours[7] = coord(this->x + 1, this->y + 1);
}

void Tile::draw() const {
    glBegin(GL_POINTS);

    Color::Black().setGL();
    glVertex2i(this->x * POINT_SIZE + POINT_OFFSET, this->y * POINT_SIZE + POINT_OFFSET);

    if (this->staticTile) {
        Color::Grey().setGL();
        glVertex2i(this->x * POINT_SIZE + POINT_OFFSET, this->y * POINT_SIZE + POINT_OFFSET);
    } else {
        Color::Stone().setGL(std::min(this->stone, 255.0f));
        glVertex2i(this->x * POINT_SIZE + POINT_OFFSET, this->y * POINT_SIZE + POINT_OFFSET);


        float alpha;
        if (this->water > 50) {
            alpha = 255;
        } else {
            alpha = this->water * 5;
        }

        Color::Blue().setGL(std::min(alpha, 255.0f));
        glVertex2i(this->x * POINT_SIZE + POINT_OFFSET, this->y * POINT_SIZE + POINT_OFFSET);
    }

    glEnd();
}

void shuffle(int arr[]) {
    int first = arr[0];
    for (int i = 0; i < 7; ++i) {
        arr[i] = arr[i + 1];
    }
    arr[7] = first;
}

void Tile::equalize(Tile **tiles) {
    if (this->staticTile)return;

    if (this->water <= 0) {
        this->water = 0;
        shuffle(this->neighbours);
        return;
    }

    for (int neighbour: this->neighbours) {
        Tile *other = tiles[neighbour];
        if (other->staticTile)continue;

        float height = this->stone + this->water;

        float heightDiff = height - (other->stone);
        if (heightDiff < 0)continue;

        float waterDiff = height - (other->stone + other->water);
        if (waterDiff < 0)continue;

        int waterTableDiff = this->water - other->water;
        float halfdiff = std::min((float) waterDiff * Tile::WaterViscosity, (float) this->water * Tile::WaterViscosity);

        this->water -= halfdiff;
        other->water += halfdiff;

        if (this->stone > 0 && (this->stone > other->stone)) {
            this->stone -= Tile::StoneHardness;
            other->stone += Tile::StoneHardness;
        }
    }
    shuffle(this->neighbours);
}

void Tile::setStatic() {
    this->staticTile = true;
    this->stone = 255 * 4;
    this->water = 0;
}
