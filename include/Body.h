#pragma once
#include <Arduino.h>
#include "Leg.h"

#define NUMBER_OF_LEGS 6

class Body
{
private:
    std::vector<Leg*> _Legs; 
    bool _OnPosition{false};
public:
    Body();
    void ReachInitialPosition();
    void SetStancePosition();
    void StandUp();
};