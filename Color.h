//
// Created by eric on 30.10.22.
//

#ifndef WATER_COLOR_H
#define WATER_COLOR_H


class Color {
    unsigned char r{},g{},b{};
    unsigned char a=255;

public:
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);

    void setGL();
    void setGL(unsigned char alpha);
    void setGL(float alpha);

    static Color &Black() {static Color color(0, 0, 0,255);return color;};
    static Color &Red() {static Color color(255, 0, 0,255);return color;};
    static Color &Green() {static Color color(0, 255, 0,255);return color;};
    static Color &Blue() {static Color color(0, 0, 255,255);return color;};
    static Color &White() {static Color color(255, 255,255,255);return color;};
    static Color &Grey() {static Color color(128, 128,128,255);return color;};

    static Color &Stone() {static Color color(227, 187, 123);return color;};
    static Color &Water() {static Color color(131, 213, 242);return color;};

    static void Direct(int r, int g, int b, unsigned char alpha);

    static void Direct(int r, int g, int b);
};


#endif //WATER_COLOR_H
