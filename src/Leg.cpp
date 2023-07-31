#include "Leg.h"

Leg::Leg(byte coxaPin, byte femurPin, byte tibiaPin)
{
    _CoxaJoint = new ServoMotor(coxaPin);
    _FemurJoint = new ServoMotor(femurPin);
    _TibiaJoint = new ServoMotor(tibiaPin);
}

Leg::~Leg()
{
    delete _CoxaJoint;
    delete _FemurJoint;
    delete _TibiaJoint;
}

void Leg::SetDefaultPos(LegPos pos)
{
    _CoxaBase = pos.CoxaAngle;
    _FemurBase = pos.FemurAngle;
    _TibiaBase = pos.TibiaAngle ;
}