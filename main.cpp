#include "image.h"
#include "protocol.h"
#include <iostream>
#include <stdio.h>

void animationOne(image *cube, protocol *prot) {
    for (int intensity = 0; intensity < 16; intensity++) {
        cube->animationOne(intensity);
        prot->getCube(cube);
        prot->send(intensity | (0x80 + intensity) );
    }
}

int main() {
    image vcube;
    protocol prot;

    //prot.getCube(&vcube);
    
    if (prot.open() == INVALID_HANDLE_VALUE) return -1;

    std::cout << "Conexao estabelecida!" << std::endl;

    //run animationOne
    std::cout << "retorno do send: ";
    animationOne(&vcube, &prot);
    //prot.send(0);
    std::cout << std::endl;
/*
    //run animationTwo
    vcube.animationTwo(&vcube, &prot);

    std::cout << "retorno do activate: " << std::endl;
    for (int i = 0; i < 16; i++) {
        prot.activate(i | (0x80 + i));
        Sleep(1000);
        std::cout << "ativou imagem " << i << std::endl;
    }
*/
    std::cout << "retorno do clear: ";
    prot.clear();
    std::cout << std::endl;
}
