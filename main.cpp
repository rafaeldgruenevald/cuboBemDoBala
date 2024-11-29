#include "cube.h"
#include "protocol.h"
#include <iostream>
#include <stdio.h>

void animationTwo(cube *cube, protocol *prot) {
    bool active = true;
    int size = 0;
    for (int i = 0; i < 9; i++) {
        cube->animationTwo(i, size);
        prot->send(i | 0x80, cube->getMatrix());
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
    cube vcube;
    protocol prot(115200,"COM8");

    if (prot.open() == INVALID_HANDLE_VALUE) return -1;

    std::cout << "Conexao estabelecida!" << std::endl;
    animationTwo(&vcube, &prot);

    std::cout << "retorno do clear: ";
    prot.clear();
    std::cout << std::endl;
}
