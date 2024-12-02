#include "cube.h"
#include "protocol.h"
#include <iostream>
#include <stdio.h>

void animation(cube *cube, protocol *proto) {
    int intensity = 15;
    for (int i = 0; i < 9; i++) {
        cube->fade(intensity, i, 8);
        proto->sendImg(i | 0x80, cube->matrix);
        intensity = 15 - i;
    }
    for (int j = 0; j < 10; j++) {
        proto->activateImg(j | 0x80);
        Sleep(200);
        if (j == 9) {
            Sleep (2000);
            j = 0;
        }
    }
}

int main() {
    cube cubo;
    protocol proto(115200, "COM6", 10000);
    if (proto.openSerial() == INVALID_HANDLE_VALUE) return -1;
    animation(&cubo, &proto);
    proto.clear();
}
