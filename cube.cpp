#include <unistd.h>
#include "cube.h"

cube::cube() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                matrix[x][y][z] = 15;
            }
        }
    }
}

uint8_t getMatrix() {
    return matrix;
}

void cube::animationOne(int intensity) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                matrix[x][y][z] = intensity;
            }
        }
    }
}

void cube::animationTwo(int pos, int size){
    for (int x = 0; x < pos; x++) {
        for (int y = 0; y < pos; y++) {
            for (int z = 0; z < pos; z++) {
                if(x<=size && y<=size && z<=size){
                    matrix[x][y][z] = 15;
                }
            }
        }
    }
}
