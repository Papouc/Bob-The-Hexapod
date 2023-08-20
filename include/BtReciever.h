#pragma once

#define BAUD_RATE 9600
#define NO_DATA 'N'
#define FIRST_CONNECT 'C'
#define DISCONNECT 'D'

class BtReciever
{
private:
    bool _Connected{false};

public:
    BtReciever(int rx, int tx);
    char GetData();
};
