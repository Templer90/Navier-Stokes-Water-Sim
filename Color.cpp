//
// Created by eric on 30.10.22.
//

#include "Color.h"
#include <GL/glut.h>

void Color::setGL() {
    this->setGL(this->a);
}

void Color::setGL(unsigned char alpha) {
    Color::Direct(this->r, this->g, this->b, alpha);
}

void Color::Direct(int r, int g, int b,unsigned char alpha) {
    glColor4ub(r, g, b, alpha);
}

void Color::Direct(int r, int g, int b) {
    Color::Direct(r, g, b, 255);
}


void Color::setGL(float alpha) {
    this->setGL((unsigned char)alpha);
}

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 255;
}

Color::Color(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

