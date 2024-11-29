#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

class image {
public:
    image();
    //virtual ~image();
    int getCube(int x, int y, int z);
    void animationOne(int intensity);
    void animationTwo(int pos, int size);
    void animationThree();
    void staticOne();
    void full(int intensity);
private:
    uint8_t matrix[8][8][8];
    void led(int x, int y, int z);
    void line(int x, int y);
    void layer(int x);
};
#endif
