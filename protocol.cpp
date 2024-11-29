#include <iostream>
#include "cube.h"
#include "protocol.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


protocol::protocol(int baud, char *p) {
    baudrate = baud;
    strcpy(port, p);
}

HANDLE protocol::openSerial() {
    DCB cdcb;
    COMMTIMEOUTS comto;
    pCom = CreateFile(
        port, //nome do arquivo
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (pCom == INVALID_HANDLE_VALUE) {
        std::cerr << "Nao abriu a " << port;
        return pCom;
    }

    GetCommState(pCom, &cdcb);

    cdcb.BaudRate = baudrate;
    cdcb.ByteSize = 8;
    cdcb.StopBits = ONESTOPBIT;
    cdcb.Parity = 2;

    if (!SetCommState(pCom, &cdcb)) {
        std::cerr << "SetCommState" << stderr;
        return INVALID_HANDLE_VALUE;
    }

    GetCommTimeouts(pCom, &comto);
    comto.ReadIntervalTimeout = MAXDWORD;
    comto.ReadTotalTimeoutMultiplier = 0;
    comto.ReadTotalTimeoutConstant = 0;
    comto.WriteTotalTimeoutMultiplier = 0;
    comto.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(pCom, &comto);
    return pCom;
}

void protocol::send(char CID, uint8_t c[][8][8]) {
    int n = 10000;
    out[0] = SNC;
    out[1] = CID;
    WriteFile(pCom, out, 2, &b, NULL);
    do {
        ReadFile(pCom, in, 1, &b, NULL);
        n--;
    } while (n > 0 && b == 0);

    if (in[0] != 'M') {
        std::cerr << "Nao autorizado! Comando recebido: " << in[0] << std::endl;
    } else {
        std::cout << in[0] << " ";
        WriteFile(pCom, c, 512, &b, NULL);
        n = 10000;
        do {
            ReadFile(pCom, in, 1, &b, NULL);
            n--;
        } while (n > 0 && b == 0);
        std::cout << in[0] << " / ";
    }
}

void protocol::activate(char CID) {
    out[0] = ATX;
    out[1] = CID;
    WriteFile(pCom, out, 2, &b, NULL);
}

void protocol::clear() {
    out[0] = CLR;
    out[1] = CLR;
    WriteFile(pCom, out, 2, &b, NULL);
}
