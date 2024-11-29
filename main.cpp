#include "image.h"
#include "protocol.h"
#include <iostream>
#include <stdio.h>

int main() {
    image vcube;
    protocol prot;

    prot.getCube(&vcube);
    if (prot.open() == INVALID_HANDLE_VALUE) return -1;

    std::cout << "passou do open" << std::endl;
    prot.send(0);
    std::cout << "retorno do send" << std::endl;
   /* prot.activate(0);
    std::cout << "retorno do activate" << std::endl;*/
}
