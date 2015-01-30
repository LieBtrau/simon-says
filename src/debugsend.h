#ifndef DEBUGSEND_H
#define DEBUGSEND_H
#include "Arduino.h"

//Send debug data at 1200baud
class DebugSend
{
public:
    DebugSend(byte pinNr);
    ~DebugSend();
    void sendByte(byte data);
private:
    void sendBit(bool bHigh);
    byte _pinNr;
};

#endif // DEBUGSEND_H
