//
// Created by eric on 30.10.22.
//

#ifndef WATER_TILE_H
#define WATER_TILE_H


class Tile {
    int index;
    bool staticTile = false;
    int neighbours[8]{};

    void initneighbours();
public:
    constexpr static const float WaterViscosity=0.2f;
    constexpr static const float StoneHardness=0.01f;

    Tile(int x, int y);
    explicit Tile(int i);

    int x, y;
    float stone{}, water{};

    void setStatic();

    void draw() const;

    void equalize(Tile **tiles);
};



#endif //WATER_TILE_H
