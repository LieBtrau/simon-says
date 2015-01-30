#include "debugsend.h"

DebugSend::DebugSend(byte pinNr):_pinNr(pinNr)
{
}

DebugSend::~DebugSend()
{

}

void DebugSend::sendBit(bool bHigh){
    digitalWrite(_pinNr, bHigh ? HIGH : LOW);
    delayMicroseconds(100);
}

void DebugSend::sendByte(byte data){
    //startBit
    sendBit(false);
    //Data
    for(byte i=0;i<8;i++){
        sendBit(data & 0x01 ? true : false);
        data>>=1;
    }
    //stopBit
    sendBit(true);
}
