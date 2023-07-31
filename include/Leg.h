#pragma once
#include <ServoMotor.h>
#include "LegPos.h"

class Leg
{
private:
    ServoMotor *_CoxaJoint;
    ServoMotor *_FemurJoint;
    ServoMotor *_TibiaJoint;

    byte _CoxaBase;
    byte _FemurBase;
    byte _TibiaBase;

public:
    Leg(byte coxaPin, byte femurPin, byte tibiaPin);
    ~Leg();
    void SetDefaultPos(LegPos pos);
};