#include "BtReciever.h"
#include <Arduino.h>

BtReciever::BtReciever(int rx, int tx)
{
    Serial1.setRX(rx);
    Serial1.setTX(tx);

    Serial1.begin(BAUD_RATE);
}

char BtReciever::GetData()
{
    if (Serial1.available() > 0)
    {
        byte data = Serial1.read();

        if (!_Connected)
        {
            _Connected = true;
            return FIRST_CONNECT;
        }
        else if (data == DISCONNECT)
        {
            _Connected = false;
            return DISCONNECT;
        }

        return (char)data;
    }

    return NO_DATA;
}