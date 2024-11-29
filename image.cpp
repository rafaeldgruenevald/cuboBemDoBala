#include <unistd.h>
#include "image.h"

image::image() {
    //intensity = 15;
    //placeholder to test the protocol
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                matrix[x][y][z] = 15;
            }
        }
    }
}

int image::getCube(int x, int y, int z) {
    return matrix[x][y][z];
}

void image::animationOne(int intensity) {
    //for (intensity = 0; intensity < 16; intensity++) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int z = 0; z < 8; z++) {
                    matrix[x][y][z] = intensity;
                }
            }
        }
        //usleep(1000);
    //}
}

void image::animationTwo(){
    //reset cube
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                matrix[x][y][z] = 0;
            }
        }
    }

    int size = 0;
    while(matrix[7][7][7]<15){  //while the last LED is not fully bright
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int z = 0; z < 8; z++) {
                    if(x<=size && y<=size && z<=size && matrix[x][y][z]<15){     //increse brightness of LEDs that fit in "size"
                        matrix[x][y][z]++;
                    }
                }
            }
        }
        usleep(1000);
        size++;
    }
}
