#include <iostream>
#include "protocol.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


protocol::protocol() {
    baudrate = 115200;
    //strcpy_s(port, 4, "COM3");
}

void protocol::getCube(image* cube) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int z = 0; z < 8; z++) {
                copyCube[x][y][z] = cube->getCube(x, y, z);
            }
        }
    }
}

HANDLE protocol::open()
{
    DCB cdcb; //nomeia a estrutura DCB (Device Control Block) utilizada para definir todos os par�metros da comunica��o
    COMMTIMEOUTS comto; //nomeia a estrutura COMMTIMEOUTS (COMMon TIME OUTS) utilizada para definir os timeouts da comunica��o
    pCom = CreateFile(
        port, //nome do arquivo
        GENERIC_READ | GENERIC_WRITE, //abre arquivo para leitura ou escrita
        0, //indica que o arquivo n�o pode ser compartilhado
        NULL, //utiliza a estrutura default para as fun��es de seguran�a
        OPEN_EXISTING, //abre o arquivo, se n�o existir, retorna erro
        FILE_ATTRIBUTE_NORMAL, //o arquivo deve ser utilizado sozinho
        NULL); //sem gabarito de atributos

    if (pCom == INVALID_HANDLE_VALUE) { // testa falha na abertura do arquivo
        std::cerr << "Nao abriu a " << port;
        return pCom;
    }

    GetCommState(pCom, &cdcb); //le os par�metros de comunica��o atuais

    cdcb.BaudRate = baudrate; //define a taxa de transmiss�o
    cdcb.ByteSize = 8; //define o tamanho do dado - 8 bits
    cdcb.StopBits = ONESTOPBIT; //define o tamanho do stop bit - 1 stop bit
    cdcb.Parity = 2; //define o tipo de paridade - sem paridade

    if (!SetCommState(pCom, &cdcb)) { //seta os novos par�metros de comunica��o
        std::cerr << "SetCommState" << stderr;
        return INVALID_HANDLE_VALUE;
    }

    GetCommTimeouts(pCom, &comto);
    //Le os par�metros atuais de COMMTIMEOUTS
    comto.ReadIntervalTimeout = MAXDWORD;
    //tempo m�ximo entre a chegada de dois caracters consecutivos(ms)
    comto.ReadTotalTimeoutMultiplier = 0;
    comto.ReadTotalTimeoutConstant = 0;
    comto.WriteTotalTimeoutMultiplier = 0;
    comto.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(pCom, &comto);
    //seta os par�metros de COMMTIMEOUTS
    return pCom;
}

void protocol::send(char CID) {
    int n = 10000;
    out[0] = SNC;
    out[1] = CID|0x80;
    WriteFile(pCom, out, 2, &b, NULL);
    do {
        ReadFile(pCom, in, 1, &b, NULL);
        n--;
    } while (n > 0 && b == 0);

    if (in[0] != 'M') {
        std::cerr << "Nao autorizado! Comando recebido: " << in[0] << std::endl;
    } else {
        std::cout << in[0] << std::endl;
        WriteFile(pCom, copyCube, 512, &b, NULL);
        n = 10000;
        do {
            ReadFile(pCom, in, 1, &b, NULL);
            n--;
        } while (n > 0 && b == 0);
        std::cout << in[0] << std::endl;
    }
}

void protocol::activate(char CID) {
    out[0] = ATX;
    out[1] = CID|0x80;
    WriteFile(pCom, out, 2, &b, NULL);
}

