#ifndef WATER_CONSTANTS_H
#define WATER_CONSTANTS_H

#define ScreenWidth 512
#define ScreenHeight 512

#define Power 7
#define GridWidth (1<<Power)
#define GridHeight GridWidth // Square Size
#define GridSize GridWidth*GridHeight


#define POINT_SIZE (ScreenWidth/GridWidth)
#define POINT_OFFSET (POINT_SIZE/2)

#define coord(x,y) ((x)+GridWidth*(y))
#define xCoord(i) ((i)%GridWidth)
#define yCoord(i) ((i)/GridWidth)

#endif //WATER_CONSTANTS_H
