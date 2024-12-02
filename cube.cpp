#include <unistd.h>
#include "cube.h"

cube::cube() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                matrix[x][y][z] = 0;
            }
        }
    }
}

void cube::fade(int inten,int h, int b) {
    for (int x = 0; x < b; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < h; z++) {
                matrix[x][y][z] = inten;
            }
        }
    }
}
