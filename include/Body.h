#pragma once
#include <Arduino.h>
#include "Leg.h"

#define NUMBER_OF_LEGS 6

class Body
{
private:
    std::vector<Leg *> _Legs;
    int _StanceAngles[6]{-20, 0, 20, -20, 0, 20};
    int _StepNumber{0};
    bool _OnPosition{false};

public:
    Body();
    void ReachInitialPosition();
    void SetStancePosition();
    void SetNextStepPosition();
    void MoveToPosistion();
    inline bool IsOnPosition() { return _OnPosition; }
};