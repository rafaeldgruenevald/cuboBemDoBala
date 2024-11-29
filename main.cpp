#include "image.h"
#include "protocol.h"
#include <iostream>
#include <stdio.h>

void animationOne(image *cube, protocol *prot) {
    bool active = true, up = true;
    int i = 0;

    cube->full(0);
    for (int intensity = 0; intensity < 16; intensity++) {
        cube->animationOne(intensity);
        prot->getCube(cube);
        prot->send(intensity | 0x80);
    }

    while (active) {
        prot->activate(i | 0x80);
        Sleep(300);
        std::cout << "ativou imagem " << i << std::endl;
        if (i == 15) up = false;
        if (i == 0) up = true;
        if (up) i++;
        else i--;
    }
}

void animationTwo(image *cube, protocol *prot) {
    bool active = true;
    int size = 0;

    cube->full(0);
    for (int i = 0; i < 9; i++) {
        cube->animationTwo(i, size);
        prot->getCube(cube);
        prot->send(i | 0x80);
        size++;
    }
    for (int j = 0; j < 9; j++) {
        prot->activate(j | 0x80);
        Sleep(300);
        std::cout << "ativou imagem " << j << std::endl;
        if (j == 8) {
            Sleep (1000);
            j = 0;
        }
    }
}

int main() {
    image vcube;
    protocol prot;

    if (prot.open() == INVALID_HANDLE_VALUE) return -1;

    std::cout << "Conexao estabelecida!" << std::endl;

    //animationOne(&vcube, &prot);
    animationTwo(&vcube, &prot);

    std::cout << "retorno do clear: ";
    prot.clear();
    std::cout << std::endl;
}
