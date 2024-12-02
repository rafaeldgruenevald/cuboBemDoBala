#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "cube.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define SNC  ('S'|0x80)
#define ATX  ('X'|0x80)
#define CLR  ('C'|0x80)
#define ACK  'A'
#define NAK  'N'
#define MND  'M'
#define NID  'I'
#define TOUT 'T'

class protocol {
public:
    protocol(int baud, char p[6], int tries);
    HANDLE openSerial();
    void sendImg(char nImg, uint8_t mtrxImg[][8][8]);
    void activateImg(char nImg);
    void clear();
private:
    HANDLE comPort;
    unsigned long int bytesWritten;
    int baudrate;
    int nTries;
    char in[2];
    char out[6];
    char port[6];
};
#endif // PROTOCOL_H
