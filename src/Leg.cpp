#include "Leg.h"

Leg::Leg(byte coxaPin, byte femurPin, byte tibiaPin, bool left)
{
    _CoxaJoint = new ServoMotor(coxaPin);
    _FemurJoint = new ServoMotor(femurPin);
    _TibiaJoint = new ServoMotor(tibiaPin);

    _Left = left;
}

Leg::~Leg()
{
    delete _CoxaJoint;
    delete _FemurJoint;
    delete _TibiaJoint;
}

void Leg::SetDefaultPos(int coxaAngle, int femurAngle, int tibiaAngle)
{
    _CoxaInfo.JointBase = coxaAngle;
    _CoxaInfo.JointPrevious = coxaAngle;
    _CoxaInfo.JointCurrent = coxaAngle;

    _FemurInfo.JointBase = femurAngle;
    _FemurInfo.JointPrevious = femurAngle;
    _FemurInfo.JointCurrent = femurAngle;

    _TibiaInfo.JointBase = tibiaAngle;
    _TibiaInfo.JointPrevious = tibiaAngle;
    _TibiaInfo.JointCurrent = tibiaAngle;

    (*_CoxaJoint).write(coxaAngle);
    (*_FemurJoint).write(femurAngle);
    (*_TibiaJoint).write(tibiaAngle);
}

void Leg::DetermineServoAngles(Point point)
{
    DetermineServoAngles(point, _CoxaInfo.JointCurrent);
}

void Leg::DetermineServoAngles(Point point, int coxaAngle)
{
    // direction values

    double input = sqrt(pow(point.X, 2) + pow(point.Z, 2));
    double baseAngle = degrees(atan(point.X / point.Z));

    // femur angle value

    double femurAngle = degrees(
        acos(
            (pow(TIBIA_FOOT_DISTANCE, 2) - pow(FEMUR_TIBIA_DISTANCE, 2) - pow(input, 2)) /
            (-2 * FEMUR_TIBIA_DISTANCE * input)));

    // tibia angle value

    double tibiaAngle = degrees(
        asin((input * sin(radians(femurAngle))) / TIBIA_FOOT_DISTANCE) +
        asin((LEG_BEND_DISTANCE * sin(radians(LEG_BEND_ANGLE))) / TIBIA_FOOT_DISTANCE));

    // final values for servos

    short sideConstant = _Left ? 1 : -1;

    int coxaToWrite = _CoxaInfo.JointBase + (sideConstant * coxaAngle);

    int femurToWrite = _FemurInfo.JointBase + sideConstant * (180 - (baseAngle + femurAngle));

    int tibiaToWrite = _TibiaInfo.JointBase + sideConstant * (90 - tibiaAngle);

    // save destination values

    _CoxaInfo.JointDestination = coxaToWrite;
    _FemurInfo.JointDestination = femurToWrite;
    _TibiaInfo.JointDestination = tibiaToWrite;

    OnPosition = false;
}

void Leg::ExecuteMovement()
{
    _CoxaInfo.JointCurrent = (_CoxaInfo.JointDestination * 0.05) + (_CoxaInfo.JointPrevious * 0.95);
    _CoxaInfo.JointPrevious = _CoxaInfo.JointCurrent;

    _FemurInfo.JointCurrent = (_FemurInfo.JointDestination * 0.05) + (_FemurInfo.JointPrevious * 0.95);
    _FemurInfo.JointPrevious = _FemurInfo.JointCurrent;

    _TibiaInfo.JointCurrent = (_TibiaInfo.JointDestination * 0.05) + (_TibiaInfo.JointPrevious * 0.95);
    _TibiaInfo.JointPrevious = _TibiaInfo.JointCurrent;

    (*_CoxaJoint).write(_CoxaInfo.JointCurrent);
    (*_FemurJoint).write(_FemurInfo.JointCurrent);
    (*_TibiaJoint).write(_TibiaInfo.JointCurrent);

    OnPosition = abs(_CoxaInfo.JointDestination - _CoxaInfo.JointCurrent) < 0.2 &&
                 abs(_FemurInfo.JointDestination - _FemurInfo.JointCurrent) < 0.2 &&
                 abs(_TibiaInfo.JointDestination - _TibiaInfo.JointCurrent) < 0.2;
}