#include <iostream>
#include "cube.h"
#include "protocol.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


protocol::protocol(int baud, char p[6], int tries) {
    baudrate = baud;
    nTries = tries;
    strcpy(port, p);
}

HANDLE protocol::openSerial() {
    DCB cdcb;
    COMMTIMEOUTS comto;
    comPort = CreateFile(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (comPort == INVALID_HANDLE_VALUE) {
        std::cerr << "Porta " << port << " nao ta querendo";
        return comPort;
    }

    GetCommState(comPort, &cdcb);

    cdcb.BaudRate = baudrate;
    cdcb.ByteSize = 8;
    cdcb.StopBits = ONESTOPBIT;
    cdcb.Parity = 2;

    if (!SetCommState(comPort, &cdcb)) {
        std::cerr << "SetCommState" << stderr;
        return INVALID_HANDLE_VALUE;
    }

    GetCommTimeouts(comPort, &comto);
    comto.ReadIntervalTimeout = MAXDWORD;
    comto.ReadTotalTimeoutMultiplier = 0;
    comto.ReadTotalTimeoutConstant = 0;
    comto.WriteTotalTimeoutMultiplier = 0;
    comto.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(comPort, &comto);
    return comPort;
}

void protocol::sendImg(char nImg, uint8_t mtrxImg[][8][8]) {
    int n = nTries;
    out[0] = SNC;
    out[1] = nImg;
    WriteFile(comPort, out, 2, &bytesWritten, NULL);
    do {
        ReadFile(comPort, in, 1, &bytesWritten, NULL);
        n--;
    } while (n > 0 && bytesWritten == 0);

    if (in[0] != 'M') {
        std::cerr << "Nao autorizado! Comando recebido: " << in[0] << std::endl;
    } else {
        WriteFile(comPort, mtrxImg, 512, &bytesWritten, NULL);
        n = 10000;
        do {
            ReadFile(comPort, in, 1, &bytesWritten, NULL);
            n--;
        } while (n > 0 && bytesWritten == 0);
    }
}

void protocol::activateImg(char nImg) {
    out[0] = ATX;
    out[1] = nImg;
    WriteFile(comPort, out, 2, &bytesWritten, NULL);
}

void protocol::clear() {
    out[0] = CLR;
    out[1] = CLR;
    WriteFile(comPort, out, 2, &bytesWritten, NULL);
}
