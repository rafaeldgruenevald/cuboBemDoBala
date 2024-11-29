#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

class image {
public:
    image();
    //virtual ~image();
    int getCube(int x, int y, int z);
    void animationOne(int intensity);
    void animationTwo();
    void animationThree();
    void staticOne();
private:
    uint8_t matrix[8][8][8];
    //int intensity;
    void led(int x, int y, int z);
    void line(int x, int y);
    void layer(int x);
    void full();
};
#endif // IMAGE_H
