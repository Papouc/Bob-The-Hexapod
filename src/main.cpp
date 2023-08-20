#include <Arduino.h>
#include "Body.h"

#define TIMER_PERIOD 5

Body *_Body = nullptr;

ulong prevMillis;
ulong currMillis;

void setup()
{
    Serial.begin(9600);

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
        // _Body->SetNextTurnPosition(Rotation::LEFT);
        // _Body->SetNextStepPosition(Direction::FORWARD);
    }

    if (currMillis - prevMillis >= TIMER_PERIOD)
    {
        _Body->MoveToPosistion();
        prevMillis = currMillis;
    }
}
