#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

class cube {
public:
    cube();
    uint8_t getMatrix();
private:
    uint8_t matrix[8][8][8];
};
#endif
