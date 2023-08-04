#include <Arduino.h>
#include "Body.h"

Body *_Body = nullptr;

ulong prevMillis;
ulong currMillis;

void setup()
{
    _Body = new Body();
    (*_Body).ReachInitialPosition();

    delay(6000);

    _Body->SetStancePosition();
    prevMillis = millis();
}

void loop()
{
    currMillis = millis();

    if (currMillis - prevMillis >= 30)
    {
        _Body->StandUp();
        prevMillis = currMillis;
    }
}
