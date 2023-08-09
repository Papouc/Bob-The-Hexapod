#include <Arduino.h>
#include "Body.h"

#define TIMER_PERIOD 8

Body *_Body = nullptr;

ulong prevMillis;
ulong currMillis;

void setup()
{
    _Body = new Body();
    _Body->ReachInitialPosition();

    delay(6000);

    // _Body->SetStancePosition();
    prevMillis = millis();
}

void loop()
{
    currMillis = millis();

    if (_Body->IsOnPosition()) 
    {
        _Body->SetNextStepPosition();
    }

    if (currMillis - prevMillis >= TIMER_PERIOD)
    {
        _Body->MoveToPosistion();
        prevMillis = currMillis;
    }
}
