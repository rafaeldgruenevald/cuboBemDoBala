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
    protocol(int baud, char *p);
    HANDLE openSerial();
    void send(char CID, uint8_t c[][8][8]);
    void activate(char CID);
    void clear();
    char in[2];
    char out[6];
private:
    HANDLE pCom;
    unsigned long int b;
    int baudrate;
    char port[6];
};
#endif // PROTOCOL_H
