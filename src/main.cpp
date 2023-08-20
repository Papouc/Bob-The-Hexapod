#include <Arduino.h>
#include "Body.h"
#include "BtReciever.h"
#include "PinLayout.h"

#define TIMER_PERIOD 5

Body *_Body = nullptr;
BtReciever *_Reciever = nullptr;

ulong prevMillis;
ulong currMillis;

void setup()
{
    _Body = new Body();
    _Body->ReachInitialPosition();

    _Reciever = new BtReciever(SERIAL_RX_PIN, SERIAL_TX_PIN);

    delay(1000);

    prevMillis = millis();
}

void loop()
{
    currMillis = millis();

    char data = _Reciever->GetData();

    if (_Body->IsOnPosition())
    {
        // ready for next move
        switch (data)
        {
        case 'F':
            _Body->SetNextStepPosition(Direction::FORWARD);
            break;
        case 'B':
            _Body->SetNextStepPosition(Direction::BACKWARD);
            break;
        case 'L':
            _Body->SetNextTurnPosition(Rotation::LEFT);
            break;
        case 'R':
            _Body->SetNextTurnPosition(Rotation::RIGHT);
            break;
        case FIRST_CONNECT:
            _Body->SetStancePosition();
            break;
        case DISCONNECT:
            _Body->ReachInitialPosition();
            break;
        }
    }

    if (currMillis - prevMillis >= TIMER_PERIOD)
    {
        _Body->MoveToPosistion();
        prevMillis = currMillis;
    }
}
