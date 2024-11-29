#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "image.h"
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
    protocol();                //constructor
    //virtual ~protocol();     //destructor
    void getCube(image* cube); //get virtual image thru a pointer
    HANDLE open();        //create connection between intefaces
    void send(char CID);       //send virtual image
    void activate(char CID);           //activate image sent in the cube

    //depois fazer uma funcao pra puxar esses valores (se necessario)
    //e devolver essas buxas pro privado
    char in[2];  //command received
    char out[6]; //command sent
private:
    uint8_t copyCube[8][8][8]; //DEPOIS ARRUMAR ESSA GAMBIARRA
    HANDLE pCom;           //handler object
    unsigned long int b;   //bytes received
    int baudrate;          //proprietary baudrate
    char port[6] = "COM3"; //port identification
    image* cube;           //pointer to virtual cube
};
#endif // PROTOCOL_H
