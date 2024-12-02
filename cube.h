#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

class cube {
public:
    cube();
    void fade(int inten,int h, int b);
    uint8_t matrix[8][8][8];
};
#endif
